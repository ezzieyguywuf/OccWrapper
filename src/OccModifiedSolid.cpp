#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <TopoDS_Face.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <utility> // for std::make_pair
#include <stdexcept>

using Occ::ModifiedSolid;

ModifiedSolid::ModifiedSolid(Occ::Box origBox, Occ::Box newBox)
    : myOrigSolid(origBox), myNewSolid(newBox)
{
    std::vector<Occ::FaceName> FaceNames = {
        Occ::FaceName::top,
        Occ::FaceName::bottom,
        Occ::FaceName::left,
        Occ::FaceName::right,
        Occ::FaceName::front,
        Occ::FaceName::back };
    for (const Occ::FaceName& faceName : FaceNames)
    {
        this->addModifiedFace(origBox.getFaceIndex(origBox.getNamedFace(faceName)),
                              newBox.getFaceIndex(newBox.getNamedFace(faceName)));
    }
}

ModifiedSolid::ModifiedSolid(Occ::Cylinder origCyl, Occ::Cylinder newCyl)
    : myOrigSolid(origCyl), myNewSolid(newCyl)
{
    std::vector<Occ::FaceName> FaceNames = {
        Occ::FaceName::top,
        Occ::FaceName::bottom,
        Occ::FaceName::lateral};
    for (const Occ::FaceName& faceName : FaceNames)
    {
        this->addModifiedFace(origCyl.getFaceIndex(origCyl.getNamedFace(faceName)),
                              newCyl.getFaceIndex(newCyl.getNamedFace(faceName)));
    }
}


ModifiedSolid::ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation)
    : myOrigSolid(anOrigSolid), myNewSolid(TopoDS::Compound(anOperation.Shape()))
{
    uint i = 0;
    for (const Occ::Face& occFace : myOrigSolid.getFaces())
    {
        TopoDS_Face aFace = TopoDS::Face(occFace.getShape());
        TopTools_ListOfShape modified = anOperation.Modified(aFace);
        TopTools_ListIteratorOfListOfShape iterator(modified);

        for(; iterator.More(); iterator.Next())
        {
            TopoDS_Face modifiedFace = TopoDS::Face(iterator.Value());
            uint j = myNewSolid.getFaceIndex(modifiedFace);
            this->addModifiedFace(i, j);
        }
        i++;
    }
}

const Occ::Solid& ModifiedSolid::getNewSolid() const
{
    return myNewSolid;
}

const Occ::Solid& ModifiedSolid::getOrigSolid() const
{
    return myOrigSolid;
}

vector<uint> ModifiedSolid::getModifiedFaceIndices(const Occ::Face& aFace) const
{
    for (const auto& pair : modifiedFaces)
    {
        const Occ::Face& origFace = myOrigSolid.getFaces().at(pair.first);
        if (origFace == aFace)
        {
            return pair.second;
        }
    }

    // If the face was not modified nor was it deleted, then it must have remained
    // unchanged. We'll find the new index and return that.
    if (not (this->isDeleted(aFace)))
    {
        return {this->getNewFaceIndex(aFace)};
    }
    throw std::runtime_error("Face was not modified or deleted, and yet I was unable to find it.");
}

bool ModifiedSolid::isDeleted(const Occ::Face& aFace) const
{
    for (uint i : deletedFaces)
    {
        const Occ::Face& checkFace = myOrigSolid.getFaces()[i];
        if (aFace == checkFace)
        {
            return true;
        }
    }
    return false;
}

const vector<uint>& ModifiedSolid::getNewFaceIndices() const
{
    return newFaces;
}
//--------------------------------------------------
//----- Private Methods ----------------------------
//--------------------------------------------------

uint ModifiedSolid::getNewFaceIndex(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::Face& newFace : myNewSolid.getFaces())
    {
        if (aFace == newFace)
        {
            return i;
        }
        i++;
    }
    throw std::runtime_error("aFace does not appear in myNewSolid.");
}

void ModifiedSolid::addModifiedFace(uint origSolidIndex, uint newSolidIndex)
{
    modifiedFaces[origSolidIndex].push_back(newSolidIndex);
}

//const Occ::Face& ModifiedSolid::getModifiedFace(const Occ::Face& aFace) const
//{
    //return myNewSolid.getFaces()[this->getModifiedFaceIndex(aFace)];
//}
