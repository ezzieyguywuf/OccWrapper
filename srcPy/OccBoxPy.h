#ifndef OCCBOXPY
#define OCCBOXPY
#include <pybind11/pybind11.h>
#include <OccBox.h>

namespace py = pybind11;
using BoxPyClass = py::class_<Occ::Box, Occ::Primitive>;
#endif /* ifndef OCCBOXPY */
