#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <OccShape.h>

namespace py = pybind11;

void init_OccShape(py::module& m)
{
    py::class_<Occ::Shape>(m, "Shape")
        .def(py::init([](Occ::Shape arg){
                    return Occ::Shape(arg);}))
        .def("__eq__", [](const Occ::Shape& s1, const Occ::Shape& s2){
                return s1 == s2;}, 
             py::is_operator(),
             py::arg("aShape"),
             py::doc("Tests whether self and aShape are topologically"
                 "equivalent. Uses\nTopoDS_Shape::IsEqual method from OpenCasCade"))
        .def("__ne__", [](const Occ::Shape& s1, const Occ::Shape& s2){
                return s1 != s2;}, py::is_operator())
        .def("isSimilar", &Occ::Shape::isSimilar,
             py::arg("aShape"),
             py::doc("Tests whether self and aShape are topologically"
                 "similar. Uses\nTopoDS:Shape::IsSimilar method from OpenCasCade."))
        .def("isNull", &Occ::Shape::isNull,
             py::doc("Returns true if the Shape is null, i.e. is managing nullptr"))
        .def("translate", &Occ::Shape::translate,
             py::arg("dx"), py::arg("dy"), py::arg("dz"),
             py::doc("Translate the shape (i.e. move it)."))
        .def("writeFile", 
             (void (Occ::Shape::*)(const char*) const) &Occ::Shape::writeFile,
             py::arg("filename"),
             py::doc("Writes the Shape to a file, using the OpenCasCade brep "
                 "file format."))
        ;
}
