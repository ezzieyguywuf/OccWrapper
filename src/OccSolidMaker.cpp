#include <OccSolidMaker.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>


using Occ::SolidMaker;

Occ::Box SolidMaker::makeBox(double dx, double dy, double dz)
{
    return Occ::Box(BRepPrimAPI_MakeBox(dx, dy, dz));
}

Occ::Cylinder SolidMaker::makeCylinder(double rad, double height)
{
    return Occ::Cylinder(BRepPrimAPI_MakeCylinder(rad, height));
}

Occ::BooleanSolid SolidMaker::makeBoolean(BRepAlgoAPI_BooleanOperation& aBooleanOp)
{
    // Run the op
    aBooleanOp.Build();

    // Get the Base and Tool shapes, and create Occ::Solid's of them.
    Occ::Solid occBase(aBooleanOp.Shape1());
    Occ::Solid occTool(aBooleanOp.Shape2());

    // Create the Occ::ModifiedSolid for each
    Occ::ModifiedSolid modBase(occBase, aBooleanOp);
    Occ::ModifiedSolid modTool(occTool, aBooleanOp);

    // Finally, create the Occ::BooleanSolid and return
    Occ::Solid newSolid(aBooleanOp.Shape());
    return Occ::BooleanSolid(newSolid, {modBase, modTool});
}
