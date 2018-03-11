#include <PrimitiveSolidManager.h>
#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include "gtest/gtest.h"

class MyShape : public Occ::Shape
{
    public:
        MyShape(TopoDS_Shape aShape)
            : Occ::Shape(aShape){};
};

TEST(OccShape, Equals){
    Occ::Box myBox = Occ::SolidMaker::makeBox(10, 10, 10);
    PrimitiveSolidManager mgr(myBox);
    uint i = mgr.getFaceIndex(myBox.getFace(Occ::FaceName::top));
    EXPECT_GE(i, 0);
}
