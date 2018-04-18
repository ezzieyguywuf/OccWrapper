#include <pybind11/pybind11.h>
#include <OccCylinder.h>
#include <OccSolidMaker.h>

namespace py = pybind11;

void init_OccCylinder(py::module& m)
{
    py::class_<Occ::Cylinder, Occ::Primitive>(m, "Cylinder")
        //.def(py::init(&Occ::SolidMaker::makeCylinder),
             //py::arg("rad"), py::arg("height"),
             //py::doc(R"pbdoc(
                //Create a cylinder who's axis is coincident with the z-axis. This
                //cylinder will exist entirely in the +z domain.
             //)pbdoc"))
        .doc() = "A Cylinder. As such, it has three faces. The "
        "OccWrapper.FaceNames enum can be\nused to access the "
        "following faces: top, bottom, left, right, front, back.";
}
