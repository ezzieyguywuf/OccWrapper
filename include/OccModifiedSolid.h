#ifndef OCCMODIFIEDSOLID_H
#define OCCMODIFIEDSOLID_H

#include <OccSolid.h>
#include <OccTypes.h>

#include <BRepAlgoAPI_BooleanOperation.hxx>

using Occ::UintPairs;
using Occ::uints;
namespace Occ
{
    class ModifiedSolid
    {
        public:
            ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation);

            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uints newSolidIndices);
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
