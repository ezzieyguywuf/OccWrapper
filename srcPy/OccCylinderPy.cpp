#include "OccCylinderPy.h"

CylinderPyClass* init_OccCylinder(py::module& m)
{
    CylinderPyClass* cylClass = new CylinderPyClass(m, "Cylinder");
    cylClass->doc() = "A Cylinder. As such, it has three faces. The "
                      "OccWrapper.FaceNames enum can be\nused to access the "
                      "following faces: top, bottom, left, right, front, back.";
    return cylClass;
}
