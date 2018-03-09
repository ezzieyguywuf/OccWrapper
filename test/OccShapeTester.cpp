#include <OccShape.h>
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS.hxx>
#include "gtest/gtest.h"

class MyShape : public Occ::Shape
{
    public:
        MyShape(TopoDS_Shape aShape)
            : Occ::Shape(aShape){};
};

TEST(OccShape, Equals){
    BRepPrimAPI_MakeBox mkBox1(10.0, 10.0, 10.0);
    BRepPrimAPI_MakeBox mkBox2(10.0, 10.0, 5.0);
    mkBox1.Build();
    mkBox2.Build();
    MyShape shape1(mkBox1.Shape());
    MyShape shape2(mkBox1.Shape());
    MyShape shape3(mkBox2.Shape());
    EXPECT_EQ(shape1, shape2);
    EXPECT_NE(shape1, shape3);
}
