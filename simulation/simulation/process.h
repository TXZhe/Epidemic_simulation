#pragma once

#include "net_work.h"
#include <vector>
#include <algorithm>
#include <set>

#ifndef _COMMONVARIABLES_H
#define _COMMONVARIABLES_H
#endif


using namespace std;

int process_halftime(int source, double beta, vector<net_work> &reaction_net, set<USERS> &immunized);

int process_halftime(int source, double beta, vector<net_work> &reaction_net, set<int> &immunized);