#include <OccFaceComparator.h>
#include <OccSolidMaker.h>
#include <OccModifiedSolid.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    Occ::BooleanSolid fused = Occ::SolidModifier::makeFusion(box, cyl);

    const Occ::Face& top1 = fused.getFaces()[3];
    const Occ::Face& top2 = fused.getFaces()[7];

    auto v1 = fused.getConstituentFace(top1);
    auto v2 = fused.getConstituentFace(top2);

    std::cout << v1[0] << v2[0] << std::endl;

    return 0;
}
