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
AddLib(OccEdgePy STATIC OccShapePy OccEdge)
AddLib(OccFacePy STATIC OccEdgePy OccFace)
AddLib(OccSolidPy STATIC OccFacePy OccSolid)
AddLib(OccPrimitivePy STATIC OccSolidPy OccPrimitive)
AddLib(OccSolidMakerPy STATIC ${OccWrapperLibs} OccSolidMaker)

pybind11_add_module(OccWrapper OccWrapperPy.cpp)
target_link_libraries(OccWrapper PRIVATE 
    OccShapePy
    OccEdgePy
    OccFacePy
    OccSolidPy
    OccPrimitivePy
    #OccSolidMakerPy
)

pybind11_add_module(example_py test.cpp)
