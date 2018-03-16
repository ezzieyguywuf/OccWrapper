#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <utility>

using uint = unsigned int;
using std::pair;
using ::testing::ElementsAreArray;

TEST(OccSolidModifier, getConstituentFace){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    Occ::BooleanSolid boolSolid = Occ::SolidModifier::makeFusion(box, cyl);

    const Occ::Face& getFace1 = boolSolid.getFaces()[3];
    const Occ::Face& getFace2 = boolSolid.getFaces()[7];

    auto data1 = boolSolid.getConstituentFace(getFace1);
    auto data2 = boolSolid.getConstituentFace(getFace2);

    EXPECT_THAT(data1, ElementsAreArray({0, 5, 0}));
    EXPECT_THAT(data2, ElementsAreArray({0, 5, 1}));
}
