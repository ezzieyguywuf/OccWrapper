#ifndef OCCSOLIDMODIFIER_H
#define OCCSOLIDMODIFIER_H

#include <OccSolid.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

namespace Occ
{
    class SolidModifier
    {
        public:
            virtual ~SolidModifier() = 0;

            static ModifiedSolids makeFusion(const Solid& base, const Solid& tool);
    };
}

#endif /* OCCSOLIDMODIFIER_H */
