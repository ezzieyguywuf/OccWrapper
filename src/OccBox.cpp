#include <OccBox.h>
#include <OccTypes.h>

#include <TopoDS.hxx>

using Occ::Box;
using Occ::FaceName;
Box::Box(BRepPrimAPI_MakeBox aMaker)
    : Occ::Primitive(TopoDS::Solid(aMaker.Shape()))
{
    myNamedFaces.emplace(FaceName::top, Solid::getFaceIndex(Occ::Face(aMaker.TopFace())));
    myNamedFaces.emplace(FaceName::bottom, Solid::getFaceIndex(Occ::Face(aMaker.BottomFace())));
    myNamedFaces.emplace(FaceName::left, Solid::getFaceIndex(Occ::Face(aMaker.LeftFace())));
    myNamedFaces.emplace(FaceName::right, Solid::getFaceIndex(Occ::Face(aMaker.RightFace())));
    myNamedFaces.emplace(FaceName::front, Solid::getFaceIndex(Occ::Face(aMaker.FrontFace())));
    myNamedFaces.emplace(FaceName::back, Solid::getFaceIndex(Occ::Face(aMaker.BackFace())));
}
