#pragma once
#include <vector>
class Cube;
using CubeVector = std::vector <Cube*>;
class CubeList
{
    public:
        static bool isPositiveUnate(const CubeVector& cubelist);
        static bool isNegativeUnate(const CubeVector& cubelist);
        static bool isBinate(const CubeVector& cubelist);
};