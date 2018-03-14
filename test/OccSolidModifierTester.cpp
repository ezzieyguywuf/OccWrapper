#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>
#include "gtest/gtest.h"

TEST(OccSolidModifier, makeFusion){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    Occ::BooleanSolid boolSolid = Occ::SolidModifier::makeFusion(box, cyl);

    EXPECT_EQ(boolSolid.getFaces().size(), 11);
}
