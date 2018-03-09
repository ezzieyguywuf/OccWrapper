#include <OccSolid.h>

#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>

using Occ::Solid;

Solid::Solid(const TopoDS_Solid& aSolid)
    : Shape(aSolid)
{
    TopTools_IndexedMapOfShape faces;
    TopExp::MapShapes(this->getShape(), TopAbs_FACE, faces);
    for (int i=1; i <= faces.Extent(); i++)
    {
        myFaces.push_back(Occ::Face(TopoDS::Face(faces.FindKey(i))));
    }

    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(this->getShape(), TopAbs_EDGE, edges);
    for (int i=1; i <= edges.Extent(); i++)
    {
        myEdges.push_back(Occ::Edge(TopoDS::Edge(edges.FindKey(i))));
    }
}

const Occ::Faces& Solid::getFaces() const
{
    return myFaces;
}

const Occ::Edges& Solid::getEdges() const
{
    return myEdges;
}
