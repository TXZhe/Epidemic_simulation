#pragma once

#include "net_work.h"
#include <vector>
#include <algorithm>

#ifndef SET
#include <set> 
#endif


using namespace std;

set<USERS> immunize_edge(double pha, int immune_type, vector<vector<USERS>> &social_tie,int minlenth, vector<USERS> &edges);

set<int> immunize_node(double pha, int immune_type, vector<net_work> &social_tie, net_work &edges, vector<int> &nodes);
set<int> immunize_node_aqirf(double pha, net_work &irf_neighbor, vector<int> &nodes);