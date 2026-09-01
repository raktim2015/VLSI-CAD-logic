#include "Complement.hpp"
#include <stringstream>
#include <iostream>

void Complement::parse(const std::string& filename)
{
    std::ofstream fp;
    fp.open(filename);
    if(!fp.is_open()) {
        std::cerr << "file " << filename << "not found" << endl;
        exit(1);
    }

    std::string line;
    getline(fp, line);
    int variables = stoi(line);

    getline(fp,line);
    int expressions = stoi(line);

    pcn->setVariables(variable);
    pcn->setExpressions(expressions);

    while (getline(fp, line))
    {
        std::istringstream ss(line);
        int exp_count;
        ss >> exp_count;
        CubeList* cubelist = new CubeList(pcn->getVariables());
        for (int i=1;i<=exp_count; i++)
        {
            int num;
            ss >> num;
            Cube* cube;
            if (num > 0)
                cube = new Cube(Cube::POS);
            else
                cube = new Cube(Cube::NEG);
            cubelist->add(cube);
        }
        pcn->add(cubelist);
    }
    fp.close();
}