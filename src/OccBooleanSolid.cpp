#include <OccBooleanSolid.h>

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

pair<uint, uint> BooleanSolid::getConstituentFace(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::ModifiedSolid& modSolid : myBaseSolids)
    {
        uint j = 0;
        for (const Occ::Face& origFace : modSolid.getOrigSolid().getFaces())
        {
            for (const Occ::Face& checkFace : modSolid.getModifiedFaces(origFace))
            {
                if (checkFace == aFace)
                {
                   return {i, j}; 
                }
            }
            j++;
        }
        i++;
    }
    throw std::runtime_error("Was unable to find a constituent face.");
}
