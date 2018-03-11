#include <PrimitiveSolidManager.h>

#include <iostream>

PrimitiveSolidManager::PrimitiveSolidManager(Occ::Solid aSolid)
    : mySolid(aSolid)
{
    for (uint i = 0; i < mySolid.getFaces().size(); i++)
    {
        mappedFaces.emplace(i, i);
    }

    std::vector<uint> foundFaces;
    for (uint i = 0; i < mySolid.getEdges().size(); i++)
    {
        foundFaces.clear();
        const Occ::Edge& myEdge = mySolid.getEdges()[i];
        for (const auto& face : mappedFaces)
        {
            const Occ::Face& checkFace = mySolid.getFaces()[face.first];
            for (uint j = 0; j < checkFace.getEdges().size() ; j++)
            {
                const Occ::Edge& checkEdge = checkFace.getEdges()[j];
                if (myEdge.isSimilar(checkEdge))
                {
                    foundFaces.push_back(face.first);
                }
            }
        }

        if (foundFaces.size() == 0)
        {
            throw std::runtime_error("Did not find two faces for this Edge");
        }
        else if (foundFaces.size() == 1)
        {
            // TODO: do something with seam edges?
            std::clog << "Warning: Only one Edge found. Doing nothing. (is this a seam edge?)";
        }
        else if (foundFaces.size() > 2)
        {
            throw std::runtime_error("Found more than two faces that share this Edge.");
        }
        mappedEdges.emplace(mappedEdges.size() - 1, std::make_pair(foundFaces[0], foundFaces[1]));
    }
}

uint PrimitiveSolidManager::getEdgeIndex(const Occ::Edge anEdge) const
{
    for (const auto& data : mappedEdges)
    {
        if (anEdge.isSimilar(this->getEdgeByIndex(data.first)))
        {
            return data.first;
        }
    }
    throw std::runtime_error("Was unable to find anEdge in mySolid.");
}

uint PrimitiveSolidManager::getFaceIndex(const Occ::Face aFace) const
{
    for (const auto& data : mappedFaces)
    {
        if (aFace == mySolid.getFaces()[data.second])
        {
            return data.first;
        }
    }
    throw std::runtime_error("That face is not not in mySolid");
}

Occ::Edge PrimitiveSolidManager::getEdgeByIndex(uint i) const
{
    const Occ::Face& face1 = mySolid.getFaces()[mappedEdges.at(i).first];
    const Occ::Face& face2 = mySolid.getFaces()[mappedEdges.at(i).second];
    for (const auto& edge1 : face1.getEdges())
    {
        for (const auto& edge2 : face2.getEdges())
        {
            if (edge1.isSimilar(edge2))
            {
                return edge1;
            }
        }
    }
    throw std::runtime_error("That edge does not appear to be in mySolid");
}

Occ::Face PrimitiveSolidManager::getFaceByIndex(uint i) const
{
    return mySolid.getFaces()[mappedFaces.at(i)];
}
