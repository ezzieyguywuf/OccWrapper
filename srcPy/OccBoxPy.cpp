#include <pybind11/pybind11.h>
#include <OccBox.h>

namespace py = pybind11;

void init_OccBox(py::module& m)
{
    py::class_<Occ::Box, Occ::Primitive>(m, "Box")
        .doc() = "A Box. As such, it has six faces. The OccWrapper.FaceNames "
                 "enum can be\nused to access the following faces: top, bottom, "
                 "left, right, front, back.";
}
