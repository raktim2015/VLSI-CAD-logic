#pragma once
#include <vector>
class Cube;
using CubeVector = std::vector <Cube*>;
using CubeCubeVector = std::vector <std::vector <Cube*>> ;

class Complement {
    private:
        int m_variables;
        int m_expressions;
        CubeCubeVector m_pcn;
    public:
        explicit Complement() : m_variables(0), m_expressions(0) {}
        void parse(const std::string& filename);
        void setVariables(const int& variables) {
            m_variables = variables;
        }
        void setExpressions(const int& expressions) {
            m_expressions = expressions;
        }
        void initializeEmptyCubeList();
        void displayPCN(const std::string& msg);
        void findComplement();
};