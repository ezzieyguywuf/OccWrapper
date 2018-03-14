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
            uint j = myOrigSolid.getFaceIndex(modifiedFace);
            this->addModifiedFace(i, j);
        }
        i++;
    }
}

bool ModifiedFace::isModified(const Occ::Face& aFace)
{
    for (const auto& data : modifiedFaceIndices)
    {
        const Occ::Face& origFace = this->myOrigSolid.getFaces()[data.first];
        if (origFace == aFace)
        {
            return true;
        }
    }
    return false;
}

const Occ::Face& ModifiedFace::getModifiedFace(const Occ::Face& aFace)
{
    for (const auto& data : modifiedFaceIndices)
    {
        const Occ::Face& origFace = this->myOrigSolid.getFaces()[data.first];
        if (origFace == aFace)
        {
            return this->myNewSolid.getFaces()[data.second];
        }
    }
    throw std::runtime_error("That face does not appear to have been modified.")
}

void ModifiedSolid::addModifiedFace(uint origSolidIndex, uint newSolidIndex)
{
    modifiedFaceIndices.emplace(origSolidIndex, newSolidIndex);
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

const Occ::Solid& ModifiedSolid::getNewSolid() const
{
    return myNewSolid;
}

const Occ::Solid& ModifiedSolid::getOrigSolid() const
{
    return myOrigSolid;
}

uint ModifiedSolid::getModifiedFaceIndex(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::Face& origFace : myOrigSolid.getFaces())
    {
        if (origFace == aFace)
        {
            return modifiedFaceIndices.at(i);
        }
        i++;
    }
    throw std::runtime_error("aFace is not found within myOrigSolid.");
}

const Occ::Face& ModifiedSolid::getModifiedFace(const Occ::Face& aFace) const
{
    return myNewSolid.getFaces()[this->getModifiedFaceIndex(aFace)];
}

const std::map<uint, uint>& ModifiedSolid::getModifiedFaceIndices() const
{
    return modifiedFaceIndices;
}

const uints& ModifiedSolid::getNewFaceIndices() const
{
    return newFaceIndices;
}

const uints& ModifiedSolid::getDeletedFaceIndices() const
{
    return deletedFaceIndices;
}
