#include "SceneLoader.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "SDL.h"

#include "../externals/json.hpp"
#include "../externals/tinyxml2.h"

#include "../components/Animator.h"
#include "../components/Script.h"
#include "../components/BoxCollider.h"
#include "../components/Sprite.h"
#include "../components/Velocity.h"
#include "../core/Game.h"
#include "../core/Actor.h"

SceneLoader::SceneLoader(Game& game)
	: game_(game)
{
}

std::unique_ptr<Scene> SceneLoader::loadJson(const std::string& file) const
{
	using json = nlohmann::json;

	auto& resourceManager = game_.resourceManager();

	auto sceneJsonString = resourceManager.loadFile(file);
	json sceneJson = json::parse(sceneJsonString);

	auto scene = std::unique_ptr<Scene>(new Scene(game_));
	auto& tilemap = scene->tilemap();

	tilemap.sourceImageFile = sceneJson["source"].get<std::string>();
	tilemap.width = sceneJson["width"].get<int>();
	tilemap.height = sceneJson["height"].get<int>();
	tilemap.tileSize = sceneJson["tileSize"].get<int>();

	auto& tilesetJson = sceneJson["tileset"];

	for (auto& it : tilesetJson.items())
	{
		auto& tileTypeJson = it.value();

		int tileTypeId = tileTypeJson["id"].get<int>();
		std::string name = tileTypeJson["name"].get<std::string>();
		int x = tileTypeJson["x"].get<int>();
		int y = tileTypeJson["x"].get<int>();
		bool collidable = tileTypeJson["collidable"].get<bool>();

		tilemap.addTileType(tileTypeId, x, y, collidable, name);
	}

	int rows = tilemap.height / tilemap.tileSize;
	int columns = tilemap.width / tilemap.tileSize;

	auto& layersJson = sceneJson["layers"];

	for (auto& it : layersJson.items())
	{
		auto& tilemapLayer = tilemap.addLayer();

		auto& layerJson = it.value();

		for (int i = 0; i < layerJson.size(); ++i) 
		{
			auto& row = layerJson[i];

			for (int j = 0; j < row.size(); ++j)
			{
				auto& column = row[j];
				int typeId = column.get<int>();

				if (typeId > 0) 
				{
					auto tile = tilemap.tileTypes[typeId];

					int x = j * tilemap.tileSize;
					int y = i * tilemap.tileSize;

					tilemapLayer.addTile(*tile, x, y);

					if (tile->collidable)
					{
						auto actor = scene->spawnActor(tile->name);
						actor->position((float)x, (float)y);

						auto coll = actor->addComponent<BoxCollider>();
						coll->width(tilemap.tileSize);
						coll->height(tilemap.tileSize);
					}
				}
			}
		}
	}

	tilemap.texture = resourceManager.loadTexture(tilemap.sourceImageFile);

	return scene;
}

std::unique_ptr<Scene> SceneLoader::load(const std::string& file) const
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());

	std::unique_ptr<Scene> scene(new Scene(game_));
	Tilemap& tilemap = scene->tilemap();

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
		const char* name = e->Attribute("name");

		if (name == nullptr)
			name = "tile";

		tilemap.addTileType(id, x, y, collidable, name);
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
					Actor* actor = scene->spawnActor(tile->name);
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
				sprite->center();
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
				actor->addComponent<Script>();
				auto beh = actor->getComponent<Script>();
				beh->script(name);
			}

			if (strcmp(type, "Collider") == 0)
			{
				int w = e->IntAttribute("w");
				int h = e->IntAttribute("h");
				int xOff = e->IntAttribute("xOffset");
				int yOff = e->IntAttribute("yOffset");

				actor->addComponent<BoxCollider>();
				auto coll = actor->getComponent<BoxCollider>();
				coll->center();
				coll->width(w);
				coll->height(h);
				coll->offset(xOff, yOff);
				coll->updateBBox();
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
