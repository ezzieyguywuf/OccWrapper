#ifndef OCCSOLIDMODIFIER_H
#define OCCSOLIDMODIFIER_H

#include <OccSolid.h>
#include <OccModifiedSolids.h>
#include <OccTypes.h>

namespace Occ
{
    class SolidModifier
    {
        public:
            virtual ~SolidModifier() = 0;

            static ModifiedSolids makeFusion(const Solid& base, const Solid& tool);
        private:
            SolidModifier() = default;
    };
}

#endif /* OCCSOLIDMODIFIER_H */
