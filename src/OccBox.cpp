#include <OccBox.h>
#include <OccTypes.h>

#include <TopoDS.hxx>

using Occ::Box;
using Occ::FaceName;
Box::Box(BRepPrimAPI_MakeBox aMaker)
    : Occ::Primitive(TopoDS::Solid(aMaker.Shape()))
{
    myNamedFaces.emplace(FaceName::top, Occ::Face(aMaker.TopFace()));
    myNamedFaces.emplace(FaceName::bottom, Occ::Face(aMaker.BottomFace()));
    myNamedFaces.emplace(FaceName::left, Occ::Face(aMaker.LeftFace()));
    myNamedFaces.emplace(FaceName::right, Occ::Face(aMaker.RightFace()));
    myNamedFaces.emplace(FaceName::front, Occ::Face(aMaker.FrontFace()));
    myNamedFaces.emplace(FaceName::back, Occ::Face(aMaker.BackFace()));
}
