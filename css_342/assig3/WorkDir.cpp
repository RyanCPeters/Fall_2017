//
// Created by R.Peters on 11/17/2017.
//

#include "WorkDir.h"
#include <iostream>
#include <unistd.h>

WorkDir::WorkDir(std::string path)
{
    m_oldWorkingDirectory = GetWorkingDirectory();
    std::cout << "Changing directory to " << path << std::endl;
    chdir(path.c_str());
}

std::string WorkDir::GetWorkingDirectory()
{
    char currentWD[2048] = {0};
    getcwd(currentWD, 2047);
    return std::string(currentWD);
}


WorkDir::~WorkDir(){
    chdir(m_oldWorkingDirectory .c_str());
}
