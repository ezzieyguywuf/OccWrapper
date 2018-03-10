#include <OccBox.h>

#include <TopoDS.hxx>

using Occ::Box;

Box::Box(double dx, double dy, double dz)
    : myMaker(dx, dy, dz), mySolid(TopoDS::Solid(myMaker.Shape()))
{
    myMappedFaces.emplace("top", Occ::Face(myMaker.TopFace()));
    myMappedFaces.emplace("bottom", Occ::Face(myMaker.BottomFace()));
    myMappedFaces.emplace("left", Occ::Face(myMaker.LeftFace()));
    myMappedFaces.emplace("right", Occ::Face(myMaker.RightFace()));
    myMappedFaces.emplace("front", Occ::Face(myMaker.FrontFace()));
    myMappedFaces.emplace("back", Occ::Face(myMaker.BackFace()));
}

const Occ::Face& Box::top() const
{
    return myMappedFaces.at("top");
}

const Occ::Face& Box::bottom() const
{
    return myMappedFaces.at("bottom");
}

const Occ::Face& Box::left() const
{
    return myMappedFaces.at("left");
}

const Occ::Face& Box::right() const
{
    return myMappedFaces.at("right");
}

const Occ::Face& Box::front() const
{
    return myMappedFaces.at("front");
}

const Occ::Face& Box::back() const
{
    return myMappedFaces.at("back");
}

const Occ::Edges& Box::getEdges() const
{
    return mySolid.getEdges();
}
