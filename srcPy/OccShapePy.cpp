#include <pybind11/pybind11.h>
#include <OccShape.h>

namespace py = pybind11;

void init_OccShape(py::module& m)
{
    py::class_<Occ::Shape>(m, "Shape")
        .def(py::init([](Occ::Shape arg){
                    return Occ::Shape(arg);}));
}
