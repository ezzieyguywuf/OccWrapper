#include <OccShape.h>

using Occ::Shape;

Shape::Shape(TopoDS_Shape aShape)
    : myShape(aShape)
{}

Shape::Shape(const Shape& aShape)
    : myShape(aShape.myShape)
{}

bool Shape::operator==(const Shape& aShape) const
{
    return myShape.IsEqual(aShape.myShape);
}

bool Shape::operator!=(const Shape& aShape) const
{
    return not myShape.IsEqual(aShape.myShape);
}

bool Shape::isSimilar(const Shape& aShape) const
{
    return myShape.IsSame(aShape.myShape);
}
