#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <TopoDS.hxx>
#include "gtest/gtest.h"

TEST(OccModifiedSolid, twoBoxes){
    Occ::Box box1 = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Box box2 = Occ::SolidMaker::makeBox(10, 10, 5);
    Occ::ModifiedSolid modifiedSolid(box1, box2);

    EXPECT_EQ(modifiedSolid.getNewSolid().getFaces().size(), 6);
}

TEST(OccModifiedSolid, booleanOperation)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    Occ::ModifiedSolid modifiedSolid(box, mkFuse);
    Occ::Face left = box.getNamedFace(Occ::FaceName::left);
    Occ::Face front = box.getNamedFace(Occ::FaceName::front);
    auto iter = modifiedSolid.getModifiedFaceIndices().begin();

    EXPECT_EQ(modifiedSolid.getNewSolid().getFaces().size(), 11);
    EXPECT_TRUE(modifiedSolid.isModified(left));
    EXPECT_FALSE(modifiedSolid.isModified(front));
    EXPECT_EQ(modifiedSolid.getModifiedFaceIndices().size(), 4);
    EXPECT_LE((*iter).first, 6);
    EXPECT_LE((*iter).second, 11);
}

TEST(OccModifiedSolid, getModifiedFace)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    Occ::ModifiedSolid modifiedSolid(box, mkFuse);
    Occ::Face left = box.getNamedFace(Occ::FaceName::left);
    Occ::Face front = box.getNamedFace(Occ::FaceName::front);

    EXPECT_NE(modifiedSolid.getModifiedFace(left), left);
}
