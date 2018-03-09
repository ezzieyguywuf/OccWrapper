#ifndef OCCTYPES_H
#define OCCTYPES_H

#include <BKALTypes.h>
#include <vector>
#include <map>
#include <utility> // for std::pair

using BKAL::uint;
using BKAL::uints;
using std::vector;
using std::pair;
using std::map;

namespace Occ{
    using UintPair = pair<uint, uint>;
    using UintPairs = vector<UintPair>;
    using MapUintPairs = map<uint, UintPairs>;
}
#endif /* ifndef OCCTYPES_H */
