#ifndef OCCMODIFIEDSOLID_H
#define OCCMODIFIEDSOLID_H

#include <OccSolid.h>
#include <OccBox.h>
#include <OccCylinder.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <map>

#include <BRepAlgoAPI_BooleanOperation.hxx>

using Occ::uints;
namespace Occ
{
    class ModifiedSolid
    {
        public:
            ModifiedSolid(Occ::Box origBox, Occ::Box newBox);
            ModifiedSolid(Occ::Cylinder origCyl, Occ::Cylinder newCyl);
            ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation);

            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uints newSolidIndices);
            //void addNewFace(uint newSolidIndex);
            //void addNewFaces(uints newSolidIndices);
            //void addDeletedFace(uint origSolidIndex);
            //void addDeletedFaces(uint origSolidIndex);

            const Solid& getNewSolid() const;
            const Solid& getOrigSolid() const;
            const std::map<uint, uint>& getModifiedFaceIndices() const;
            uint getModifiedFaceIndex(const Occ::Face& aFace) const;
            const Occ::Face& getModifiedFace(const Occ::Face& aFace) const;
            const uints& getNewFaceIndices() const;
            const uints& getDeletedFaceIndices() const;
        private:
            Solid myOrigSolid;
            Solid myNewSolid;
            std::map<uint, uint> modifiedFaceIndices;
            uints newFaceIndices;
            uints deletedFaceIndices;
    };
}

#endif /* OCCMODIFIEDSOLID_H */
