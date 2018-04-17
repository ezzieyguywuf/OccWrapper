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
AddLib(OccEdgePy STATIC OccShapePy)
AddLib(OccFacePy STATIC OccEdgePy)
AddLib(OccSolidMakerPy STATIC ${OccWrapperLibs} OccSolidMaker)
AddLib(OccPrimitivePy STATIC ${OccWrapperLibs})

pybind11_add_module(OccWrapper OccWrapperPy.cpp)
target_link_libraries(OccWrapper PRIVATE 
    OccFacePy
    OccSolidMakerPy
    OccPrimitivePy
)
