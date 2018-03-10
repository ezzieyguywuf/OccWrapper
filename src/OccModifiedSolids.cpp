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
