#include <pybind11/pybind11.h>
#include <OccSolidModifier.h>
#include "OccShapePy.h"

namespace py = pybind11;

void init_OccSolidModifier(py::module& m, ShapePyClass* shapeClass)
{
    py::class_<Occ::SolidModifier>(m, "SolidModifier")
        .def("makeFusion", 
             &Occ::SolidModifier::makeFusion,
             "Create a fusion")
        .doc() = "Used to modify an OccWrapper.Solid, typically using a boolean operation";

    shapeClass
        ->def("fuse", &Occ::SolidModifier::makeFusion,
              //py::arg("base"), py::arg("tool"),
              py::doc("Create a fusion of two Shape's"));
}
