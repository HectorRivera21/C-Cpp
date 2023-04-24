
#ifndef TILING_H
#define TILING_H

#include <cstdlib>
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

// Returns whether the floor represented by the parameter string has a tiling.
//
// If the parameter string does not represent a valid floor, 
// then the function has undefined behavior.        
bool has_tiling(string floor);

#endif


