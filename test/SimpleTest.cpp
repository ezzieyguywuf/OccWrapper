#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    Occ::ModifiedSolid modifiedSolid(box, mkFuse);

    return 0;
}
