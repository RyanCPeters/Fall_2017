//
// Created by R.Peters on 11/17/2017.
//

#include "WorkDir.hpp"
#include <iostream>
#include <unistd.h>

/** WorkDir::WorkDir(std::string path)
 *
 * This contructor is according to a simple template I found some time ago and saved to a folder of miscelanious crap...
 *
 * I lament now that I didn't write down where I got the inspiration from, as I feel I should be giving them credit. :(
 *
 * @param path the requests directory path to where output files should be made.
 */
WorkDir::WorkDir(std::string path)
{
    m_oldWorkingDirectory = GetWorkingDirectory();
    std::cout << "Changing directory to " << path << std::endl;
    chdir(path.c_str());
}


/** std::string WorkDir::GetWorkingDirectory()
 * @return a string representing the path to the directory containing the executable file for this program
 */
std::string WorkDir::GetWorkingDirectory()
{
    char currentWD[2048] = {0};
    getcwd(currentWD, 2047);
    return std::string(currentWD);
}

/** boilerplate deconstructor
 */
WorkDir::~WorkDir(){
    chdir(m_oldWorkingDirectory .c_str());
}
