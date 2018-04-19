#ifndef OCCSHAPEPY
#define OCCSHAPEPY
#include <pybind11/pybind11.h>
#include <OccShape.h>

namespace py = pybind11;

using ShapePyClass = py::class_<Occ::Shape>;
#endif /* ifndef OCCSHAPEPY */
