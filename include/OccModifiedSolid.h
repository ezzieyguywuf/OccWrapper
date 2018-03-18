#ifndef OCCMODIFIEDSOLID_H
#define OCCMODIFIEDSOLID_H

#include <OccSolid.h>
#include <OccBox.h>
#include <OccCylinder.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <map>
#include <vector>

#include <BRepAlgoAPI_BooleanOperation.hxx>

using Occ::uints;
using std::vector;
namespace Occ
{
    class ModifiedSolid
    {
        public:
            ModifiedSolid(Occ::Box origBox, Occ::Box newBox);
            ModifiedSolid(Occ::Cylinder origCyl, Occ::Cylinder newCyl);
            ModifiedSolid(Solid anOrigSolid, BRepAlgoAPI_BooleanOperation& anOperation);
            // This constructor takes _raw indices_ that maps faces from the original
            // solid to the new solid.
            //
            // throws std::runtime_error if each face in either solid is not accounted for
            ModifiedSolid(Solid origSolid,
                          Solid newSolid, 
                          map<uint, vector<uint>> modfiedFaces, 
                          uints deletedFaces, 
                          uints newFaces);

            bool operator==(const ModifiedSolid& aModifiedSolid) const;
            bool operator!=(const ModifiedSolid& aModifiedSolid) const;

            // returns the new Occ::Solid
            const Solid& getNewSolid() const;
            // return the original Occ::Solid
            const Solid& getOrigSolid() const;
            // Returns a vector of indices which correspond to faces in myNewSolid. These
            // faces represent modification(s) of aFace. The vector will be sorted using
            // std::sort.
            //
            // throws std::runtime_error if aFace is not in myOrigSolid
            vector<uint> getModifiedFaceIndices(const Occ::Face& aFace) const;
            // Checks whether or ont aFace was deleted.
            bool isDeleted(const Occ::Face& aFace) const;
            const vector<uint>& getNewFaceIndices() const;

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
            // map.at(i) = vector(j, k, etc...)
            std::map<uint, vector<uint>> modifiedFaces;
            // a vector of indices to myNewSolid.getFaces() which are generated faces
            uints newFaces;
            // a vector of indices to the myOrigSolid.getFaces() which have been deleted
            uints deletedFaces;

    };
}

#endif /* OCCMODIFIEDSOLID_H */
