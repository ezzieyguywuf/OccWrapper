#ifndef OCCMODIFIEDSOLID_H
#define OCCMODIFIEDSOLID_H

#include <OccSolid.h>
#include <OccBox.h>
#include <OccCylinder.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <map>
#include <set>

#include <BRepAlgoAPI_BooleanOperation.hxx>

using Occ::uints;
using std::set;
namespace Occ
{
    class ModifiedSolid
    {
        public:
            ModifiedSolid(Occ::Box origBox, Occ::Box newBox);
            ModifiedSolid(Occ::Cylinder origCyl, Occ::Cylinder newCyl);
            ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation);

            // returns the new Occ::Solid
            const Solid& getNewSolid() const;
            // return the original Occ::Solid
            const Solid& getOrigSolid() const;
            // Returns a set of indices which correspond to faces in myNewSolid. These
            // faces represent modification(s) of aFace.
            //
            // throws std::runtime_error if aFace is not in myOrigSolid
            const set<uint>& getModifiedFaceIndices(const Occ::Face& aFace) const;
            // Checks whether or ont aFace was deleted.
            bool isDeleted(const Occ::Face& aFace) const;
            const set<uint>& getNewFaceIndices() const;

        private:
            uint getNewFaceIndex(const Occ::Face& aFace) const;
            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uints newSolidIndices);
            //void addNewFace(uint newSolidIndex);
            //void addNewFaces(uints newSolidIndices);
            //void addDeletedFace(uint origSolidIndex);
            //void addDeletedFaces(uint origSolidIndex);


            Solid myOrigSolid;
            Solid myNewSolid;
            // each face in myOrigSolid (i), can be modifieds into one or more faces in
            // myNewSolid (j, k, etc...). This is stored as:
            // map.at(i) = set(j, k, etc...)
            std::map<uint, set<uint>> modifiedFaces;
            // a set of indices to myNewSolid.getFaces() which are generated faces
            set<uint> newFaces;
            // a set of indices to the myOrigSolid.getFaces() which have been deleted
            set<uint> deletedFaces;

    };
}

#endif /* OCCMODIFIEDSOLID_H */
