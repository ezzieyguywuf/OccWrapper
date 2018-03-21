#include <OccBooleanSolid.h>

#include <TopoDS_Solid.hxx>

using Occ::BooleanSolid;

BooleanSolid::BooleanSolid(Occ::Solid aNewSolid, vector<Occ::ModifiedSolid> baseSolids)
    : Solid(aNewSolid), myBaseSolids(baseSolids)
{
    for (const Occ::ModifiedSolid& modSolid : baseSolids)
    {
        if (modSolid.getNewSolid() != *this)
        {
            throw std::runtime_error("Each Occ::ModifiedSolid MUST have a newSolid that is the same as *this");
        }
    }
}

const std::vector<Occ::ModifiedSolid>& BooleanSolid::getModifiedSolids() const
{
    return myBaseSolids;
}

array<uint, 3> BooleanSolid::getConstituentFace(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::ModifiedSolid& modSolid : myBaseSolids)
    {
        uint j = 0;
        for (const Occ::Face& origFace : modSolid.getOrigSolid().getFaces())
        {
            uint k = 0;
            for (uint index : modSolid.getModifiedFaceIndices(origFace))
            {
                const Occ::Face& checkFace = this->getFaces()[index];
                if (checkFace.isSimilar(aFace))
                {
                   return {i, j, k}; 
                }
                k++;
            }
            j++;
        }
        i++;
    }
    throw std::runtime_error("Was unable to find a constituent face.");
}
