#ifndef OCCBOX_H
#define OCCBOX_H

#include <OccPrimitive.h>
#include <OccTypes.h>

#include <BRepPrimAPI_MakeBox.hxx>

namespace Occ{
    class Box : public Occ::Primitive
    {
        public:
            Box(BRepPrimAPI_MakeBox aMaker);
    };
}

#endif /* OCCBOX_H */
