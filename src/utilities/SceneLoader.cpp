#include "SceneLoader.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "../externals/tinyxml2.h"

#include "../components/BoxCollider.h"
#include "../core/Game.h"
#include "../core/Actor.h"

SceneLoader::SceneLoader(Game& game)
	: game_(game)
{
}

std::unique_ptr<Scene> SceneLoader::load(const std::string& file) const
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());

	std::unique_ptr<Scene> scene(new Scene(game_));
	Tilemap& tilemap = scene->getTilemap();

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
		bool collidable = e->BoolAttribute("collidable");

		tilemap.addTileType(id, x, y, collidable);
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

				if (tile->collidable)
				{
					Actor* actor = scene->spawnActor("tile");
					actor->position(x, y);
					actor->addComponent<BoxCollider>();

					auto coll = actor->getComponent<BoxCollider>();
					coll->width(tilemap.tileSize);
					coll->height(tilemap.tileSize);
				}
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
		
	}

	auto& resourceManager = game_.getResourceManager();

	tilemap.texture = resourceManager.loadTexture(tilemap.sourceImageFile);

	return scene;
}
