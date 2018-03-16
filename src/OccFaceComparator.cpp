#include <OccFaceComparator.h>

#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <GeomAdaptor_Surface.hxx>

#include <cmath>


bool Occ::FaceComparator::operator()(const Occ::Face& face1, const Occ::Face& face2) const
{
    //const TopoDS_Face& topoFace1 = TopoDS::Face(face1.getShape());
    //const TopoDS_Face& topoFace2 = TopoDS::Face(face2.getShape());

    BRepAdaptor_Surface surf1(TopoDS::Face(face1.getShape()));
    BRepAdaptor_Surface surf2(TopoDS::Face(face2.getShape()));

    double u1a = surf1.FirstUParameter();
    double u2a = surf1.LastUParameter();
    double v1a = surf1.FirstVParameter();
    double v2a = surf1.LastVParameter();
    double u1b = surf2.FirstUParameter();
    double u2b = surf2.LastUParameter();
    double v1b = surf2.FirstVParameter();
    double v2b = surf2.LastVParameter();

    // find the center of u and v parameters for both
    double ua = (u1a + u2a) / 2.0;
    double va = (v1a + v2a) / 2.0;
    double ub = (u1b + u2b) / 2.0;
    double vb = (v1b + v2b) / 2.0;

    // get the point at each (u, v) pair;
    const auto& pt1 = surf1.Value(ua, va);
    const auto& pt2 = surf2.Value(ub, vb);

    // whichever point is closest to the origin represents the "smallest" face.
    double dist1 = std::sqrt(std::pow(pt1.X(),2) + std::pow(pt1.Y(),2) + std::pow(pt1.Z(),2));
    double dist2 = std::sqrt(std::pow(pt2.X(),2) + std::pow(pt2.Y(),2) + std::pow(pt2.Z(),2));
    return dist1 < dist2;
}
