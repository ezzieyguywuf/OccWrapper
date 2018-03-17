#ifndef OCCEdge_H
#define OCCEdge_H

#include <OccShape.h>
#include <TopoDS_Edge.hxx>
#include <Precision.hxx>

namespace Occ{
    class Edge : public Shape
    {
        public:
            Edge(const TopoDS_Edge& aEdge);
            // Checks if a (potentially topologically distinct) anEdge geometrically
            // ovelaps with *this.
            bool overlaps(const Occ::Edge& anEdge, 
                          double tolerance=Precision::Confusion()) const;
    };

}

#endif /* OCCEdge_H */
