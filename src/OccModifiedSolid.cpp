#include <OccModifiedSolid.h>

#include <TopoDS_Face.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <utility> // for std::make_pair
#include <stdexcept>

using Occ::ModifiedSolid;

ModifiedSolid::ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation)
    : origSolid(anOrigSolid), newSolid(TopoDS::Compound(anOperation.Shape()))
{
    uint i = 0;
    for (const Occ::Face& occFace : origSolid.getFaces())
    {
        TopoDS_Face aFace = TopoDS::Face(occFace.getShape());
        TopTools_ListOfShape modified = anOperation.Modified(aFace);
        TopTools_ListIteratorOfListOfShape iterator(modified);

        for(; iterator.More(); iterator.Next())
        {
            TopoDS_Face modifiedFace = TopoDS::Face(iterator.Value());
            uint j = origSolid.getFaceIndex(modifiedFace);
            this->addModifiedFace(i, j);
        }
        i++;
    }
}

void ModifiedSolid::addModifiedFace(uint origSolidIndex, uint newSolidIndex)
{
    modifiedFaceIndices.push_back(std::make_pair(origSolidIndex, newSolidIndex));
}

void ModifiedSolid::addModifiedFaces(uints origSolidIndices, uints newSolidIndices)
{
    if (origSolidIndices.size() != newSolidIndices.size())
    {
        throw std::invalid_argument("Both vectors must be of the same length");
    }

    for (uint i = 0; i < origSolidIndices.size(); i++)
    {
        this->addModifiedFace(origSolidIndices[i], newSolidIndices[i]);
    }
}
