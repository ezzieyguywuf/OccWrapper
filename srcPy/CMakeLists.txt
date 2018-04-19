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

pybind11_add_module(example_py test.cpp)
