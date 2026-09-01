#pragma once
#include <string>
#include <vector>

using namespace std;

class Cube
{
  /*
    01 -> x term
    10 -> x' term
    11 -> dont care / no term
  */

  private:
    pair <bool, bool> cube;
  
  public:
    explicit Cube(const bool val1, const bool val2) 
    {
      cube = make_pair(val1,val2);
    }
};

class CubeList
{
  private:
    vector <Cube*> m_cube_list;
};

class PCN : public CubeList
{
  private:
    unsigned int m_variables;
    unsigned int m_expressions;
    vector <CubeList*> m_cube_list; 

  public:
    void setVariables(const int variables) { m_variables = variables; }
    void setExpressions(const int expressions) { m_expressions = expressions; }
};
