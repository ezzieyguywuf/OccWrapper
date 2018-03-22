#ifndef OCCSOLID_H
#define OCCSOLID_H

#include <OccShape.h>
#include <OccFace.h>
#include <OccEdge.h>
#include <OccTypes.h>

#include <TopoDS_Solid.hxx>
#include <TopoDS_Compound.hxx>

#include <string>

using Occ::uint;

namespace Occ{
    class Solid : public Shape
    {
        public:
            Solid();
            Solid(const TopoDS_Shape& aShape);
            Solid(const TopoDS_Solid& aSolid);
            Solid(const TopoDS_Compound& aCompound);

            // rule of three
            Solid (const Solid& aSolid);
            Solid operator=(const Solid& aSolid);
            ~Solid() = default;

            const Faces& getFaces() const;
            const Edges& getEdges() const;
            uint getFaceIndex(const Occ::Face& aFace) const;
            // translate the TopoDS_Shape
            void translate(double dx, double dy, double dz);

        protected:
            void processFaces();
            void processEdges();

        private:
            Faces myFaces;
            Edges myEdges;
    };

}

#endif /* OCCSOLID_H */
