#ifndef OCCSOLID_H
#define OCCSOLID_H

#include <OccShape.h>
#include <OccFace.h>
#include <OccEdge.h>
#include <OccTypes.h>

#include <TopoDS_Solid.hxx>
#include <TopoDS_Compound.hxx>

using Occ::uint;

namespace Occ{
    class Solid : public Shape
    {
        public:
            Solid();
            Solid(const TopoDS_Shape& aShape);
            Solid(const TopoDS_Solid& aSolid);
            Solid(const TopoDS_Compound& aCompound);

            const Faces& getFaces() const;
            const Edges& getEdges() const;
            uint getFaceIndex(const Occ::Face& aFace) const;

        protected:
            void processFaces();
            void processEdges();

        private:
            Faces myFaces;
            Edges myEdges;
    };

}

#endif /* OCCSOLID_H */
