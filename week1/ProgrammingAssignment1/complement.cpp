#include "Cube.hpp"
#include "Complement.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using CubeVector = std::vector <Cube*>;
using CubeCubeVector = std::vector <std::vector <Cube*> >;

void Complement::initializeEmptyCubeList() {
    // m_expressions = rows, m_variables = columns. Initialize with Don't care.
    CubeVector curr_expression;
    for (int i=0;i<m_expressions;i++) {
        curr_expression.clear();
        for (int j=0;j<m_variables;j++) {
            Cube* c = new Cube(Cube::CubeType::DNC);
            curr_expression.push_back(c);
        }
        m_pcn.push_back(curr_expression);
    }
}

void Complement::displayPCN(const std::string& msg)
{
    std::cout << "############ PCN STARTS " << msg << "############ " << std::endl;
    for (const auto& l : m_pcn)
    {
        for (const auto& e : l) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "############ PCN ENDS " << msg << "############ " << std::endl;
}

void Complement::parse(const std::string& filename)
{
    std::ifstream fp;
    fp.open(filename);
    if(!fp.is_open()) {
        std::cerr << "file " << filename << "not found" << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(fp, line);
    int variables = stoi(line);

    std::getline(fp,line);
    int expressions = stoi(line);

    setVariables(variables);
    setExpressions(expressions);
    initializeEmptyCubeList();
    int expression_ind = 0;
    while (std::getline(fp, line))
    {
        if ((line.size() == 0) || line[0]==' ')
            break;
        std::istringstream ss(line);
        int exp_count;
        ss >> exp_count;
        for (int i=1;i<=exp_count; i++)
        {
            int exp_j;
            ss >> exp_j;
            if (exp_j > 0)
                m_pcn[expression_ind][exp_j-1]->setPositive();
            else
                m_pcn[expression_ind][abs(exp_j)-1]->setNegative();
        }
        expression_ind++;
    }
    fp.close();
    displayPCN("PCN after parsing");
}

CubeCubeVector Complement::findComplement(CubeCubeVector pcn_cube)
{
    CubeVector& x = findMostBinate();
    CubeCubeVector P = findComplement(positiveCoFactor(x,pcn_cube));
    CubeCubeVector N = findComplement(negativeCoFactor(x,pcn_cube));
    CubeCubeVector var1 = pcnAnd(x,P);
    CubeCubeVector var2 = pcnAnd(pcnComplement(x),N);
    CubeCubeVector res = pcnOr(var1, var2);
    return res;
}

int main()
{
    static std::string FILE1 { "/Users/raktim/Documents/coursera/VLSI-CAD-logic/week1/ProgrammingAssignment1Files/UnateRecursiveComplement/part1.pcn" };
    Complement *pcn = new Complement();
    pcn->parse(FILE1);
    CubeCubeVector res = pcn->findComplement();
    return 0;
}