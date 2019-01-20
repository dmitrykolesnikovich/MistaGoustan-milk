#ifndef _ACTOR_TESTS_
#define _ACTOR_TESTS_

#include "gtest/gtest.h"

#include "core/Actor.h"

#include "mocks/core/MScene.h"

class ActorTests : public ::testing::Test {};

TEST_F(ActorTests, Ctor_Constructs)
{
    MScene mscene;
    ASSERT_NO_THROW(Actor(mscene, 2, "steve", {0, 0}));
}

#endif