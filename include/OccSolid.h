#ifndef OCCSOLID_H
#define OCCSOLID_H

#include <OccShape.h>
#include <TopoDS_Solid.hxx>

namespace Occ{
    class Solid : public Shape
    {
        public:
            Solid(const TopoDS_Solid& aSolid);
    };

    Solid::Solid(const TopoDS_Solid& aSolid)
        : Shape(aSolid)
    {}
}

#endif /* OCCSOLID_H */
