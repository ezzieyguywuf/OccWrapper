#include <pybind11/pybind11.h>
#include <OccFace.h>

namespace py = pybind11;

void init_OccFace(py::module& m)
{
    py::class_<Occ::Face, Occ::Shape>(m, "Face")
        .def("sharesEdge", &Occ::Face::sharesEdge, 
                py::arg("aFace"),
                py::doc("Checks whether self has a common OccWrapper.Edge with aFace"))
        .def("containsEdge", &Occ::Face::containsEdge,
                py::arg("anEdge"),
                py::doc("Checks whether self contains anEdge."))
        .doc() = "A topological Face. The underlying C++ code wraps a TopoDS_Face.";
}
