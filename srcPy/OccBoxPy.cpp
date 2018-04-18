#include "OccBoxPy.h"

BoxPyClass* init_OccBox(py::module& m)
{
    BoxPyClass* boxClass = new BoxPyClass(m, "Box");
        //.def(py::init(&Occ::SolidMaker::makeBox),
             //py::arg("dx"), py::arg("dy"), py::arg("dz"),
             //py::doc(R"pbdoc(
                //Create a box in the +x, +y, +z domain. One corner of the box
                //will be coincident with the origin, and each face will be
                //perpendicular to one of the primary planes.
             //)pbdoc"))
    boxClass->doc() = "A Box. As such, it has six faces. The OccWrapper.FaceNames "
                      "enum can be\nused to access the following faces: top, bottom, "
                      "left, right, front, back.";
    return boxClass;
}
