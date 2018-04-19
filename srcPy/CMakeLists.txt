include_directories(
    ${PYBIND11_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

AddPyLib(OccShapePy OccShape)
AddPyLib(OccEdgePy OccEdge OccShapePy)
AddPyLib(OccFacePy OccFace OccEdgePy)
AddPyLib(OccSolidPy OccSolid OccFacePy)
AddPyLib(OccPrimitivePy OccPrimitive OccSolidPy)
AddPyLib(OccBoxPy OccBox OccPrimitivePy)
AddPyLib(OccCylinderPy OccCylinder OccPrimitivePy)
AddPyLib(OccModifiedSolidPy OccModifiedSolid OccBoxPy OccCylinderPy)
AddPyLib(OccBooleanSolidPy OccBooleanSolid OccModifiedSolidPy)
AddPyLib(OccSolidMakerPy OccSolidMaker OccBoxPy OccCylinderPy OccBooleanSolidPy)

pybind11_add_module(OccWrapper OccWrapperPy.cpp)
target_link_libraries(OccWrapper PRIVATE 
    OccSolidMakerPy
)

execute_process(
    COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("-- Python site-packages directory is ${PYTHON_SITE_PACKAGES}")
install(FILES "${CMAKE_BINARY_DIR}/lib/OccWrapper.cpython-36m-x86_64-linux-gnu.so"
    DESTINATION ${PYTHON_SITE_PACKAGES}
)
