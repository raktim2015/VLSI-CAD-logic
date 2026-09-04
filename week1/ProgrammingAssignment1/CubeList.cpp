/*
    CubeList is stateless.
    This will all the operations needed on cube vector
*/
#include "Cube.hpp"
#include "CubeList.hpp"
#include <iostream>
bool CubeList::isPositiveUnate(const CubeVector& cubelist)
{
    bool res = true;
    for (const auto& cube : cubelist)
    {
        res = res && !(cube->isNegative());
    }   
    return res;
}

bool CubeList::isNegativeUnate(const CubeVector& cubelist)
{
    bool res = true;
    for (const auto& cube : cubelist)
    {
        res = res && !(cube->isPositive());
    }   
    return res;
}
bool CubeList::isBinate(const CubeVector& cubelist)
{
    short binateCheck = 0;
    for (const auto& cube : cubelist) {
        if (cube->isPositive()) {
            binateCheck = binateCheck | 1;
        }
        else if (cube->isNegative()) {
            binateCheck = binateCheck | 2;
        }
    }
    return (binateCheck==3) ? true : false;
}

void check(const CubeVector& cubelst)
{
    std::cout << "POSUNATE : " << CubeList::isPositiveUnate(cubelst) << 
        " NEGUNATE : " << CubeList::isNegativeUnate(cubelst) << 
        " BINATE : " << CubeList::isBinate(cubelst) << std::endl;
}
int __test__cubelist()
{
    CubeVector cubevecBinate = {new Cube(Cube::CubeType::POS), new Cube(Cube::CubeType::NEG)};
    CubeVector cubevecPosUnate = {new Cube(Cube::CubeType::POS), new Cube(Cube::CubeType::POS), new Cube(Cube::CubeType::DNC)};
    CubeVector cubevecNegUnate = {new Cube(Cube::CubeType::NEG), new Cube(Cube::CubeType::NEG), new Cube(Cube::CubeType::NEG)};
    check(cubevecBinate);
    check(cubevecPosUnate);
    check(cubevecNegUnate);

    return 0;
}