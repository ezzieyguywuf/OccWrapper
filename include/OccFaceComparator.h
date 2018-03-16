#ifndef FACECOMPARATOR_H
#define FACECOMPARATOR_H

#include <OccFace.h>

namespace Occ
{
    struct FaceComparator
    {
        public:
            // is face1 "less than" face2? Note, this algorithm only makes sense for two
            // co-planar faces, i.e. it can be used to order the  faces of a solid that
            // originated from a single face but have since been split.
            bool operator()(const Occ::Face& face1, const Occ::Face& face2) const;
    };
}

#endif /* FACECOMPARATOR_H */
