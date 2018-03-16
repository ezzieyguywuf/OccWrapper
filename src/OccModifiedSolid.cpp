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

set<Occ::Face, Occ::FaceComparator> ModifiedSolid::getModifiedFaces(const Occ::Face& aFace) const
{
    for (const auto& vals : modifiedFaces)
    {
        const Occ::Face& checkFace = myOrigSolid.getFaces()[vals.first];
        if (checkFace == aFace)
        {
            set<Occ::Face, Occ::FaceComparator> outFaces;
            for (uint i : vals.second)
            {
                outFaces.insert(myNewSolid.getFaces()[i]);
            }
            return outFaces;
        }
    }
    if (not (this->isDeleted(aFace)))
    {
        return {aFace};
    }
    return {};
}

//--------------------------------------------------
//----- Private Methods ----------------------------
//--------------------------------------------------

void ModifiedSolid::addModifiedFace(uint origSolidIndex, uint newSolidIndex)
{
    modifiedFaces[origSolidIndex].push_back(newSolidIndex);
}

const vector<uint>& ModifiedSolid::getModifiedFaceIndices(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::Face& origFace : myOrigSolid.getFaces())
    {
        if (origFace == aFace)
        {
            return modifiedFaces.at(i);
        }
        i++;
    }
    throw std::runtime_error("aFace is not found within myOrigSolid.");
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

//const Occ::Face& ModifiedSolid::getModifiedFace(const Occ::Face& aFace) const
//{
    //return myNewSolid.getFaces()[this->getModifiedFaceIndex(aFace)];
//}
