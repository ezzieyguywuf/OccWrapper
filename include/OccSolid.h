#ifndef OCCSOLID_H
#define OCCSOLID_H

#include <OccShape.h>
#include <OccFace.h>
#include <OccEdge.h>
#include <OccTypes.h>

#include <TopoDS_Solid.hxx>

namespace Occ{
    class Solid : public Shape
    {
        public:
            Solid(const TopoDS_Solid& aSolid);

            const Faces& getFaces() const;
            const Edges& getEdges() const;

        private:
            Faces myFaces;
            Edges myEdges;
    };

}

#endif /* OCCSOLID_H */
