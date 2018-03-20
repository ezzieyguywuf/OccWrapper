#ifndef OCCSHAPE_H
#define OCCSHAPE_H

#include <TopoDS_Shape.hxx>
#include <vector>

using std::vector;
// TODO NOTE: make Occ::Shape a virtual templated base class (change namespace too). Then,
// you can define Occ::Shape which inherits this Other::Shape and implements operator  ==,
// operator !=, isSimilar, and getShape. Perhaps use curiously recurring template pattern?
// Probably won't need to...
//
// Next, Occ::Edge, Occ::Face etc. will also become templated. This will allow us to
// remove all Occ code from OccWrapper, which can be rechristened TopoWrapper.

namespace Occ{
    class Solid;
    class Shape
    {
        // For the Occ::Solid(TopoDS_Shape) constructor (needs access to myShape). Is
        // there a better way to do this?
        friend class Solid;
        public:
            Shape(const Shape& aShape);
            Shape operator=(const Shape& aShape);
            ~Shape() = default;

            bool operator==(const Shape& aShape) const;
            bool operator!=(const Shape& aShape) const;
            // Overlap, but different orientations.
            bool isSimilar(const Shape& aShape) const;
            bool isNull() const;

            TopoDS_Shape getShape() const;

        protected:
            Shape(TopoDS_Shape aShape);

        private:
            TopoDS_Shape myShape;
    };
}

#endif /* OCCSHAPE_H */
