#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <TopoDS_Face.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <algorithm> // for std::sort
#include <stdexcept>
#include <vector>

using Occ::ModifiedSolid;
using std::vector;

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
    : myOrigSolid(anOrigSolid), myNewSolid(anOperation.Shape())
{
    uint i = 0;
    for (const Occ::Face& occFace : myOrigSolid.getFaces())
    {
        // TODO do something with generated (i.e. new) faces.

        TopoDS_Face aFace = TopoDS::Face(occFace.getShape());
        
        if (anOperation.IsDeleted(aFace))
        {
            // if deleted, add to deletedFaces and move on to the next face
            deletedFaces.push_back(i);
            i++;
            continue;
        }

        TopTools_ListOfShape modified = anOperation.Modified(aFace);
        TopTools_ListIteratorOfListOfShape iterator(modified);

        for(; iterator.More(); iterator.Next())
        {
            TopoDS_Face modifiedFace = TopoDS::Face(iterator.Value());
            uint j = myNewSolid.getFaceIndex(modifiedFace);
            this->addModifiedFace(i, j);
        }

        if (modified.Extent() == 0)
        {
            // If not deleted or modified, then the face is the same in the new solid.
            // Despite being topologically equivalent, we must still treat it as modified
            // as it will likely have a new index.
            this->addModifiedFace(i, this->getNewFaceIndex(aFace));
            i++;
            continue;
        }
        i++;
    }
}

ModifiedSolid::ModifiedSolid(Solid origSolid,
                             Solid newSolid, 
                             map<uint, vector<uint>> newModifiedFaces, 
                             uints newdDeletedFaces, 
                             uints newNewFaces)
    : myOrigSolid(origSolid), myNewSolid(newSolid)
{

    const int size1 = origSolid.getFaces().size() - 1;
    const int size2 = newSolid.getFaces().size() - 1;

    vector<bool> checkOrig(size1, false);
    vector<bool> checkNew(size2, false);

    for (auto aPair : newModifiedFaces)
    {
        checkOrig[aPair.first] = true;
        for (uint i : aPair.second)
        {
            checkNew[i] = true;
            this->addModifiedFace(aPair.first, i);
        }

    }
    for (uint i : newdDeletedFaces)
    {
        if (i >= myOrigSolid.getFaces().size())
        {
            throw std::runtime_error("Index out of range for deletedFace");
        }
        checkOrig[i] = true;
        deletedFaces.push_back(i);
    }
    for (uint i : newNewFaces)
    {
        if (i >= myNewSolid.getFaces().size())
        {
            throw std::runtime_error("Index out of range for newFace");
        }
        checkNew[i] = true;
        newFaces.push_back(i);
    }
    if (std::find(checkOrig.begin(), checkOrig.end(), false) != checkOrig.end())
    {
        throw std::runtime_error("All faces in origSolid not accounted for");
    }

    if (std::find(checkNew.begin(), checkNew.end(), false) != checkNew.end())
    {
        throw std::runtime_error("All faces in NewSolid not accounted for");
    }
}

bool ModifiedSolid::operator==(const ModifiedSolid& aModifiedSolid) const
{
    if (myOrigSolid != aModifiedSolid.myOrigSolid)
        return false;
    if (myNewSolid != aModifiedSolid.myNewSolid)
        return false;
    if(modifiedFaces != aModifiedSolid.modifiedFaces)
        return false;
    if (newFaces != aModifiedSolid.newFaces)
        return false;
    if (deletedFaces != aModifiedSolid.deletedFaces)
        return false;
    return true;
}

bool ModifiedSolid::operator!=(const ModifiedSolid& aModifiedSolid) const
{
    return not ((*this) == aModifiedSolid);
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
        if (origFace.isSimilar(aFace))
        {
            return pair.second;
        }
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
    vector<uint>& myVec = modifiedFaces[origSolidIndex];
    myVec.push_back(newSolidIndex);
    std::sort(myVec.begin(), myVec.end());
}

//const Occ::Face& ModifiedSolid::getModifiedFace(const Occ::Face& aFace) const
//{
    //return myNewSolid.getFaces()[this->getModifiedFaceIndex(aFace)];
//}
