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

            // returns the new Occ::Solid
            const Solid& getNewSolid() const;
            // return the original Occ::Solid
            const Solid& getOrigSolid() const;
            // return the list of faces which aFace was modified into. Note that this
            // vector will be of length 0 if aFace was not modified at all.
            vector<Occ::Face> getModifiedFaces(const Occ::Face& aFace) const;
        private:
            // Given `aFace`, this method returns a key which can be used in the
            // modifiedFacesIndices to retrieve the face in the new solid which `aFace`
            // (from the original solid) corresponds to.
            //
            // throws std::runtime_error if aFace is not in myOrigSolid.
            const vector<uint>& getModifiedFaceIndices(const Occ::Face& aFace) const;
            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uints newSolidIndices);
            //void addNewFace(uint newSolidIndex);
            //void addNewFaces(uints newSolidIndices);
            //void addDeletedFace(uint origSolidIndex);
            //void addDeletedFaces(uint origSolidIndex);
            bool isDeleted(const Occ::Face& aFace) const;


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
