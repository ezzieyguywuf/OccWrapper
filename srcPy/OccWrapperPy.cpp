#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void init_OccShape(py::module&);


PYBIND11_MODULE(OccWrapper, m)
{
    m.doc() = "A wrapper to open-cascade, available in Python.";
    init_OccShape(m);
}
