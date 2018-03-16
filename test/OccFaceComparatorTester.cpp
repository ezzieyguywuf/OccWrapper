#include <OccFaceComparator.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccFace.h>
#include <OccSolidMaker.h>
#include <OccTypes.h>
#include <TopoDS.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <utility>

TEST(OccFaceComparator, compareFaces){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);

    const Occ::Face& front = box.getNamedFace(Occ::FaceName::front);
    const Occ::Face& back = box.getNamedFace(Occ::FaceName::back);
    const Occ::Face& left = box.getNamedFace(Occ::FaceName::left);
    const Occ::Face& right = box.getNamedFace(Occ::FaceName::right);
    const Occ::Face& top = box.getNamedFace(Occ::FaceName::top);
    const Occ::Face& bottom = box.getNamedFace(Occ::FaceName::bottom);

    Occ::FaceComparator comp;

    EXPECT_TRUE(comp(back, front));;
    EXPECT_TRUE(comp(left, right));;
    EXPECT_TRUE(comp(bottom, top));;
}

TEST(OccFaceComparator, compareFusedFaces)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());

    Occ::BooleanSolid solid = Occ::SolidModifier::makeFusion(box, cyl);

    const Occ::Face& top1 = solid.getFaces()[3];
    const Occ::Face& top2 = solid.getFaces()[7];

    Occ::FaceComparator comp;

    EXPECT_TRUE(comp(top1, top2));;
}
