#include <OccCylinder.h>

#include <TopoDS.hxx>
#include <BRepPrim_Cylinder.hxx>

using Occ::Cylinder;
using Occ::FaceName;

Cylinder::Cylinder(BRepPrimAPI_MakeCylinder aMaker)
    : Occ::Primitive(TopoDS::Solid(aMaker.Shape()))
{
    BRepPrim_Cylinder cyl = aMaker.Cylinder();
    myNamedFaces.emplace(FaceName::top, Occ::Face(cyl.TopFace()));
    myNamedFaces.emplace(FaceName::bottom, Occ::Face(cyl.BottomFace()));
    myNamedFaces.emplace(FaceName::lateral, Occ::Face(cyl.LateralFace()));
}
