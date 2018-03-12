#ifndef OCCPRIMITIVE_H
#define OCCPRIMITIVE_H

#include <OccSolid.h>
#include <OccFace.h>
#include <OccEdge.h>
#include <OccTypes.h>

#include <map>

#include <TopoDS_Solid.hxx>

namespace Occ{
    class Primitive : public Occ::Solid
    {
        public:
            inline Primitive(const TopoDS_Solid aSolid);

            inline const Face& getNamedFace(const FaceName& which) const;

        protected:
            std::map<FaceName, Face> myNamedFaces;
    };

    Primitive::Primitive(TopoDS_Solid aSolid)
        : Solid(aSolid)
    {}

    const Face& Primitive::getNamedFace(const FaceName& which) const
    {
        return myNamedFaces.at(which);
    }
}

#endif /* OCCPRIMITIVE_H */
