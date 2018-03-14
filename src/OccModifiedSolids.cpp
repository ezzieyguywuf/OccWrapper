#include <OccModifiedSolids.h>

using Occ::ModifiedSolids;

ModifiedSolids::ModifiedSolids(Occ::Solid aNewSolid)
    : myNewSolid(aNewSolid)
{}

void ModifiedSolids::addModifiedSolid(ModifiedSolid aModifiedSolid)
{
    if (baseSolids.size() > 0)
    {
        if (baseSolids[0].getNewSolid() != myNewSolid)
        {
            throw std::invalid_argument("Must have the same newSolid as `this`");
        }
    }
    baseSolids.push_back(aModifiedSolid);
}

const std::vector<Occ::ModifiedSolid>& ModifiedSolids::getModifiedSolids() const
{
    return baseSolids;
}

const Occ::Solid& ModifiedSolids::getNewSolid() const
{
    return myNewSolid;
}

pair<uint, uint> ModifiedSolids::getConstituentFace(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::ModifiedSolid& modSolid : baseSolids)
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
