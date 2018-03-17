#include <OccEdge.h>

#include <ShapeAnalysis_Edge.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS.hxx>

using Occ::Edge;

Edge::Edge(const TopoDS_Edge& aEdge)
    : Shape(aEdge)
{}

bool Edge::overlaps(const Occ::Edge& anEdge, double tolerance) const
{
    TopoDS_Edge myEdge = TopoDS::Edge(this->getShape());
    TopoDS_Edge checkEdge = TopoDS::Edge(anEdge.getShape());
    return ShapeAnalysis_Edge().CheckOverlapping(myEdge, checkEdge, tolerance);
}
