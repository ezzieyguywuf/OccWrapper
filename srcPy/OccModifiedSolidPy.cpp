#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <OccModifiedSolid.h>


#include <map>
#include <vector>

namespace py = pybind11;

using std::map;
using std::vector;
using uint = unsigned int;

void init_OccModifiedSolid(py::module& m)
{
    py::class_<Occ::ModifiedSolid>(m, "ModifiedSolid")
        .def(py::init<Occ::Box, Occ::Box>(),
             py::arg("origBox"), py::arg("newBox"),
             py::doc("Creates a ModifiedSolid tracking the changes from origBox "
                     "to newBox."))
        .def(py::init<Occ::Cylinder, Occ::Cylinder>(),
             py::arg("origCyl"), py::arg("newCyle"),
             py::doc("Creates a ModifiedSolid tracking the changes from origCyl "
                     "to newCyl."))
        .def(py::init<Occ::Solid, 
                      Occ::Solid, 
                      map<uint, vector<uint>>,
                      vector<uint>,
                      map<int, vector<uint>>>(),
             py::arg("origSolid"),
             py::arg("newSolid"), 
             py::arg("modifiedFaces"),
             py::arg("deletedFaces"),
             py::arg("newFaces"),
             py::doc(
R"mydelimiter(
    Creates a modified solid "from scratch".

    Creates a ModifiedSolid which maps the changes from origSolid to newSolid.
    Please note that _every_ face in both origSolid and newSolid _must_ be 
    accounted for in some way: it must either be modified, deleted, or new.

    Args:
        origSolid (OccWrapper.Solid): The original, un-modified solid
        newSolid (OccWrapper.Solid): The solid with `origSolid` was modified into.
        modifiedFaces (dict): A dictionary of modified faces.
            The key corresponds to an index in `origSolid.getFaces()`. The value
            corresponds to a list of indices in `newSolid.getFaces()`. Each
            key-value pair represents a "to" relationship, such that for any
            key index `i` in origSolid.getFaces, each value index `j` in
            `newSolid.getFaces()` is a modification of `i` "to" `j`.
        deletedFaces (list): A list of deleted faces.
            Each item in the list is an index that refers to an item in the
            `origSolid.getFaces()` list.
        newFaces (list): A list of new faces.
            Each item in the list is an index that refers to an item in the
            `newSolid.getFaces()` list.
)mydelimiter"))
        .def("__eq__", [](const Occ::ModifiedSolid& s1, const Occ::ModifiedSolid& s2){
                return s1 == s2;}, 
             py::is_operator(),
             py::arg("aModifiedSolid"),
             py::doc("Tests whether self and aModifiedSolid are equal."))
        .def("__ne__", [](const Occ::ModifiedSolid& s1, const Occ::ModifiedSolid& s2){
                return s1 != s2;}, py::is_operator())
        .def("getNewSolid", &Occ::ModifiedSolid::getNewSolid,
             py::doc("returns the new solid"))
        .def("getOrigSolid", &Occ::ModifiedSolid::getOrigSolid,
             py::doc("returns the original solid"))
        .def("getModifiedFaceIndices", &Occ::ModifiedSolid::getModifiedFaceIndices,
             py::arg("aFace"),
             py::doc(R"pbdoc(
                Returns a vector of indices which correspond to faces in the new
                solid. These faces represent modification(s) of `aFace`. The
                vector will be sorted.
             )pbdoc"))
        .def("isDeleted", &Occ::ModifiedSolid::isDeleted,
             py::arg("Face"),
             py::doc("Check if `aFace` was deleted"))
        .def("getNewFaceIndices", &Occ::ModifiedSolid::getNewFaceIndices,
             py::doc("Return the new faces"))
        .def("getNewFaceMap", &Occ::ModifiedSolid::getNewFaceMap,
             py::doc("returns the new faces"))
        .doc() = R"pbdoc(
        A ModifiedSolid is a helper class used for communication. It contains
        information regarding a topological update of a solid. This information
        includes which Faces were modified, which were deleted, and which are
        new. It also maintains a copy of the original un-modified solid, as well
        as the new modified solid)pbdoc"
        ;
}
