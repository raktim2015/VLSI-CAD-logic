#include <iostream>
#include <string>
#include <fstream>
#include "complement.hpp"

using namespace std;

static void parseInputFile(const std::string& fname, PCN* pcn)
{

  ifstream fp;	
  fp.open(fname);
	if (!fp.is_open())
	{
		cerr << "file " << fname << " not found " << endl;
    exit(1);
	} 
  
  string line;
  getline(fp,line);
  pcn->setVariables((unsigned int)(stoi(line)));
  getline(fp,line); 
  pcn->setExpressions((unsigned int)(stoi(line)));

  while (getline(fp,line))
  {
    vector <int> tokens = tokenize(line);
    if(tokens.size() == 0) continue;
    for (auto i=1 ; i<tokens.size();i++) {
      
    } 
  }  

  fp.close(); 
}

int main()
{
  std::string fname = "../ProgrammingAssignment1Files/UnateRecursiveComplement/part1.pcn";
  PCN *pcn = new PCN();
  parseInputFile(fname, pcn);

	return 0;
}
