#include <BRepPrimAPI_MakeBox.hxx>
#include <OccSolid.h>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>

int main(void)
{
    BRepPrimAPI_MakeBox mkBox(10, 10, 10);
    TopoDS_Shape aShape = mkBox.Shape();
    TopoDS_Solid aSolid = TopoDS::Solid(aShape);
    Occ::Solid myShape(aSolid);

    return 0;
}
