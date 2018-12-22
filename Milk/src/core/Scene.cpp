#include "Scene.h"

Scene::Scene(Game& game)
	: _game(game)
{
}

Scene::~Scene()
{
}

Actor* Scene::spawnActor(const std::string& name)
{
	int id = _idGenerator.popId();

	auto actor = std::unique_ptr<Actor>(new Actor(*this));
	actor->_id = id;
	actor->_name = name;

	_actorsById.insert(std::make_pair(id, std::move(actor)));

	return _actorsById.at(id).get();
}

bool Scene::destroyActor(int id)
{
	if (_actorsById.find(id) == _actorsById.end())
		return false;

	_actorsToRemove.emplace_back(id);

	return true;
}

Actor* Scene::findActor(const std::string& name)
{
	for (auto& it : _actorsById) 
	{
		if (it.second->getName() == name)
			return it.second.get();
	}

	return nullptr;
}
