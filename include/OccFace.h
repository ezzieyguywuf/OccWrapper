#ifndef OCCFace_H
#define OCCFace_H

#include <OccShape.h>
#include <TopoDS_Face.hxx>

namespace Occ{
    class Face : public Shape
    {
        public:
            inline Face(const TopoDS_Face& aFace);
    };

    Face::Face(const TopoDS_Face& aFace)
        : Shape(aFace)
    {}
}

#endif /* OCCFace_H */
