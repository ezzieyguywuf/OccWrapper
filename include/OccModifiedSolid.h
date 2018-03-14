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

            // checks if aFace was modified
            bool isModified(const Occ::Face& aFace) const;
            //// checks if aFace was deleted
            //bool isDeleted(const Occ::Face& aFace) const;
            //// checks if aFace is a new face
            //bool isNew(const Occ::Face& aFace) const;
            // returns the Occ::Face which aFace was modified into.
            //
            // throws std::runtime_error if aFace is not in myOrigSolid or if it was not
            // modified into a face in myNewSolid.
            const Occ::Face& getModifiedFace(const Occ::Face& aFace) const;

            void addModifiedFace(uint origSolidIndex, uint newSolidIndex);
            void addModifiedFaces(uints origSolidIndices, uints newSolidIndices);
            //void addNewFace(uint newSolidIndex);
            //void addNewFaces(uints newSolidIndices);
            //void addDeletedFace(uint origSolidIndex);
            //void addDeletedFaces(uint origSolidIndex);

            // returns the new Occ::Solid
            const Solid& getNewSolid() const;
            // return the original Occ::Solid
            const Solid& getOrigSolid() const;
            // returns a map in which each key->value pair corresponds to an
            // OriginalSolidFace->NewSolidFace pair.
            const std::map<uint, uint>& getModifiedFaceIndices() const;
            // returns a vector of indices. Each of these indices represents a face in the
            // `myNewSolid.getFaces()` vector which is new.
            const uints& getNewFaceIndices() const;
            // returns vector of indices. Each of these indices represents a face in the
            // `myOrigSolid.getFaces()` vector which was deleted
            const uints& getDeletedFaceIndices() const;
        private:
            // Given `aFace`, this method returns a key which can be used in the
            // modifiedFacesIndices to retrieve the face in the new solid which `aFace`
            // (from the original solid) corresponds to.
            //
            // throws std::runtime_error if aFace is not in myOrigSolid.
            uint getModifiedFaceIndex(const Occ::Face& aFace) const;

            Solid myOrigSolid;
            Solid myNewSolid;
            // a map of key->value pair in which the key is an index to
            // myOrigSolid.getFaces() which corresponds to the value, which is a in index
            // to myNewSolid.getFaces()
            std::map<uint, uint> modifiedFaceIndices;
            // a vector of indices to myNewSolid.getFaces() which are generated faces
            uints newFaceIndices;
            // a vector of indices to the myOrigSolid.getFaces() which have been deleted
            uints deletedFaceIndices;

    };
}

#endif /* OCCMODIFIEDSOLID_H */
