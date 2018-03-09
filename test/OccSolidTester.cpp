#include <OccSolid.h>
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS.hxx>
#include "gtest/gtest.h"

TEST(OccShape, Equals){
    BRepPrimAPI_MakeBox mkBox1(10.0, 10.0, 10.0);
    BRepPrimAPI_MakeBox mkBox2(10.0, 10.0, 10.0);
    mkBox1.Build();
    mkBox2.Build();
    Occ::Solid shape1(TopoDS::Solid(mkBox1.Shape()));
    Occ::Solid shape2(TopoDS::Solid(mkBox1.Shape()));
    Occ::Solid shape3(TopoDS::Solid(mkBox2.Shape()));
    EXPECT_EQ(shape1, shape2);
    EXPECT_NE(shape1, shape3);
}
