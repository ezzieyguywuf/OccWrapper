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

    const Occ::Face& back = box.getNamedFace(Occ::FaceName::back);
    const Occ::Face& left = box.getNamedFace(Occ::FaceName::left);

    // ASSERT values determined manually via FreeCAD
    EXPECT_THAT(ms.getModifiedFaceIndices(back), ElementsAreArray({4}));
    EXPECT_THAT(ms.getModifiedFaceIndices(left), ElementsAreArray({5}));
}

TEST(OccModifiedSolid, oneToOneFaceModificationWithTranslation)
{
    Occ::Box box1 = Occ::SolidMaker::makeBox(10, 10, 10);
    box1.translate(-5,5,3);
    Occ::Box box2 = Occ::SolidMaker::makeBox(5,5,5);

    Occ::ModifiedSolid ms(box1, box2);

    const Occ::Face& front = box1.getNamedFace(Occ::FaceName::front);
    const Occ::Face& top = box1.getNamedFace(Occ::FaceName::top);

    EXPECT_THAT(ms.getModifiedFaceIndices(front), ElementsAreArray({1}));
    EXPECT_THAT(ms.getModifiedFaceIndices(top), ElementsAreArray({5}));
}

TEST(OccModifiedSolid, oneToManyFaceModification)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    // ms = Modified Solid
    Occ::ModifiedSolid ms(box, mkFuse);

    const Occ::Face& top = box.getNamedFace(Occ::FaceName::top);
    const Occ::Face& bottom = box.getNamedFace(Occ::FaceName::bottom);

    // ASSERT values determined manually via FreeCAD
    EXPECT_THAT(ms.getModifiedFaceIndices(top), ElementsAreArray({3, 7}));
    EXPECT_THAT(ms.getModifiedFaceIndices(bottom), ElementsAreArray({1, 6}));
}

TEST(OccModifiedSolid, noFaceModification)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    // ms = Modified Solid
    Occ::ModifiedSolid ms(box, mkFuse);

    const Occ::Face& front = box.getNamedFace(Occ::FaceName::front);
    const Occ::Face& right = box.getNamedFace(Occ::FaceName::right);

    // ASSERT values determined manually via FreeCAD
    EXPECT_THAT(ms.getModifiedFaceIndices(front), ElementsAreArray({2}));
    EXPECT_THAT(ms.getModifiedFaceIndices(right), ElementsAreArray({0}));
}
