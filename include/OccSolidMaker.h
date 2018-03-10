#ifndef OCCSOLIDMAKER_H
#define OCCSOLIDMAKER_H

#include <OccBox.h>
#include <OccCylinder.h>

namespace Occ{
    class SolidMaker
    {
        public:
            static Occ::Box makeBox(double dx, double dy, double dz);
            static Occ::Cylinder makeCylinder(double rad, double height);

        private:
            SolidMaker() = default;
    };
}

#endif /* OCCSOLIDMAKER_H */
