#include "gtest/gtest.h"

#include "../test/tests/core/ActorTests.h"
#include "../test/tests/core/SceneTests.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}