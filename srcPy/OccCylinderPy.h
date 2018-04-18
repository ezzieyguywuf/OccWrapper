#ifndef OCCCYLINDERPY
#define OCCCYLINDERPY
#include <pybind11/pybind11.h>
#include <OccCylinder.h>

namespace py = pybind11;
using CylinderPyClass = py::class_<Occ::Cylinder, Occ::Primitive>;
#endif /* ifndef OCCCYLINDERPY */
