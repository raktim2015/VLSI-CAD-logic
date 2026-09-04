#include "Cube.hpp"
#include <iostream>


bool Cube::isPositive() const
{
    return (val1==LOW && val2==HIGH);
}
bool Cube::isNegative() const
{
    return (val1==HIGH && val2==LOW);
}
bool Cube::isDontCare() const
{
    return (val1==HIGH && val2==HIGH);
}
void Cube::setPositive()
{
    val1 = LOW;
    val2 = HIGH;
}
void Cube::setNegative()
{
    val1 = HIGH;
    val2 = LOW;
}
void Cube::setDontCare()
{
    val1 = HIGH;
    val2 = HIGH;
}
std::ostream& operator<<(std::ostream& os, const Cube* cube)
{
    if (cube->isPositive()) os << "01";
    else if(cube->isNegative()) os << "10";
    else if(cube->isDontCare()) os << "11";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Cube& cube)
{
    if (cube.isPositive()) os << "01";
    else if(cube.isNegative()) os << "10";
    else if(cube.isDontCare()) os << "11";
    return os;
}

int __test__cube()
{
    Cube* pos = new Cube(Cube::CubeType::POS);
    Cube* neg = new Cube(Cube::CubeType::NEG);
    Cube* dnc = new Cube(Cube::CubeType::DNC);
    std::cout << pos << " " << neg << " " << dnc << std::endl;

    dnc->setPositive();
    pos->setNegative();
    neg->setDontCare();

    std::cout << pos << " " << neg << " " << dnc << std::endl;

    return 0;
}