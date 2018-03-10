#include <OccSolidModifier.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <TopoDS.hxx>

using Occ::SolidModifier;

Occ::ModifiedSolids SolidModifier::makeFusion(const Occ::Solid& base, const Occ::Solid& tool)
{
    BRepAlgoAPI_Fuse mkFuse(base.getShape(), tool.getShape());
    ModifiedSolid modBase(base, mkFuse);
    ModifiedSolid modTool(tool, mkFuse);
    ModifiedSolids modSolids(Occ::Solid(TopoDS::Compound(mkFuse.Shape())));
    modSolids.addModifiedSolid(modBase);
    modSolids.addModifiedSolid(modTool);
    return modSolids;
}
