#ifndef OCCCylinder_H
#define OCCCylinder_H

#include <OccSolid.h>
#include <OccFace.h>

#include <map>
#include <string>

#include <BRepPrimAPI_MakeCylinder.hxx>

namespace Occ{
    class Cylinder
    {
        public:
            Cylinder(double rad, double height);;

            const Face& top() const;
            const Face& bottom() const;
            const Face& lateral() const;

            const Edges& getEdges() const;

        private:
            BRepPrimAPI_MakeCylinder myMaker;
            Solid mySolid;
            std::map<std::string, Occ::Face> myMappedFaces;
    };
}

#endif /* OCCCylinder_H */
