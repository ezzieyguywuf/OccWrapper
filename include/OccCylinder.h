#ifndef OCCCylinder_H
#define OCCCylinder_H

#include <OccPrimitive.h>
#include <OccTypes.h>

#include <BRepPrimAPI_MakeCylinder.hxx>

namespace Occ{
    class Cylinder : public Occ::Primitive
    {
        public:
            Cylinder() = default;
            Cylinder(BRepPrimAPI_MakeCylinder aMaker);
    };
}

#endif /* OCCCylinder_H */
