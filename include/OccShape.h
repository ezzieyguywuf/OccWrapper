#ifndef OCCSHAPE_H
#define OCCSHAPE_H

#include <TopoDS_Shape.hxx>
#include <vector>

using std::vector;

namespace Occ{
    class Shape
    {
        public:
            Shape(const Shape& aShape);
            Shape operator=(const Shape& aShape);
            ~Shape() = default;

            bool operator==(const Shape& aShape) const;
            bool operator!=(const Shape& aShape) const;
            // Overlap, but different orientations.
            bool isSimilar(const Shape& aShape) const;

        protected:
            Shape(TopoDS_Shape aShape);
            TopoDS_Shape getShape() const;

        private:
            TopoDS_Shape myShape;
    };
}

#endif /* OCCSHAPE_H */
