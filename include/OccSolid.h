#ifndef OCCSOLID_H
#define OCCSOLID_H

#include <OccShape.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <TopoDS_Solid.hxx>

namespace Occ{
    class Solid : public Shape
    {
        public:
            Solid(const TopoDS_Solid& aSolid);

            const Faces& getFaces() const;

        private:
            Faces myFaces;
    };

}

#endif /* OCCSOLID_H */
