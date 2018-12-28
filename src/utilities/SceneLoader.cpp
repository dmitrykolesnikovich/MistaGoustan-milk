#include "SceneLoader.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "../externals/tinyxml2.h"

#include "../components/Animator.h"
#include "../components/Behavior.h"
#include "../components/BoxCollider.h"
#include "../components/Sprite.h"
#include "../components/Velocity.h"
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
					actor->position((float)x, (float)y);
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

	tinyxml2::XMLElement* objectsElement = layersElement->NextSiblingElement("actors");

	for (tinyxml2::XMLElement* e = objectsElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const char* name = e->FirstChildElement("name")->GetText();
		tinyxml2::XMLElement* posElement = e->FirstChildElement("position");
		int x = posElement->IntAttribute("x");
		int y = posElement->IntAttribute("y");

		Actor* actor = scene->spawnActor(name);
		actor->position(x, y);

		tinyxml2::XMLElement* componentsElement = e->FirstChildElement("components");

		for (tinyxml2::XMLElement* e = componentsElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			const char* type = e->Attribute("type");

			if (strcmp(type, "Sprite") == 0) 
			{
				const char* textureName = e->FirstChildElement("textureName")->GetText();
				tinyxml2::XMLElement* srcRctElement = e->FirstChildElement("sourceRect");
				int sx = srcRctElement->IntAttribute("x");
				int sy = srcRctElement->IntAttribute("y");
				int sw = srcRctElement->IntAttribute("w");
				int sh = srcRctElement->IntAttribute("h");

				actor->addComponent<Sprite>();
				auto sprite = actor->getComponent<Sprite>();
				sprite->textureName(textureName);
				sprite->sourceRect(sx,sy, sw, sh);
			}

			if (strcmp(type, "Velocity") == 0)
			{
				float vx = e->FloatAttribute("x");
				float vy = e->FloatAttribute("y");

				actor->addComponent<Velocity>();
				auto vel = actor->getComponent<Velocity>();
				vel->value(vx, vy);
			}

			if (strcmp(type, "Script") == 0)
			{
				const char* name = e->Attribute("name");
				actor->addComponent<Behavior>();
				auto beh = actor->getComponent<Behavior>();
				beh->script(name);
			}

			if (strcmp(type, "Collider") == 0)
			{
				int w = e->IntAttribute("w");
				int h = e->IntAttribute("h");

				actor->addComponent<BoxCollider>();
				auto coll = actor->getComponent<BoxCollider>();
				coll->width(w);
				coll->height(h);
			}

			if (strcmp(type, "Animator") == 0)
			{
				int rows = e->IntAttribute("rows");
				int columns = e->IntAttribute("columns");

				actor->addComponent<Animator>();
				auto animator = actor->getComponent<Animator>();
				animator->rows(rows);
				animator->columns(columns);

				tinyxml2::XMLElement* animationElements = e->FirstChildElement("animations");

				for (tinyxml2::XMLElement* e = animationElements->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) 
				{
					const char* name = e->Attribute("name");

					const char* tilesText = e->Attribute("frames");

					std::istringstream iss(tilesText);
					std::vector<std::string> res((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

					std::vector<int> f(0);

					for (auto& it : res) 
					{
						f.emplace_back(std::atoi(it.c_str()));
					}

					animator->addAnimation(name, f);
				}
			}
		}
	}

	auto& resourceManager = game_.resourceManager();

	tilemap.texture = resourceManager.loadTexture(tilemap.sourceImageFile);

	return scene;
}
