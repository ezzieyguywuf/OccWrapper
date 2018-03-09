#ifndef OCCSHAPE_H
#define OCCSHAPE_H

#include <TopoDS_Shape.hxx>

namespace Occ{
    class Shape
    {
        public:
            Shape(TopoDS_Shape aShape);
            Shape(const Shape& aShape);
            ~Shape() = default;

            bool operator==(const Shape& aShape) const;
            bool operator!=(const Shape& aShape) const;
            bool isSimilar(const Shape& aShape) const;

        private:
            TopoDS_Shape myShape;
    };
}

#endif /* OCCSHAPE_H */
