#include <pybind11/pybind11.h>
#include <OccSolidMaker.h>
#include "OccBoxPy.h"
#include "OccCylinderPy.h"

namespace py = pybind11;

void init_OccSolidMaker(py::module& m, BoxPyClass* boxClass, CylinderPyClass* cylClass)
{
    py::class_<Occ::SolidMaker>(m, "SolidMaker")
        .def("makeBox", &Occ::SolidMaker::makeBox, "Make a box with one corner on the origin")
        .def("makeCylinder", &Occ::SolidMaker::makeCylinder, "Make a cylinder centered on the origin.");
        ;
    //py::object box = (py::object) py::module::import("OccWrapper").attr("Box");
    boxClass->def(py::init(&Occ::SolidMaker::makeBox),
              py::arg("dx"), py::arg("dy"), py::arg("dz"),
              py::doc(R"pbdoc(
                 Create a box in the +x, +y, +z domain. One corner of the box
                 will be coincident with the origin, and each face will be
                 perpendicular to one of the primary planes.
              )pbdoc"))
        ;
    cylClass->def(py::init(&Occ::SolidMaker::makeCylinder),
              py::arg("rad"), py::arg("height"),
              py::doc(R"pbdoc(
                  Create a cylinder who's axis is coincident with the z-axis. This
                  cylinder will exist entirely in the +z domain.
              )pbdoc"))
        ;
}
