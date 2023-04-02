#pragma once

#include <unistd.h>
#include <sys/wait.h>

#include "manager.hpp"

using namespace std;

class Active
{
private:
    vector<string> osMatch;

public:
    static void startActiveDetection();
};