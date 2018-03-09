#ifndef OCCFace_H
#define OCCFace_H

#include <OccShape.h>
#include <OccEdge.h>
#include <OccTypes.h>

#include <TopoDS_Face.hxx>

namespace Occ{
    class Face : public Shape
    {
        public:
            Face(const TopoDS_Face& aFace);
            const Edges& getEdges() const;

        private:
            Edges myEdges;
    };

}

#endif /* OCCFace_H */
