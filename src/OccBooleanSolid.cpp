#include <OccBooleanSolid.h>

using Occ::BooleanSolid;

BooleanSolid::BooleanSolid(Occ::Solid aNewSolid, vector<Occ::ModifiedSolid> baseSolids)
    : Solid(aNewSolid), myBaseSolids(baseSolids)
{
    for (const Occ::ModifiedSolid& modSolid : baseSolids)
    {
        if (modSolid.getNewSolid() != *this)
        {
            throw std::runtime_error("Each Occ::ModifiedSolid MUST have a newSolid that is the asem as *this");
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
            if (modSolid.isModified(origFace))
            {
                uint k = modSolid.getModifiedFaceIndices().at(j);
                const Occ::Face& newFace = modSolid.getNewSolid().getFaces()[k];
                if (aFace == newFace)
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
