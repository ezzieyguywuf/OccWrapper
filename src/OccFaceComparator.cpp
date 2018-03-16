#include <OccFaceComparator.h>

#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <BRep_Tool.hxx>
#include <Precision.hxx>

#include <cmath>
#include <stdexcept>


bool Occ::FaceComparator::operator()(const Occ::Face& face1, const Occ::Face& face2) const
{
    // First, get all vertices in each face
    TopTools_IndexedMapOfShape vertices1;
    TopTools_IndexedMapOfShape vertices2;

    //TopExp::MapShapes(face1.getShape(), TopAbs_VERTEX, vertices1);
    //TopExp::MapShapes(face2.getShape(), TopAbs_VERTEX, vertices2);

    TopExp_Explorer exp1(face1.getShape(), TopAbs_VERTEX);
    TopExp_Explorer exp2(face2.getShape(), TopAbs_VERTEX);
    
    for (; exp1.More(); exp1.Next())
    {
        for (; exp2.More(); exp2.Next())
        {
            auto pt1 = BRep_Tool::Pnt(TopoDS::Vertex(exp1.Current()));
            auto pt2 = BRep_Tool::Pnt(TopoDS::Vertex(exp2.Current()));
            // make sure these points are not the same before comparing them. If so, go on
            // to a new set of points.
            if (pt1.Distance(pt2) > Precision::Confusion())
            {
                double dist1 = std::sqrt(std::pow(pt1.X(),2) + std::pow(pt1.Y(),2) + std::pow(pt1.Z(),2));
                double dist2 = std::sqrt(std::pow(pt2.X(),2) + std::pow(pt2.Y(),2) + std::pow(pt2.Z(),2));
                return dist1 < dist2;
            }
        }
    }


    // get the point at each (u, v) pair;

    // whichever point is closest to the origin represents the "smallest" face.
    throw std::runtime_error("These appear to be the same face");
}
