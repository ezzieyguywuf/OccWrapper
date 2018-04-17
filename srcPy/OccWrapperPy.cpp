#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void init_OccShape(py::module&);
void init_OccPrimitive(py::module&);
void init_OccEdge(py::module&);
void init_OccSolidMaker(py::module&);

PYBIND11_MODULE(OccWrapper, m)
{
    m.doc() = "A wrapper to open-cascade, available in Python.";
    init_OccShape(m);
    init_OccEdge(m);
    init_OccPrimitive(m);
    //init_OccBox(m);
    init_OccSolidMaker(m);
}
