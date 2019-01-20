#ifndef _MSCENE_
#define _MSCENE_

#include "gmock/gmock.h"

#include "core/IScene.h"

class MScene : public IScene
{
public:
    MOCK_METHOD1(spawnActor, Actor*( const std::string&));
    MOCK_METHOD1(destroyActor, bool(int));
    MOCK_CONST_METHOD1(findActor, Actor*(const std::string&));
    MOCK_METHOD0(camera, Camera&());
    MOCK_METHOD0(tilemap, Tilemap&());
    MOCK_METHOD0(updateActorList, void());
    MOCK_METHOD0(end, void());
    MOCK_CONST_METHOD0(bounds, SDL_Rect());
};

#endif