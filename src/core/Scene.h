#ifndef _SCENE_
#define _SCENE_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Actor.h"
#include "IScene.h"

#include "tilemap/Tilemap.h"

#include "utilities/Camera.h"
#include "utilities/IdGenerator.h"

class Game;

class Scene : public IScene
{
public:
	explicit Scene(Game& game);
	~Scene() = default;

		// Spawns a new actor in the games current scene.
		// Components are to be added immediately after spawned actor is returned.
		Actor* spawnActor(const std::string& name) override;

		// Attempts to destroy and actor with the given id.
		// Returns true if successful.
		bool destroyActor(int id) override;

		// Attempts to find an actor with the given name.
		// Returns nullptr if not actor is found.
		Actor* findActor(const std::string& name) const override;

		// Returns the scenes camera.
		Camera& camera() override;

		// Returns the scenes tilemap.
		Tilemap& tilemap() override;

		// Updates the scenes internal lists after spawning and destroying actors.
		void updateActorList() override;

		// Destroys all actors and generates events.
		void end() override;

		// Return the scene boundaries.
		SDL_Rect bounds() const;

private:
	Game& game_;
	
	IdGenerator idGenerator_;
	Camera camera_;
	Tilemap tilemap_;

	std::unordered_map<int, std::unique_ptr<Actor>> actorsById_;
	std::vector<std::unique_ptr<Actor>> actorsToSpawn_;
	std::vector<int> actorsToDestroy_;
};

#endif
