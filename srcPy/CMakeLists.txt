include_directories(
    ${PYBIND11_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)
add_library(OccShapePy STATIC OccShapePy.cpp)
target_link_libraries(OccShapePy OccShape)

#add_library(OccWrapperPy OccWrapperPy.cpp)
#target_link_libraries(OccWrapperPy OccShapePy)

pybind11_add_module(OccWrapperPy OccWrapperPy.cpp)
target_link_libraries(OccWrapperPy PRIVATE 
    OccShapePy
)
