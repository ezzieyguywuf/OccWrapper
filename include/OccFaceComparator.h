#ifndef FACECOMPARATOR_H
#define FACECOMPARATOR_H

#include <OccFace.h>

namespace Occ
{
    struct FaceComparator
    {
        public:
            // is face1 "less than" face2? Note, this algorithm only works for two faces
            // which do not share any edges.
            bool operator()(const Occ::Face& face1, const Occ::Face& face2) const;
    };
}

#endif /* FACECOMPARATOR_H */
