#include "LevelLoader.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "../externals/tinyxml2.h"

#include "../core/Game.h"
#include "../core/GameObject.h"
#include "../core/Level.h"

LevelLoader::LevelLoader(Game& game)
	: _game(game)
{
}

Level* LevelLoader::load(const std::string& file)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());

	Level* level = new Level(_game);
	Tilemap& tilemap = level->_tilemap;

	tinyxml2::XMLElement* root = doc.RootElement();

	tilemap.sourceImageFile = root->Attribute("source");
	tilemap.width = root->IntAttribute("width");
	tilemap.height = root->IntAttribute("height");
	tilemap.tileSize = root->IntAttribute("tilesize");

	tinyxml2::XMLElement* tilesetElement = root->FirstChildElement("tileset");

	for (tinyxml2::XMLElement* e = tilesetElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		int id = e->IntAttribute("id");
		int x = e->IntAttribute("x");
		int y = e->IntAttribute("y");

		tilemap.addTileType(id, x, y);
	}

	tinyxml2::XMLElement* layersElement = tilesetElement->NextSiblingElement();

	int rows = tilemap.height / tilemap.tileSize;
	int columns = tilemap.width / tilemap.tileSize;

	for (tinyxml2::XMLElement* e = layersElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		tinyxml2::XMLElement* tiles = e->FirstChildElement("tiles");
		const char* tilesText = tiles->GetText();

		std::istringstream iss(tilesText);
		std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

		TileLayer& layer = tilemap.addLayer();

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

				layer.addTile(*tile, x, y);
			}

			currentColumn++;
			if (currentColumn > columns - 1)
			{
				currentColumn = 0;
				currentRow++;
			}
		}
	}

	tinyxml2::XMLElement* objectsElement = layersElement->NextSiblingElement("gameobjects");

	for (tinyxml2::XMLElement* e = objectsElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const char* id = e->Attribute("id");
		
		int x = e->IntAttribute("x");
		int y = e->IntAttribute("y");

		GameObject& gameObject = level->createGameObject(id);
		gameObject.position.x = x;
		gameObject.position.y = y;
	}

	return level;
}
