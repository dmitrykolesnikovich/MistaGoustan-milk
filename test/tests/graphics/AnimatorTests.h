#ifndef MILK_ANIMATOR_TESTS_H
#define MILK_ANIMATOR_TESTS_H

#include "gtest/gtest.h"

#include "graphics/Animator.h"
#include "scene/Actor.h"

class AnimatorTests : public ::testing::Test {};

TEST_F(AnimatorTests, Ctor_Constructs) {
    milk::Actor actor{1, "steve", {0,0}};
    ASSERT_NO_THROW(milk::Animator(actor, 1, 1));
    ASSERT_NO_THROW(milk::Animator(actor, 1, 1, 0.5f));
}

#endif
