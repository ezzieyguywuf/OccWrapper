#ifndef OCCPRIMITIVE_H
#define OCCPRIMITIVE_H

#include <OccSolid.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <map>

#include <TopoDS_Solid.hxx>

namespace Occ{
    class Primitive : public Occ::Solid
    {
        public:
            Primitive() = default;
            Primitive(const TopoDS_Solid aSolid);

            const Face& getNamedFace(const FaceName& which) const;

        protected:
            std::map<FaceName, uint> myNamedFaces;
    };
}

#endif /* OCCPRIMITIVE_H */
