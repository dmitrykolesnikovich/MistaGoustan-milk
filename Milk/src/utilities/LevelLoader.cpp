#include "LevelLoader.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "../externals/tinyxml.h"
#include "../externals/tinystr.h"

#include "../core/Game.h"
#include "../core/GameObject.h"
#include "../core/Level.h"

LevelLoader::LevelLoader(Game& game)
	: _game(game)
{
}

Level* LevelLoader::load(const std::string& file)
{
	TiXmlDocument doc;
	doc.LoadFile(file);

	Level* level = new Level(_game);
	Tilemap& tilemap = level->_tilemap;

	TiXmlElement* root = doc.RootElement();

	tilemap.sourceImageFile = root->Attribute("source");
	root->Attribute("width", &tilemap.width);
	root->Attribute("height", &tilemap.height);
	root->Attribute("tilesize", &tilemap.tileSize);

	TiXmlElement* tilesetElement = root->FirstChildElement("tileset");

	for (TiXmlElement* e = tilesetElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) 
	{
		int id;
		int x;
		int y;

		e->Attribute("id", &id);
		e->Attribute("x", &x);
		e->Attribute("y", &y);

		tilemap.tileTypes.insert(std::pair<int, TileType*>(id, new TileType(x, y, tilemap.tileSize)));
	}

	TiXmlElement* layersElement = tilesetElement->NextSiblingElement();

	int rows = tilemap.height / tilemap.tileSize;
	int columns = tilemap.width / tilemap.tileSize;

	for (TiXmlElement* e = layersElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		TiXmlElement* tiles = e->FirstChildElement("tiles");
		const char* tilesText = tiles->GetText();

		std::istringstream iss(tilesText);
		std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

		TileLayer* layer = new TileLayer();

		int currentRow = 0;
		int currentColumn = 0;

		for (auto& t : results) 
		{
			int tileid = std::atoi(t.c_str());
			if (tileid > 0) 
			{
				TileType* tile = tilemap.tileTypes[tileid];

				int x = currentColumn * tilemap.tileSize;
				int y = currentRow * tilemap.tileSize;

				layer->tiles.push_back(new TileInstance(*tile, x, y));
			}

			currentColumn++;
			if (currentColumn > columns - 1)
			{
				currentColumn = 0;
				currentRow++;
			}
		}

		tilemap.layers.push_back(layer);
	}

	TiXmlElement* objectsElement = layersElement->NextSiblingElement("gameobjects");

	for (TiXmlElement* e = objectsElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const char* id = e->Attribute("id");
		
		int x;
		int y;

		e->Attribute("x", &x);
		e->Attribute("y", &y);

		GameObject& gameObject = level->createGameObject(id);
		gameObject.position.x = x;
		gameObject.position.y = y;
	}

	return level;
}
