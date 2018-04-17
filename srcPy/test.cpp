#include <pybind11/pybind11.h>

namespace py = pybind11;

class Pet {
    public:
        Pet(const std::string &name, int age) : name(name), age(age) { }

        void set(int age_) { age = age_; }
        void set(const std::string &name_) { name = name_; }
        void hello(int) const{};
        void hello(const std::string&) const{};

        std::string name;
        int age;
};

PYBIND11_MODULE(example_py, m)
{
    py::class_<Pet>(m, "Pet")
       .def(py::init<const std::string &, int>())
       .def("set", (void (Pet::*)(int)) &Pet::set, "Set the pet's age")
       .def("set",   (void (Pet::*)(const std::string &)) &Pet::set, "Set the pet's name")
       .def("hello", (void (Pet::*)(const std::string &) const) &Pet::hello, "do nothing.")
       ;
}
