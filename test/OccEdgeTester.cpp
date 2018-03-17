#include <OccEdge.h>
#include <OccSolidMaker.h>
#include <OccBox.h>
#include "gtest/gtest.h"

TEST(OccEdge, overlaps){
    // make two topologically distinct, but geometrically equivalent boxes.
    Occ::Box box1 = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Box box2 = Occ::SolidMaker::makeBox(10, 10, 10);

    // grab the same edge from each box
    Occ::Edge edge1 = box1.getEdges()[0];
    Occ::Edge edge2 = box2.getEdges()[0];

    // they should not be equal but should overlap
    EXPECT_NE(edge1, edge2);
    EXPECT_TRUE(edge1.overlaps(edge2));
}
