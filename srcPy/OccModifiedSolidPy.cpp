#include <pybind11/pybind11.h>
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
        modifiedFaces (dict): A dictionary of modified faces.
            The key corresponds to an index in origSolid.getFaces. The value
            corresponds to a list of indices in newSolid.getFaces. Each
            key-value pair represents a "to" relationship, such that for any
            key index `i` in origSolid.getFaces, each value index `j` in
            newSolid.getFaces is a modification of `i` "to" `j`.
)mydelimiter"))
//"    deletedFaces"
//"        list(int, int...)"
//"            Each value represents an index in origSolid.getFaces which points to"
//"            a face which was deleted"
//"    newFaces"
//"        list(int, int...)"
//"            Each value represents an index in newSolid.getFaces which points to"
//"            a face which is new. TODO: this will change."
        .doc() = "A ModifiedSolid is used for communication. It contains "
                 "information regarding a\ntopological update of a solid. This "
                 "information includes which Faces were\nmodified, which were "
                 "deleted, and which are new. It also maintains a copy of the\n"
                 "original un-modified solid, as well as the new modified solid"
        ;
}
