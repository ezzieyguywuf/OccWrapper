#ifndef OCCMODIFIEDSOLIDS_H
#define OCCMODIFIEDSOLIDS_H

#include <OccSolid.h>
#include <OccModifiedSolid.h>

#include <vector>

namespace Occ
{
    class ModifiedSolids
    {
        public:
            ModifiedSolids(Solid aNewSolid);

            void addModifiedSolid(ModifiedSolid aModifiedSolid);
            const std::vector<Occ::ModifiedSolid>& getModifiedSolids() const;

            const Occ::Solid& getNewSolid() const;

        private:
            Solid myNewSolid;
            std::vector<Occ::ModifiedSolid> baseSolids;
    };
}

#endif /* OCCMODIFIEDSOLIDS_H */
