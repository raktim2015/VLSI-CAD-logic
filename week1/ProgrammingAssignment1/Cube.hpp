#pragma once
#include <iosfwd>

class Cube
{
    private:
        static constexpr bool LOW = false;
        static constexpr bool HIGH = true;
        bool val1;
        bool val2;
    public:
        enum class CubeType {
            POS,
            NEG,
            DNC
        };
        Cube() = delete;
        explicit Cube(CubeType type) {
            switch (type) {
                case CubeType::POS: setPositive(); break;   
                case CubeType::NEG: setNegative(); break;
                case CubeType::DNC: setDontCare(); break;
                default : break;
            }
        }
        bool isPositive() const;
        bool isNegative() const;
        bool isDontCare() const;
        void setPositive();
        void setNegative();
        void setDontCare();

        friend std::ostream& operator<<(std::ostream& os, const Cube& cube);
        friend std::ostream& operator<<(std::ostream& os, const Cube* cube);

};

