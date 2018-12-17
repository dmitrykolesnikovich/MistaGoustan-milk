#include "LevelLoader.h"

#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cstdlib>
#include <vector>

#include "Level.h"
#include "Tilemap.h"
#include "TilemapLayer.h"
#include "TilemapTile.h"
#include "Game.h"
#include "GameObject.h"

Level* LevelLoader::build(const char* file)
{
	TiXmlDocument doc;
	doc.LoadFile(file);

	Level* level = new Level();
	Tilemap* tilemap = new Tilemap();
	level->_tilemap = tilemap;

	TiXmlElement* root = doc.RootElement();

	tilemap->source = root->Attribute("source");
	root->Attribute("width", &tilemap->width);
	root->Attribute("height", &tilemap->height);
	root->Attribute("tilesize", &tilemap->tilesize);

	TiXmlElement* tilesetElement = root->FirstChildElement("tileset");

	for (TiXmlElement* e = tilesetElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) 
	{
		int id;
		int x;
		int y;

		e->Attribute("id", &id);
		e->Attribute("x", &x);
		e->Attribute("y", &y);

		tilemap->tileTypes.insert(std::pair<int, TilemapTile*>(id, new TilemapTile(x, y, tilemap->tilesize)));
	}

	TiXmlElement* layersElement = tilesetElement->NextSiblingElement();

	int rows = tilemap->height / tilemap->tilesize;
	int columns = tilemap->width / tilemap->tilesize;

	for (TiXmlElement* e = layersElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		TiXmlElement* tiles = e->FirstChildElement("tiles");
		const char* tilesText = tiles->GetText();

		std::istringstream iss(tilesText);
		std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

		TilemapLayer* layer = new TilemapLayer();

		int currentRow = 0;
		int currentColumn = 0;

		for (auto& t : results) 
		{
			int tileid = std::atoi(t.c_str());
			TilemapTile* tile = tilemap->tileTypes[tileid];

			int x = currentColumn * tilemap->tilesize;
			int y = currentRow * tilemap->tilesize;
			
			layer->tiles.push_back(new TilemapTileInstance(*tile, x, y));

			currentColumn++;
			if (currentColumn > columns - 1)
			{
				currentColumn = 0;
				currentRow++;
			}
		}

		tilemap->layers.push_back(layer);
	}

	TiXmlElement* objectsElement = layersElement->NextSiblingElement("gameobjects");

	for (TiXmlElement* e = objectsElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const char* id = e->Attribute("id");
		
		int x;
		int y;

		e->Attribute("x", &x);
		e->Attribute("y", &y);

		GameObject* gameObject = Game::getInstance().createFromFactory(id);
		gameObject->setX(x);
		gameObject->setY(y);

		level->_gameObjectsToAdd.push_back(gameObject);
	}

	return level;
}
