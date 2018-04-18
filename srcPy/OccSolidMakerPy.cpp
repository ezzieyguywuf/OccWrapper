#include <pybind11/pybind11.h>
#include <OccSolidMaker.h>

namespace py = pybind11;

void init_OccSolidMaker(py::module& m)
{
    py::class_<Occ::SolidMaker>(m, "SolidMaker")
        .def("makeBox", &Occ::SolidMaker::makeBox, "Make a box with one corner on the origin")
        .def("makeCylinder", &Occ::SolidMaker::makeCylinder, "Make a cylinder centered on the origin.");
        ;
}
