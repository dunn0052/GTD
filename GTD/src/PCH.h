#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstdarg>
#include <stdio.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

#ifdef GTD_PLATFORM_WINDOWS
// windows specific
	#include <Windows.h>
#else
	#include <stdlib.h> // Linux or Mac? 
#endif

 