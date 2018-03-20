#include <OccSolidMaker.h>
#include <OccBox.h>
#include <OccCylinder.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include "gtest/gtest.h"

// TODO create tests for Occ::Box and Occ::Cylinder (do I really need to?)

TEST(OccSolidMaker, makeFusion){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    Occ::BooleanSolid boolSolid = Occ::SolidMaker::makeBoolean(mkFuse);

    EXPECT_EQ(boolSolid.getShape(), mkFuse.Shape());
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getOrigSolid(), box);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getOrigSolid(), cyl);
    EXPECT_EQ(boolSolid.getModifiedSolids().size(), 2);
    EXPECT_EQ(boolSolid.getFaces().size(), 11);
    EXPECT_EQ(boolSolid.getEdges().size(), 21);
}

TEST(OccSolidMaker, makeCut){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Cut mkCut(box.getShape(), cyl.getShape());
    Occ::BooleanSolid boolSolid = Occ::SolidMaker::makeBoolean(mkCut);

    EXPECT_EQ(boolSolid.getShape(), mkCut.Shape());
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getOrigSolid(), box);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getOrigSolid(), cyl);
    EXPECT_EQ(boolSolid.getModifiedSolids().size(), 2);
    EXPECT_EQ(boolSolid.getFaces().size(), 7);
    EXPECT_EQ(boolSolid.getEdges().size(), 15);
}

TEST(OccSolidMaker, makeCommon){
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Common mkCommon(box.getShape(), cyl.getShape());
    Occ::BooleanSolid boolSolid = Occ::SolidMaker::makeBoolean(mkCommon);

    EXPECT_EQ(boolSolid.getShape(), mkCommon.Shape());
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[0].getOrigSolid(), box);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getNewSolid(), boolSolid);
    EXPECT_EQ(boolSolid.getModifiedSolids()[1].getOrigSolid(), cyl);
    EXPECT_EQ(boolSolid.getModifiedSolids().size(), 2);
    EXPECT_EQ(boolSolid.getFaces().size(), 5);
    EXPECT_EQ(boolSolid.getEdges().size(), 9);
}
