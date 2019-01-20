#ifndef _ISCENE_
#define _ISCENE_

#include <string>

#include "SDL.h"

#include "Actor.h"
#include "utilities/Camera.h"
#include "tilemap/Tilemap.h"

class IScene
{
public:
        // Spawns a new virtual actor in the games current scene.
        // Components are to be added immediately after spawned actor is returned.
        virtual Actor* spawnActor(const std::string& name) = 0;

        // Attempts to destroy and actor with the given id.
        // Returns true if successful.
        virtual bool destroyActor(int id) = 0;

        // Attempts to find an actor with the given name.
        // Returns nullptr if not actor is found.
        virtual Actor* findActor(const std::string& name) const = 0;

        // Returns the scenes camera.
        virtual Camera& camera() = 0;

        // Returns the scenes tilemap.
        virtual Tilemap& tilemap() = 0;

        // Updates the scenes internal lists after spawning and destroying actors.
        virtual void updateActorList() = 0;

        // Destroys all actors and generates events.
        virtual void end() = 0;

        // Return the scene boundaries.
        virtual SDL_Rect bounds() const = 0;
};

#endif