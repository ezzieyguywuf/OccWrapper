#include <OccFaceComparator.h>
#include <OccSolidMaker.h>
#include <OccModifiedSolid.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>

#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BinTools.hxx>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Cut* mkCut = new BRepAlgoAPI_Cut(box.getShape(), cyl.getShape());
    Occ::Solid newSolid(mkCut->Shape());

    std::cout << "neSolid.getFaces.size()" << newSolid.getFaces().size() << std::endl;
    return 0;
}
