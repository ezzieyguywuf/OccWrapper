#include <OccFaceComparator.h>
#include <OccSolidMaker.h>
#include <OccModifiedSolid.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());

    Occ::BooleanSolid solid = Occ::SolidModifier::makeFusion(box, cyl);

    const Occ::Face& top1 = solid.getFaces()[3];
    const Occ::Face& top2 = solid.getFaces()[7];
    const Occ::Face& top3 = solid.getFaces()[2];

    BRepAdaptor_Surface adapt1(TopoDS::Face(top1.getShape()));
    BRepAdaptor_Surface adapt2(TopoDS::Face(top2.getShape()));
    BRepAdaptor_Surface adapt3(TopoDS::Face(top3.getShape()));

    std::cout << "adapt1 type = " << adapt1.GetType() << std::endl;
    std::cout << "adapt2 type = " << adapt2.GetType() << std::endl;
    std::cout << "adapt3 type = " << adapt3.GetType() << std::endl;

    Occ::FaceComparator compare;
    compare(top1, top2);

    return 0;
}
