#pragma once

#include <vector>
#include <list>
#include <array>
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "framework.h"

#include "MyColor.h"
#include "Vector.h"

using namespace std;

using ColorMatrix = vector<vector<MyColor>>;

#define MAX_WIDTH 10

#define DEF_OFFSET 5


int sign(int x);