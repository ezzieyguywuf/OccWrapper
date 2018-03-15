#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <TopoDS.hxx>

#include <array>
#include <vector>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::array;
using std::vector;
using ::testing::ElementsAreArray;
using ::testing::Contains;

TEST(OccModifiedSolid, twoBoxes){
    Occ::Box box1 = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Box box2 = Occ::SolidMaker::makeBox(10, 10, 5);
    Occ::ModifiedSolid modifiedSolid(box1, box2);

    EXPECT_EQ(modifiedSolid.getNewSolid().getFaces().size(), 6);
}

TEST(OccModifiedSolid, oneToOneFaceModification)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    // ms = Modified Solid
    Occ::ModifiedSolid ms(box, mkFuse);
    // nf = New Faces
    const vector<Occ::Face>& nf = ms.getNewSolid().getFaces();

    const Occ::Face& back = box.getNamedFace(Occ::FaceName::back);
    const Occ::Face& left = box.getNamedFace(Occ::FaceName::left);

    // ASSERT values determined manually via FreeCAD
    ASSERT_THAT(ms.getModifiedFaces(back), ElementsAreArray({nf[4]}));
    ASSERT_THAT(ms.getModifiedFaces(left), ElementsAreArray({nf[5]}));
}

TEST(OccModifiedSolid, oneToManyFaceModification)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    // ms = Modified Solid
    Occ::ModifiedSolid ms(box, mkFuse);
    // nf = New Faces
    const vector<Occ::Face>& nf = ms.getNewSolid().getFaces();

    const Occ::Face& top = box.getNamedFace(Occ::FaceName::top);
    const Occ::Face& bottom = box.getNamedFace(Occ::FaceName::bottom);

    // ASSERT values determined manually via FreeCAD
    ASSERT_THAT(ms.getModifiedFaces(top), Contains(nf[3]));
    ASSERT_THAT(ms.getModifiedFaces(top), Contains(nf[7]));
    ASSERT_THAT(ms.getModifiedFaces(bottom), Contains(nf[1]));
    ASSERT_THAT(ms.getModifiedFaces(bottom), Contains(nf[6]));
}

TEST(OccModifiedSolid, noFaceModification)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    // ms = Modified Solid
    Occ::ModifiedSolid ms(box, mkFuse);
    // nf = New Faces
    const vector<Occ::Face>& nf = ms.getNewSolid().getFaces();

    const Occ::Face& front = box.getNamedFace(Occ::FaceName::front);
    const Occ::Face& right = box.getNamedFace(Occ::FaceName::right);

    // ASSERT values determined manually via FreeCAD
    ASSERT_THAT(ms.getModifiedFaces(front), ElementsAreArray({nf[2]}));
    ASSERT_THAT(ms.getModifiedFaces(right), ElementsAreArray({nf[0]}));
}
