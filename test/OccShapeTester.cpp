#include <OccShape.h>
#include <OccBox.h>
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS.hxx>
#include <TopLoc_Location.hxx>
#include <Geom_Surface.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <BRep_Tool.hxx>
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

TEST(OccShape, translate)
{
    BRepPrimAPI_MakeBox mkBox1(10.0, 10.0, 10.0);
    Occ::Box myBox(mkBox1); 
    myBox.translate(5,5,5);
    gp_Trsf transform;
    gp_Pnt pnt(5,5,5);
    transform.SetTranslation(gp_Vec(5,5,5));
    EXPECT_TRUE(BRep_Tool::Surface(TopoDS::Face(myBox.getNamedFace(Occ::FaceName::bottom).getShape()))->Value(0,0).IsEqual(pnt, 0.00001));
}
