#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <OccSolid.h>

namespace py = pybind11;

void init_OccSolid(py::module& m)
{
    py::class_<Occ::Solid, Occ::Shape>(m, "Solid")
        .def("getFaces", &Occ::Solid::getFaces,
             py::doc("Returns a tuple containing all the OccWrapper.Face's in "
                     "this Solid."))
        .def("getEdges", &Occ::Solid::getEdges,
             py::doc("Returns a tuple containing all the OccWrapper.Edge's in "
                     "this Solid."))
        .def("getFaceIndex", &Occ::Solid::getFaceIndex,
             py::arg("aFace"),
             py::doc("Returns an index to the tuple returned by `getFaces`"
                     "corresponding to `aFace`."))
        .doc() = "A topological Solid. The underlying C++ code wraps a"
                 "TopoDS_Solid or a\nTopoDS_Compound.";
}
