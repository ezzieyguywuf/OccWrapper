#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void init_OccShape(py::module&);
void init_OccPrimitive(py::module&);
void init_OccEdge(py::module&);
void init_OccFace(py::module&);
void init_OccSolid(py::module&);
void init_OccBox(py::module&);
void init_OccCylinder(py::module&);
void init_OccModifiedSolid(py::module&);
void init_OccBooleanSolid(py::module&);
void init_OccSolidMaker(py::module&);

PYBIND11_MODULE(OccWrapper, m)
{
    m.doc() = R"pbdoc(
    OccWrapper
    ----------
    A wrapper to open-cascade, available in Python.
    
    This module is a python wrapper around the OccWrapper c++ library.
    OccWrapper is itself a wrapper around the OpenCasCade CAD kernel."
    )pbdoc";
    // note: the order here matters. a python class must be defined before it can be used
    // in another python class. Thus, OccShape must come before OccEdge must come before
    // OccFace, etc...
    init_OccShape(m);
    init_OccEdge(m);
    init_OccFace(m);
    init_OccSolid(m);
    init_OccPrimitive(m);
    init_OccBox(m);
    init_OccCylinder(m);
    init_OccModifiedSolid(m);
    init_OccBooleanSolid(m);
    //init_OccSolidMaker(m);
}
