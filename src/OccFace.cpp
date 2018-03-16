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

bool Face::sharesEdge(const Face& aFace) const
{
    for (const Edge& myEdge : myEdges)
    {
        for (const Edge& checkEdge : aFace.getEdges())
        {
            if (myEdge.isSimilar(checkEdge))
                return true;
        }
    }
    return false;
}

bool Face::containsEdge(const Edge& anEdge) const
{
    for (const Edge& checkEdge : myEdges)
    {
        if (checkEdge == anEdge)
        {
            return true;
        }
    }
    return false;
}

const Occ::Edge& Face::getCommonEdge(const Face& aFace) const
{
    for (const Edge& myEdge : myEdges)
    {
        for (const Edge& checkEdge : aFace.getEdges())
        {
            if (myEdge.isSimilar(checkEdge))
                return myEdge;
        }
    }
    throw std::runtime_error("These two Faces do not share an Edge");
}

