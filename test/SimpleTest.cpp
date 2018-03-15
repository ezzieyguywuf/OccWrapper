#include <OccSolidMaker.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Fuse mkFuse(box.getShape(), cyl.getShape());
    mkFuse.Build();

    Occ::ModifiedSolid modifiedSolid(box, mkFuse);
    std::cout << "len of modifiedSolid.getOrigSolid().getFaces() = ";
    std::cout << modifiedSolid.getOrigSolid().getFaces().size() << std::endl;

    std::cout << std::boolalpha;
    std::cout << "front = new[2] -> " << (box.getNamedFace(Occ::FaceName::top) == modifiedSolid.getNewSolid().getFaces()[1]) << std::endl;

    Occ::Solid newSolid = modifiedSolid.getNewSolid();

    int i = 0;
    for (const auto& aFace : newSolid.getFaces())
    {
        std::cout << "For new face[" << i << "], (x,y,z) = (";
        const auto& surf = BRep_Tool::Surface(TopoDS::Face(aFace.getShape()));
        const auto& pt = surf->Value(0.1,0.1);
        std::cout << pt.X() << "," << pt.Y() << "," << pt.Z();
        std::cout << ")" << std::endl;
        i++;
    }

    i = 0;
    for (const auto& aFace : modifiedSolid.getOrigSolid().getFaces())
    {
        std::cout << "For orig face[" << i << "], (x,y,z) = (";
        const auto& surf = BRep_Tool::Surface(TopoDS::Face(aFace.getShape()));
        const auto& pt = surf->Value(0.1,0.1);
        std::cout << pt.X() << "," << pt.Y() << "," << pt.Z();
        std::cout << ")" << std::endl;
        i++;
    }

    std::cout << "frontFace == newFaces[2] -->";
    std::cout << (box.getNamedFace(Occ::FaceName::front) == newSolid.getFaces()[2]) << std::endl;

    return 0;
}
