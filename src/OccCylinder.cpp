#include <OccCylinder.h>

#include <TopoDS.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrim_Cylinder.hxx>

using Occ::Cylinder;

Cylinder::Cylinder(double rad, double height)
    : myMaker(rad, height), mySolid(TopoDS::Solid(myMaker.Shape()))
{
    BRepPrim_Cylinder cyl = myMaker.Cylinder();
    myMappedFaces.emplace("top", Occ::Face(cyl.TopFace()));
    myMappedFaces.emplace("bottom", Occ::Face(cyl.BottomFace()));
    myMappedFaces.emplace("lateral", Occ::Face(cyl.LateralFace()));
}

const Occ::Face& Cylinder::top() const
{
    return myMappedFaces.at("top");
}

const Occ::Face& Cylinder::bottom() const
{
    return myMappedFaces.at("bottom");
}

const Occ::Face& Cylinder::lateral() const
{
    return myMappedFaces.at("lateral");
}

const Occ::Edges& Cylinder::getEdges() const
{
    return mySolid.getEdges();
}
