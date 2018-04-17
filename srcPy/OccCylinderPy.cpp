#include <pybind11/pybind11.h>
#include <OccCylinder.h>

namespace py = pybind11;

void init_OccCylinder(py::module& m)
{
    py::class_<Occ::Cylinder, Occ::Primitive>(m, "Cylinder")
        .doc() = "A Cylinder. As such, it has three faces. The "
        "OccWrapper.FaceNames enum can be\nused to access the "
        "following faces: top, bottom, left, right, front, back.";
}
