#ifndef OCCBooleanSolid_H
#define OCCBooleanSolid_H

#include <OccSolid.h>
#include <OccModifiedSolid.h>

#include <utility> // for std::pair
#include <vector>

using uint = unsigned int;

namespace Occ
{
    class BooleanSolid : public Occ::Solid
    {
        public:
            BooleanSolid(Solid aNewSolid, vector<ModifiedSolid> baseSolids);

            const std::vector<Occ::ModifiedSolid>& getModifiedSolids() const;

            // Finds which baseSolid, as well as which face in that baseSolid, produced
            // the given aFace in myBaseSolids.getNewSolid(). The return value is a pair (i,j),
            // in which i refers to the index of the baseSolid and j refers to the face
            // within that base solid.
            //
            // throws std::runtime_error if aFace is not in myNewSolid
            std::pair<uint, uint> getConstituentFace(const Occ::Face& aFace) const;

        private:
            std::vector<Occ::ModifiedSolid> myBaseSolids;
    };
}

#endif /* OCCBooleanSolid_H */
