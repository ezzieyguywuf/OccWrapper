#include <PrimitiveSolidManager.h>
#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include "gtest/gtest.h"

TEST(PrimitiveSolidManager, Create){
    Occ::Box myBox = Occ::SolidMaker::makeBox(10, 10, 10);
    PrimitiveSolidManager mgr(myBox);
    uint i = mgr.getFaceIndex(myBox.getNamedFace(Occ::FaceName::top));
    EXPECT_GE(i, 0);
}

TEST(PrimitiveSolidManager, getEdgeByIndex)
{
    // create the box
    Occ::Box myBox(Occ::SolidMaker::makeBox(10, 10, 10));
    // create the solid manager
    PrimitiveSolidManager mgr(myBox);

    // get an Edge index (note: in a real-world application, the user would select an edge
    // with a mouse.)
    Occ::Face front = myBox.getNamedFace(Occ::FaceName::front);
    Occ::Face right = myBox.getNamedFace(Occ::FaceName::right);
    Occ::Edge frontRightEdge = front.getCommonEdge(right);
    uint frontRightEdgeIndex = mgr.getEdgeIndex(frontRightEdge);

    // update the managed solid
    Occ::Box newBox = Occ::SolidMaker::makeBox(5, 5, 5);
    Occ::ModifiedSolid modSolid(myBox, newBox);
    mgr.updateSolid(modSolid);

    // retrieve the Edge using our index
    Occ::Edge retrievedFrontRightEdge = mgr.getEdgeByIndex(frontRightEdgeIndex);

    // Now, in order to check it, build it from scratch too
    front = newBox.getNamedFace(Occ::FaceName::front);
    right = newBox.getNamedFace(Occ::FaceName::right);
    Occ::Edge checkFrontRightEdge = front.getCommonEdge(right);

    EXPECT_NE(frontRightEdge, retrievedFrontRightEdge);
    EXPECT_EQ(checkFrontRightEdge, retrievedFrontRightEdge);
}

//TEST(PrimitiveSolidManager, UpdateSolid)
//{
    //Occ::Box myBox(Occ::SolidMaker::makeBox(10, 10, 10));
    //Occ::Cylinder myCyl(Occ::SolidMaker::makeCylinder(2.5, 10));
    //Occ::ModifiedSolids resultData(Occ::SolidModifier::makeFusion(myBox, myCyl));

    //PrimitiveSolidManager mgr(resultData.getNewSolid());
    //// Front and right faces don't change due to the fusion, so we can access them
    //// directly using Occ::Box methods
    //Occ::Face origFront = myBox.getFace(Occ::FaceName::front);
    //Occ::Face origRight = myBox.getFace(Occ::FaceName::right);
    //// the left face was affected, so this is a little more tricky.
    //Occ::Face origLeft = resultData.getModifiedSolids()[0].getModifiedFace(myBox.getFace(Occ::FaceName::left));

    //// Now, get the "robust reference" to each of these faces.
    //uint indexFront = mgr.getFaceIndex(origFront);
    //uint indexRight = mgr.getFaceIndex(origRight);
    //uint indexLeft = mgr.getFaceIndex(origLeft);
    //uint indexFrontRightEdge = mgr.getEdgeIndex(origFront.getCommonEdge(origRight));
    //uint indexFrontLeftEdge = mgr.getEdgeIndex(origFront.getCommonEdge(origLeft));

    //Occ::Edge origFrontRightEdge = mgr.getEdgeByIndex(indexFrontRightEdge);

    //// next, change the managed solid
    //myCyl = Occ::SolidMaker::makeCylinder(2.5, 5);
    //resultData = Occ::SolidModifier::makeFusion(myBox, myCyl);
//}
