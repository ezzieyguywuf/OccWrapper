#include <OccSolid.h>

#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>

using Occ::Solid;

Solid::Solid(const TopoDS_Solid& aSolid)
    : Shape(aSolid)
{
    this->processFaces();
    this->processEdges();
}

Solid::Solid(const TopoDS_Compound& aCompound)
    : Shape(aCompound)
{
    this->processFaces();
    this->processEdges();
}

const Occ::Faces& Solid::getFaces() const
{
    return myFaces;
}

const Occ::Edges& Solid::getEdges() const
{
    return myEdges;
}

int Solid::getFaceIndex(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::Face& myFace : myFaces)
    {
        if (myFace == aFace){
            return i;
        }
        i++;
    }
    return -1;
}

void Solid::processFaces()
{
    TopTools_IndexedMapOfShape faces;
    TopExp::MapShapes(this->getShape(), TopAbs_FACE, faces);
    for (int i=1; i <= faces.Extent(); i++)
    {
        myFaces.push_back(Occ::Face(TopoDS::Face(faces.FindKey(i))));
    }
}

void Solid::processEdges()
{
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(this->getShape(), TopAbs_EDGE, edges);
    for (int i=1; i <= edges.Extent(); i++)
    {
        myEdges.push_back(Occ::Edge(TopoDS::Edge(edges.FindKey(i))));
    }
}
