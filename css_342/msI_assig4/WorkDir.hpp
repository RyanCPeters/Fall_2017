//
// Created by R.Peters on 11/17/2017.
//

#ifndef ASSIG3_WORKDIR_H
#define ASSIG3_WORKDIR_H
#include <string>

class WorkDir
{
public:
    explicit WorkDir(std::string path);
    virtual ~WorkDir();
    static std::string GetWorkingDirectory();
protected:
    std::string m_oldWorkingDirectory;
};

#endif //ASSIG3_WORKDIR_H
