#ifndef OCCTYPES_H
#define OCCTYPES_H

#include <vector>
#include <map>
#include <utility> // for std::pair

using std::vector;
using std::pair;
using std::map;

namespace Occ{
    class Shape;
    class Solid;
    class Face;
    class Edge;

    using Faces = vector<Face>;
    using Edges = vector<Edge>;
    //using uint = unsigned int;
    //using UintPair = pair<uint, uint>;
    //using UintPairs = vector<UintPair>;
    //using MapUintPairs = map<uint, UintPairs>;
    
    enum class FaceName
    {
        top,
        bottom,
        left,
        right,
        front,
        back,
        lateral
    };
}
#endif /* ifndef OCCTYPES_H */
