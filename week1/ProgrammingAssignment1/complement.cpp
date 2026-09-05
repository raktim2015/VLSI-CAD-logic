#include "Cube.hpp"
#include "CubeList.hpp"
#include "Complement.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

using CubeVector = std::vector <Cube*>;
using CubeCubeVector = std::vector <std::vector <Cube*> >;

static CubeCubeVector deepCopy(const CubeCubeVector& cube)
{
    CubeCubeVector newCube;
    for (const auto& sourceRow : cube)
    {
        CubeVector newRow;
        for(const Cube* sourceCube : sourceRow)
            newRow.push_back(new Cube(*sourceCube));
        newCube.push_back(newRow);
    }
    return newCube;
}

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

void Complement::displayPCN(const std::string& msg, const CubeCubeVector& pcn)
{
    std::cout << "############ PCN STARTS " << msg << "############ " << std::endl;
    for (const auto& l : pcn)
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
    displayPCN("PCN after parsing", m_pcn);
}

int Complement::findVariableSplit(const CubeCubeVector& cube)
{
    auto extractVariableCube = [](const CubeCubeVector& cube, const int expressions, const int ind) -> CubeVector 
    {
        CubeVector vec;
        for (auto i=0;i<expressions;i++) {
            vec.push_back(cube[i][ind]);
        }
        return vec;
    };
    struct SelectionCriteria {
        int var_ind;
        int positive;
        int negative;
        int maxval;
        int binate;
    };

    auto comp_mostposorneg = [](const struct SelectionCriteria& a, const struct SelectionCriteria& b) -> bool
    {
        if (a.maxval > b.maxval)
            return true;
        if (a.maxval < b.maxval)
            return false;
        if ((a.maxval == b.maxval) && (a.var_ind < b.var_ind))
            return true;
        return false;
    };
    auto comp_mostbinate = [](const struct SelectionCriteria& a, const struct SelectionCriteria& b) -> bool
    {

        if (a.binate < b.binate)
            return true;
        if (a.binate > b.binate)
            return false;
        if ((a.binate == b.binate) && (a.var_ind < b.var_ind))
            return true;
        return false;
    };

    /*auto comp_mostunate = [](const struct SelectionCriteria& a, const struct SelectionCriteria& b) -> bool
    {
        // will only be invoked when the pcn have all unate / dont care variables
        int max_a = std::max(a.positive, a.negative);
        int max_b = std::max(b.positive, b.negative);
        if (max_a > max_b)
            return true;
        if (max_a < max_b)
            return false;
        if ((max_a == max_b) && (a.var_ind < b.var_ind))
            return true;
        return false;
    };*/

    auto noBinate = [](const std::vector <struct SelectionCriteria>& variables) {
        for (const auto& elem : variables) {
            if (elem.positive>0 && elem.negative>0)
                return false;
        }
        return true;
    };


    
    std::vector <struct SelectionCriteria> var_criteria(m_variables);
    for (int i=0;i<m_variables;i++) {
        CubeVector expression = extractVariableCube(cube, cube.size(), i);
        var_criteria[i].var_ind = i;
        var_criteria[i].positive = CubeList::countPositive(expression);
        var_criteria[i].negative = CubeList::countNegative(expression);
        var_criteria[i].maxval = var_criteria[i].positive + var_criteria[i].negative;
        var_criteria[i].binate = abs(var_criteria[i].positive - var_criteria[i].negative);
        if (var_criteria[i].positive==0 && var_criteria[i].negative==0)
            var_criteria[i].binate = INT_MAX;
    }

    // check for no binate. Return the best unate
    if (noBinate(var_criteria)) {
        std::cout << "No binate variable exists" << std::endl;
        sort(var_criteria.begin(), var_criteria.end(), comp_mostposorneg);
        if (var_criteria.size() == 0) return -1;
        return var_criteria[0].var_ind;
    }

    // sort by most pos/neg first and check for no tie
    std::cout << "Check for most pos/neg var" << std::endl;
    sort(var_criteria.begin(), var_criteria.end(), comp_mostposorneg);
    if (var_criteria.size()==0) return -1;
    if (var_criteria[0].maxval > var_criteria[1].maxval) return var_criteria[0].var_ind; // there is no tie

    // if tie in most pos/neg, check for most binate
    std::cout << "Check for most binate" << std::endl;
    sort(var_criteria.begin(), var_criteria.end(), comp_mostbinate);
    if (var_criteria.size()==0) return -1;
    return var_criteria[0].var_ind;

    return -1;
}

CubeCubeVector Complement::positiveCofactor(int var_ind, const CubeCubeVector& cube)
{
    std::unordered_set <int> rowsToRemove;
    CubeCubeVector newCube = deepCopy(cube);
    for (int row = 0; row < cube.size(); row++) {
        if (newCube[row][var_ind]->isPositive()) newCube[row][var_ind]->setDontCare();
        else if(newCube[row][var_ind]->isNegative()) rowsToRemove.insert(row);
    }
    CubeCubeVector res;
    for (int i = 0; i<cube.size(); i++) {
        if(rowsToRemove.find(i)==rowsToRemove.end())
            res.push_back(newCube[i]);
    }
    return res;
}

CubeCubeVector Complement::negativeCofactor(int var_ind, const CubeCubeVector& cube)
{
    std::unordered_set <int> rowsToRemove;
    CubeCubeVector newCube = deepCopy(cube);
    for (int row = 0; row < cube.size(); row++) {
        if (newCube[row][var_ind]->isNegative()) newCube[row][var_ind]->setDontCare();
        else if(newCube[row][var_ind]->isPositive()) rowsToRemove.insert(row);
    }

    CubeCubeVector res;
    for (int i = 0; i<cube.size(); i++) {
        if(rowsToRemove.find(i)==rowsToRemove.end())
            res.push_back(newCube[i]);
    }
    return res;
}

CubeCubeVector Complement::pcnAnd(int posneg, int var_ind, const CubeCubeVector& cube)
{
    CubeCubeVector newCube = deepCopy(cube);
    for(int i=0;i<cube.size();i++) {
        if(posneg)
            newCube[i][var_ind]->setPositive();
        else
            newCube[i][var_ind]->setNegative();
    }
    return newCube;
}

CubeCubeVector Complement::pcnOr(const CubeCubeVector& cube1, const CubeCubeVector& cube2)
{
    CubeCubeVector newCube1 = deepCopy(cube1);
    CubeCubeVector newCube2 = deepCopy(cube2);
    for(auto& elem : newCube2) {
        newCube1.push_back(elem);
    }
    return newCube1;
}

static CubeCubeVector createOne(const int var)
{
    CubeCubeVector cl;
    CubeVector vec;
    for (int i=0;i<var;i++)
        vec.push_back(new Cube(Cube::CubeType::DNC));
    cl.push_back(vec);
    return cl;
}

static bool expressionIsOne(const CubeCubeVector& cube)
{
    for (const auto& elem : cube)
    {
        if(CubeList::isOne(elem)) return true;
    }
    return false;
}

CubeCubeVector Complement::complementCube(const CubeCubeVector& cube)
{
    int posorneg = CubeList::countPositive(cube[0]) + CubeList::countNegative(cube[0]);
    CubeCubeVector newCube;
    for(int i=0;i<posorneg;i++) {
        CubeVector curr_list(m_variables, new Cube(Cube::CubeType::DNC));
        newCube.push_back(curr_list);
    }
    int ind = 0;
    for(int i=0;i<m_variables;i++) {
        if(cube[0][i]->isPositive()) {
            newCube[ind][i]->setNegative();
            ind++;
        }
        else if(cube[0][i]->isNegative()) {
            newCube[ind][i]->setPositive();
            ind++;
        }
    }
    return newCube;
}

CubeCubeVector Complement::findComplement(CubeCubeVector pcn_cube)
{
    
    // base case
    if(pcn_cube.size() == 0)
    {
        return createOne(m_variables);
    }
    if(expressionIsOne(pcn_cube)) {
        CubeCubeVector empty;
        return empty;
    }
    if(pcn_cube.size() == 1)
    {
        return complementCube(pcn_cube);
    }
    int x = findVariableSplit(pcn_cube);
    std::cout << "Variable split " << x << std::endl;
    if (x == -1) {
        std::cout << "Undefined split " << std::endl;
        exit(1);
    }
    CubeCubeVector pcf = positiveCofactor(x,pcn_cube);
    CubeCubeVector ncf = negativeCofactor(x,pcn_cube);
    CubeCubeVector P = findComplement(pcf);
    CubeCubeVector N = findComplement(ncf);
    CubeCubeVector var1 = pcnAnd(1,x,P);
    CubeCubeVector var2 = pcnAnd(0,x,N);
    CubeCubeVector res = pcnOr(var1, var2);
    return res;
}

void Complement::convertCubeToOutput(const CubeCubeVector& cube)
{
    std::ofstream fp("./result.txt");
    fp << m_variables << std::endl;
    fp << cube.size() << std::endl;
    std::vector <int> resvec;
    for (const auto& elem : cube)
    {
        resvec.clear();
        int ind = 1;
        for(const auto& v : elem) {
            if (v->isPositive()) resvec.push_back(ind);
            if (v->isNegative()) resvec.push_back(-ind);
            ind++;
        }
        fp << resvec.size() << " ";
        for (const auto& elem : resvec) {
            fp << elem << " ";
        }
        fp << std::endl;
    }
    fp.close();   
}

int main()
{
    static std::string FILE1 { "/Users/raktim/Documents/coursera/VLSI-CAD-logic/week1/ProgrammingAssignment1Files/UnateRecursiveComplement/part1.pcn" };
    Complement *pcn = new Complement();
    pcn->parse(FILE1);
    CubeCubeVector res = pcn->findComplement(pcn->getPCN());
    pcn->displayPCN("Result ", res);
    pcn->convertCubeToOutput(res);
    return 0;
}