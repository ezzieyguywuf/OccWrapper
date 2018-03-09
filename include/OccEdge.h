#ifndef OCCEdge_H
#define OCCEdge_H

#include <OccShape.h>
#include <TopoDS_Edge.hxx>

namespace Occ{
    class Edge : public Shape
    {
        public:
            inline Edge(const TopoDS_Edge& aEdge);
    };

    Edge::Edge(const TopoDS_Edge& aEdge)
        : Shape(aEdge)
    {}
}

#endif /* OCCEdge_H */
