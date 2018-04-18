#include <pybind11/pybind11.h>
#include <OccBox.h>
//#include <OccSolidMaker.h>

namespace py = pybind11;

void init_OccBox(py::module& m)
{
    py::class_<Occ::Box, Occ::Primitive>(m, "Box")
        //.def(py::init(&Occ::SolidMaker::makeBox),
             //py::arg("dx"), py::arg("dy"), py::arg("dz"),
             //py::doc(R"pbdoc(
                //Create a box in the +x, +y, +z domain. One corner of the box
                //will be coincident with the origin, and each face will be
                //perpendicular to one of the primary planes.
             //)pbdoc"))
        .doc() = "A Box. As such, it has six faces. The OccWrapper.FaceNames "
                 "enum can be\nused to access the following faces: top, bottom, "
                 "left, right, front, back.";
}
