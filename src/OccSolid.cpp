#include <OccSolid.h>

#include <TopTools_IndexedMapOfShape.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>

using Occ::Solid;

Solid::Solid()
    : Shape(TopoDS_Solid())
{}

Solid::Solid(const TopoDS_Shape& aShape)
    : Shape(aShape)
{
    switch (aShape.ShapeType()) {
    case TopAbs_SOLID:
    case TopAbs_COMPOUND:
        break;
    default:
        throw std::runtime_error("I don't know how to create a solid from that TopoDS_Shape.");
            
    }
    this->processFaces();
    this->processEdges();
}

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

Solid::Solid(const Solid& aSolid)
    : Shape(aSolid.myShape)
{
    this->processFaces();
    this->processEdges();
}

Solid Solid::operator=(const Solid& aSolid)
{
    myShape = aSolid.myShape;
    this->processFaces();
    this->processEdges();
    return *this;
}

const Occ::Faces& Solid::getFaces() const
{
    return myFaces;
}

const Occ::Edges& Solid::getEdges() const
{
    return myEdges;
}

uint Solid::getFaceIndex(const Occ::Face& aFace) const
{
    uint i = 0;
    for (const Occ::Face& myFace : myFaces)
    {
        if (myFace.isSimilar(aFace)){
            return i;
        }
        i++;
    }
    throw std::runtime_error("That face is not in this solid");
}

void Solid::processFaces()
{
    myFaces.clear();
    TopTools_IndexedMapOfShape faces;
    TopExp::MapShapes(this->getShape(), TopAbs_FACE, faces);
    for (int i=1; i <= faces.Extent(); i++)
    {
        myFaces.push_back(Occ::Face(TopoDS::Face(faces.FindKey(i))));
    }
}

void Solid::processEdges()
{
    myEdges.clear();
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(this->getShape(), TopAbs_EDGE, edges);
    for (int i=1; i <= edges.Extent(); i++)
    {
        myEdges.push_back(Occ::Edge(TopoDS::Edge(edges.FindKey(i))));
    }
}

void Solid::translate(double dx, double dy, double dz)
{
    Shape::translate(dx, dy, dz);
    this->processFaces();
    this->processEdges();
}
