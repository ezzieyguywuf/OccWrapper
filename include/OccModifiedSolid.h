#ifndef OCCMODIFIEDSOLID_H
#define OCCMODIFIEDSOLID_H

#include <OccSolid.h>
#include <OccTypes.h>

using Occ::UintPairs;
using Occ::uints;
namespace Occ
{
    class ModifiedSolid
    {
        public:
            ModifiedSolid(Solid origSolid, Solid newSolid);

            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uint newSolidIndices);
            //void addNewFace(uint newSolidIndex);
            //void addNewFaces(uints newSolidIndices);
            //void addDeletedFace(uint origSolidIndex);
            //void addDeletedFaces(uint origSolidIndex);

        private:
            Solid origSolid;
            Solid newSolid;
            UintPairs modifiedFaceIndices;
            uints newFaceIndices;
            uints deletedFaceIndices;
    };
}

#endif /* OCCMODIFIEDSOLID_H */
