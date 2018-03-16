#ifndef OCCBooleanSolid_H
#define OCCBooleanSolid_H

#include <OccSolid.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <utility> // for std::pair
#include <array>

using Occ::uint;
using std::array;

namespace Occ
{
    class BooleanSolid : public Occ::Solid
    {
        public:
            BooleanSolid(Solid aNewSolid, vector<ModifiedSolid> baseSolids);

            const std::vector<Occ::ModifiedSolid>& getModifiedSolids() const;

            // Finds which face was modified to create aFace. The return value is a
            // triplet (i, j, k) which designates whwere aFace originated:
            //     i = which myBaseSolid
            //     j = which face within myBaseSolid[i]
            //     k = which face originating form j
            //
            // These values can be used as follows to retrieve aFace:
            //
            //     auto mod = getModifiedSolids()[i];
            //     auto face = mod.getOrigSolid().getFaces()[j];
            //     uint x = mod.getModifiedFaceIndices(face)[k];
            //     Occ::Face aFace = mod.getNewSolid().getFaces()[x];
            //
            // throws std::runtime_error if aFace is not in myNewSolid
            array<uint, 3> getConstituentFace(const Occ::Face& aFace) const;

        private:
            std::vector<Occ::ModifiedSolid> myBaseSolids;
    };
}

#endif /* OCCBooleanSolid_H */
