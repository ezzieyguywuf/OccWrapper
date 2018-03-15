#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <utility>

using uint = unsigned int;
using std::pair;
using ::testing::ElementsAre;
using ::testing::Pair;

TEST(OccSolidModifier, getConstituentFace){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    Occ::BooleanSolid boolSolid = Occ::SolidModifier::makeFusion(box, cyl);

    const pair<int, int>& data1 = boolSolid.getConstituentFace(boolSolid.getFaces()[3]);
    const pair<int, int>& data2 = boolSolid.getConstituentFace(boolSolid.getFaces()[7]);

    EXPECT_THAT(data1, Pair(0, 5));
    EXPECT_THAT(data2, Pair(0, 5));
}
