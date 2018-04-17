#include <OccPrimitive.h>

using Occ::Primitive;
using Occ::Face;
using Occ::Solid;

Primitive::Primitive(TopoDS_Solid aSolid)
    : Solid(aSolid)
{}

const Face& Primitive::getNamedFace(const FaceName& which) const
{
    return Solid::getFaces()[myNamedFaces.at(which)];
}
