#include "stdinc.h"
#include <fstream>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void PatchT5_Fullbright()
{
  ifstream infile("players/fps.cfg");

  string line;
  while(getline(infile, line))
  {
    if(line.find("r_fullbright 1") != string::npos)
    {
      *(BYTE*)0x6EDF41 = 1;
    }
  }
}
