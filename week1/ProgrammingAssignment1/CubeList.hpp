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
        static int countPositive(const CubeVector& cube);
        static int countNegative(const CubeVector& cube);
        static int countDNC(const CubeVector& cube);
        static bool isOne(const CubeVector& cube);

};