#include <OccFace.h>

#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>

using Occ::Face;

Face::Face(const TopoDS_Face& aFace)
    : Shape(aFace)
{
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(this->getShape(), TopAbs_EDGE, edges);
    for (int i=1; i <= edges.Extent(); i++)
    {
        myEdges.push_back(Occ::Edge(TopoDS::Edge(edges.FindKey(i))));
    }
}

const Occ::Edges& Face::getEdges() const
{
    return myEdges;
}
