#include <pybind11/pybind11.h>
#include <iostream>

#include "OccShapePy.h"
#include "OccBoxPy.h"
#include "OccCylinderPy.h"

ShapePyClass* init_OccShape(py::module&);
void init_OccPrimitive(py::module&);
void init_OccEdge(py::module&);
void init_OccFace(py::module&);
void init_OccSolid(py::module&);
BoxPyClass* init_OccBox(py::module&);
CylinderPyClass* init_OccCylinder(py::module&);
void init_OccModifiedSolid(py::module&);
void init_OccBooleanSolid(py::module&);
void init_OccSolidMaker(py::module&, BoxPyClass*, CylinderPyClass*);

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
    ShapePyClass* shapeClass = init_OccShape(m);
    init_OccEdge(m);
    init_OccFace(m);
    init_OccSolid(m);
    init_OccPrimitive(m);
    BoxPyClass* boxClass = init_OccBox(m);
    CylinderPyClass* cylClass = init_OccCylinder(m);
    init_OccModifiedSolid(m);
    init_OccBooleanSolid(m);
    init_OccSolidMaker(m, boxClass, cylClass);
    delete(shapeClass);
    delete(boxClass);
    delete(cylClass);
}
