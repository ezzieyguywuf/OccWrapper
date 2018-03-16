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
            // TODO perhaps return a 'hint' that can be (optionally) passed to
            // getCommonEdge in order to so many loops?
            bool sharesEdge(const Face& aFace) const;
            bool containsEdge(const Edge& anEdge) const;
            // TOZDO perhaps allow an optional 'hint' that suggests which indices in
            // myEdges and aFace.getEdges() are common?
            const Edge& getCommonEdge(const Face& aFace) const;

        private:
            Edges myEdges;
    };

}

#endif /* OCCFace_H */
