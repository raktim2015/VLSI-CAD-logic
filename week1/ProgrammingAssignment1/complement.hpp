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
        CubeCubeVector& getPCN() { return m_pcn; }
        void initializeEmptyCubeList();
        void displayPCN(const std::string& msg, const CubeCubeVector& pcn);
        CubeCubeVector findComplement(CubeCubeVector pcn_cube);
        int findVariableSplit(const CubeCubeVector& cube);
        CubeCubeVector positiveCofactor(int var_ind, const CubeCubeVector& cube);
        CubeCubeVector negativeCofactor(int var_ind, const CubeCubeVector& cube);
        CubeCubeVector pcnAnd(int posneg, int var_ind, const CubeCubeVector& pcn_cube);
        CubeCubeVector pcnOr(const CubeCubeVector& cube1, const CubeCubeVector& cube2);
        CubeCubeVector complementCube(const CubeCubeVector& cube);
        void convertCubeToOutput(const CubeCubeVector& cube);

};