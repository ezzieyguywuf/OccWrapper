#ifndef OCCBOX_H
#define OCCBOX_H

#include <OccSolid.h>
#include <OccFace.h>
#include <OccTypes.h>

#include <map>
#include <string>

#include <BRepPrimAPI_MakeBox.hxx>

namespace Occ{
    class Box
    {
        public:
            Box(double dx, double dy, double dz);;

            const Face& top() const;
            const Face& bottom() const;
            const Face& left() const;
            const Face& right() const;
            const Face& front() const;
            const Face& back() const;

            const Edges& getEdges() const;

        private:
            BRepPrimAPI_MakeBox myMaker;
            Solid mySolid;
            std::map<std::string, Occ::Face> myMappedFaces;
    };
}

#endif /* OCCBOX_H */
