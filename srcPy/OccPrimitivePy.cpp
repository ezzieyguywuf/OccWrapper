#include <pybind11/pybind11.h>
#include <OccShape.h>
#include <OccPrimitive.h>

namespace py = pybind11;

void init_OccPrimitive(py::module& m)
{
    py::enum_<Occ::FaceName>(m, "FaceName")
        .value("top", Occ::FaceName::top)
        .value("bottom", Occ::FaceName::bottom)
        .value("left", Occ::FaceName::left)
        .value("right", Occ::FaceName::right)
        .value("front", Occ::FaceName::front)
        .value("back", Occ::FaceName::back)
        .value("lateral", Occ::FaceName::lateral);
    py::class_<Occ::Primitive, Occ::Shape>(m, "Primitive")
        .def("getNamedFace", &Occ::Primitive::getNamedFace, "Get the face of a primitive by name.")
        .doc() = "A primitive solid. This is a pure virtual base class, and as " 
                 "such cannot be\n instantiated on its own.";
}
