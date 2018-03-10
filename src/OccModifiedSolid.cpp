#include <OccModifiedSolid.h>

#include <utility> // for std::make_pair
#include <stdexcept>

using Occ::ModifiedSolid;

ModifiedSolid::ModifiedSolid(Solid origSolid, Solid newSolid);

void ModifiedSolid::addModifiedFace(uint origSolidIndex, uint newSolidIndex)
{
    modifiedFaceIndices.push_back(std::make_pair(origSolidIndex, newSolidIndex));
}

void ModifiedSolid::addModifiedFaces(uints origSolidIndices, uint newSolidIndices)
{
    if (origSolidIndices.size() != newSolidIndices.size())
    {
        throw std::value_error("Both vectors must be of the same length");
    }

    for (uint i = 0; i < origSolidIndices.size(); i++)
    {
        this->addModifiedFace(origSolidIndices[i], newSolidIndices[i]);
    }
}
