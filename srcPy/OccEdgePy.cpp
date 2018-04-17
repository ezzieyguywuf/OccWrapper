#include <pybind11/pybind11.h>
#include <OccEdge.h>
#include <Precision.hxx>

namespace py = pybind11;

void init_OccEdge(py::module& m)
{
    py::class_<Occ::Edge, Occ::Shape>(m, "Edge")
        .def("overlaps", &Occ::Edge::overlaps, 
             py::arg("anEdge"), py::arg("tolerance") = Precision::Confusion(),
             py::doc("Checks if a (topologically distinct) anEdge "
                 "geometrically overlaps with self"));
}
