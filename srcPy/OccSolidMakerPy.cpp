#include <pybind11/pybind11.h>
#include <OccSolidMaker.h>

namespace py = pybind11;

void init_OccSolidMaker(py::module& m)
{
    py::class_<Occ::Box, Occ::Primitive>(m, "Box")
        .doc() = "A Box. As such, it has six faces. The OccWrapper.FaceNames "
                 "enum can be\nused to access the following faces: top, bottom, "
                 "left, right, front, back.";
    py::class_<Occ::Cylinder, Occ::Primitive>(m, "Cylinder")
        .doc() = "A Cylinder. As such, it has three faces. The "
        "OccWrapper.FaceNames enum can be\nused to access the "
        "following faces: top, bottom, left, right, front, back.";
    py::class_<Occ::SolidMaker>(m, "SolidMaker")
        .def("makeBox", &Occ::SolidMaker::makeBox, "Make a box")
        .def("makeCylinder", &Occ::SolidMaker::makeCylinder, "Make a cylinder");
}
