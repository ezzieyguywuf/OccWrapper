#ifndef OCCSOLIDMAKER_H
#define OCCSOLIDMAKER_H

#include <OccBox.h>
#include <OccCylinder.h>
#include <OccBooleanSolid.h>
#include <BRepAlgoAPI_BooleanOperation.hxx>

namespace Occ{
    class SolidMaker
    {
        public:
            static Occ::Box makeBox(double dx, double dy, double dz);
            static Occ::Cylinder makeCylinder(double rad, double height);
            static Occ::BooleanSolid makeBoolean(BRepAlgoAPI_BooleanOperation& aBooleanOp);

        private:
            SolidMaker() = default;
    };
}

#endif /* OCCSOLIDMAKER_H */
