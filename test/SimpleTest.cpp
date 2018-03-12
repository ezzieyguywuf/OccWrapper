#include <OccSolidMaker.h>
#include <OccSolidModifier.h>
#include <OccModifiedSolid.h>
#include <OccTypes.h>

#include <iostream>

int main(void)
{
    auto box = Occ::SolidMaker::makeBox(10, 10, 10);
    const Occ::Face& front = box.getNamedFace(Occ::FaceName::front);
    const Occ::Face& right = box.getNamedFace(Occ::FaceName::right);
    const Occ::Face& top = box.getNamedFace(Occ::FaceName::top);
    const Occ::Face& left = box.getNamedFace(Occ::FaceName::left);
    const Occ::Face& bottom = box.getNamedFace(Occ::FaceName::bottom);
    const Occ::Face& back = box.getNamedFace(Occ::FaceName::back);

    std::cout << std::boolalpha;
    if (front.sharesEdge(right))
        std::cout << "shares with right" << std::endl;
    if (front.sharesEdge(top))
        std::cout << "shares with top" << std::endl;
    if (front.sharesEdge(left))
        std::cout << "shares with left" << std::endl;
    if (front.sharesEdge(bottom))
        std::cout << "shares with bottom" << std::endl;
    if (front.sharesEdge(back))
        std::cout << "shares with back" << std::endl;
    if (front.sharesEdge(front))
        std::cout << "shares with front" << std::endl;
    //front.getCommonEdge(right);

    return 0;
}
