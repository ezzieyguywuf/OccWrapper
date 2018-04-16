include_directories(
    ${PYBIND11_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

AddLib(OccShapePy STATIC OccShape)

pybind11_add_module(OccWrapper OccWrapperPy.cpp)
target_link_libraries(OccWrapper PRIVATE 
    OccShapePy
)
