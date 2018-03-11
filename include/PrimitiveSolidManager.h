#ifndef PRIMITIVESOLIDMANAGER_H
#define PRIMITIVESOLIDMANAGER_H

#include <OccSolid.h>
#include <OccFace.h>
#include <OccEdge.h>

#include <map>
#include <utility>

using std::map;
using std::pair;
using uint = unsigned int;

class PrimitiveSolidManager
{
    public:
        PrimitiveSolidManager(Occ::Solid aSolid);
        uint getEdgeIndex(const Occ::Edge anEdge) const;
        uint getFaceIndex(const Occ::Face aFace) const;
        Occ::Edge getEdgeByIndex(uint i) const;
        Occ::Face getFaceByIndex(uint i) const;

    private:
        Occ::Solid mySolid;
        // A map in which the key will always point to the same face in mySolid.getFaces()
        // This is done by updating the value associated with each key any time the
        // underlying solid is modified
        map<uint, uint> mappedFaces;
        // A map in which the key will always refer to the same edge in
        // mySolid.getEdges(). This is done by identifying each edge by the two faces that
        // make it up. Therefore, in order to identify an edge, we simply keep track of
        // each face.
        map<uint, pair<uint, uint>> mappedEdges;
};

#endif /* PRIMITIVESOLIDMANAGER_H */
