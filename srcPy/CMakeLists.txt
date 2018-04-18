include_directories(
    ${PYBIND11_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

set(OccWrapperLibs
    OccPrimitive
    OccBooleanSolid 
    OccBox 
    OccCylinder 
    OccModifiedSolid
    OccShape
    OccSolid
    OccFace
    OccEdge)

AddLib(OccShapePy STATIC OccShape)
AddLib(OccEdgePy STATIC OccEdge OccShapePy)
AddLib(OccFacePy STATIC OccFace OccEdgePy)
AddLib(OccSolidPy STATIC OccSolid OccFacePy)
AddLib(OccPrimitivePy STATIC OccPrimitive OccSolidPy)
AddLib(OccBoxPy STATIC OccBox OccPrimitivePy)
AddLib(OccCylinderPy STATIC OccCylinder OccPrimitivePy)
AddLib(OccModifiedSolidPy STATIC OccModifiedSolid OccBoxPy OccCylinderPy)
AddLib(OccBooleanSolidPy STATIC OccBooleanSolid OccModifiedSolidPy)
AddLib(OccSolidMakerPy STATIC OccSolidMaker OccBoxPy OccCylinderPy OccBooleanSolidPy)

pybind11_add_module(OccWrapper OccWrapperPy.cpp)
target_link_libraries(OccWrapper PRIVATE 
    OccSolidMakerPy
)

pybind11_add_module(example_py test.cpp)
