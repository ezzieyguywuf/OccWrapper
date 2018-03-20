#include <OccFaceComparator.h>
#include <OccSolidMaker.h>
#include <OccModifiedSolid.h>
#include <OccSolidModifier.h>
#include <OccBooleanSolid.h>
#include <OccTypes.h>

#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BinTools.hxx>

#include <iostream>

int main(void)
{
    Occ::Box box = Occ::SolidMaker::makeBox(10, 10, 10);
    Occ::Cylinder cyl = Occ::SolidMaker::makeCylinder(2.5, 10);
    BRepAlgoAPI_Cut mkCut(box.getShape(), cyl.getShape());
    Occ::Solid newSolid(mkCut.Shape());

    int i = 0;
    for (const Occ::Face& aFace : cyl.getFaces())
    {
        TopTools_ListOfShape modified = mkCut.Modified(aFace.getShape());
        TopTools_ListIteratorOfListOfShape iterator(modified);

        for(; iterator.More(); iterator.Next())
        {
            TopoDS_Face modifiedFace = TopoDS::Face(iterator.Value());
            std::cout << "face " << i << " in cyl had modified faces!"<< std::endl;
            std::cout << std::boolalpha;
            std::cout << "aFace == modifiedFace -> " << (aFace.getShape() == modifiedFace) << std::endl;
            BinTools::Write(modifiedFace, "modifiedCylSurface.brep");
            for (const Occ::Face& newFace : newSolid.getFaces())
            {
                if (aFace == newFace)
                {
                    std::cout << "Found aFace in newSolid!" << std::endl;
                }
            }
        }

        i++;
    }

    return 0;
}
