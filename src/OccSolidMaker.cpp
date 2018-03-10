#include <OccSolidMaker.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>


using Occ::SolidMaker;

Occ::Box SolidMaker::makeBox(double dx, double dy, double dz)
{
    return Occ::Box(BRepPrimAPI_MakeBox(dx, dy, dz));
}

Occ::Cylinder SolidMaker::makeCylinder(double rad, double height)
{
    return Occ::Cylinder(BRepPrimAPI_MakeCylinder(rad, height));
}
