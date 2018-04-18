#include <pybind11/pybind11.h>
#include <OccBooleanSolid.h>

#include <vector>

using std::vector;

namespace py = pybind11;

void init_OccBooleanSolid(py::module& m)
{
    py::class_<Occ::BooleanSolid, Occ::Solid>(m, "BooleanSolid")
        .def(py::init<Occ::Solid, vector<Occ::ModifiedSolid>>(),
             py::arg("aNewSolid"),
             py::arg("baseSolids"),
             py::doc(R"pbdoc(
                Args:
                    aNewSolid (OccWrapper.Solid) : The result of the boolean
                        operation
                    baseSolids (list[OccWrapper.ModifiedSolid]) : A list of all
                        the solids used to create `aNewSolid`. NOTE: the first
                        solid listed will be taken as the "base" solid, with all
                        subsequent solids used as "tool" solids.
             )pbdoc"))
        .def("getModifiedSolids", &Occ::BooleanSolid::getModifiedSolids,
             py::doc(R"pbdoc(
                Returns the list of `OccWrapper.ModifiedSolid`s which fully
                define the boolean operation which was used to generate this 
                solid.
                 )pbdoc"))
        .def("getConstituentFace", &Occ::BooleanSolid::getConstituentFace,
             py::arg("aFace"),
             py::doc(R"pbdoc(
                Finds which face was modified to create `aFace`.

                Args:
                    aFace (OccWrapper.Face) : A face in self.getFaces()

                Returns:
                    list : a list of three values representing the originating face.
                        The values `(i, j, k)` which are returned each represent
                        the following:

                            `i` = which myBaseSolid
                            `j` = which face with myBaseSolid.getFaces()
                            `k` = which face modified from `j`

                        These values can be used as follows:

                            >>> mod = myBooleanSolid.getModifiedSolids()[i]
                            >>> face = mod.getOrigSolid().getFaces()[j]
                            >>> x = mod.getModifiedFaceIndices(face)[k]
                            >>> targetFace = mod.getNewSolid().getFaces()[x]

                        In this example, `targetFace` would be equivilent to
                        `aFace` passed to the `getConstituentFace` method

             )pbdoc"))
        .doc() = "";
}
