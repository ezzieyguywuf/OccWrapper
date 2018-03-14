#ifndef OCCMODIFIEDSOLIDS_H
#define OCCMODIFIEDSOLIDS_H

#include <OccSolid.h>
#include <OccModifiedSolid.h>

#include <utility> // for std::pair
#include <vector>

using uint = unsigned int;

namespace Occ
{
    class ModifiedSolids
    {
        public:
            ModifiedSolids(Solid aNewSolid);

            void addModifiedSolid(ModifiedSolid aModifiedSolid);
            const std::vector<Occ::ModifiedSolid>& getModifiedSolids() const;

            // Finds which baseSolid, as well as which
            // baseSolid.getOrigSolid().getFaces(), produced the given aFace in
            // myNewSolid.getFaces(). The return value is a pair (i,j), in which i refers
            // to the index of the baseSolid and j refers to the face within that base
            // solid.
            //
            // throws std::runtime_error if aFace is not in myNewSolid
            std::pair<uint, uint> getConstituentFace(const Occ::Face& aFace) const;

            const Occ::Solid& getNewSolid() const;

        private:
            Solid myNewSolid;
            std::vector<Occ::ModifiedSolid> baseSolids;
    };
}

#endif /* OCCMODIFIEDSOLIDS_H */
