#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

int main(void)
{
    auto box = Occ::SolidMaker::makeBox(10, 10, 10);
    auto cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    Occ::ModifiedSolids modifiedSolids = Occ::SolidModifier::makeFusion(box, cyl);

    return 0;
}
