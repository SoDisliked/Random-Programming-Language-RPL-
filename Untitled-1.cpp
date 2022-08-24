#include <iostream>
#include <fstream>
#include <string>
//bool DEVELOPER_MESSAGES false
#define DEVELOPER_MESSAGE false 
#define EXAMPLE_PROJECT false
#define NAMEVERSION "Limbaj de programare."

#if defined (_unix_)
#define UNIX true
#define WINDOWS false
#elif defined(_MSC_VER)
#define UNIX false
#define WINDOWS true
#endif

#include <regex>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <boost/any.hpp>
#include <unordered_map>
#include <stdio.h>
#include <codecvt>
#include <thread>

#if UNIX
#include <unistd.h>
#include <filesystem>
#elif WINDOWS
#include <windows.h>
#endif

#include "eval.h"
#include "strops.h"
#include "builtin.h"
#include "main.h"
#include "anyops.h"

#include "ZS.h"

using namespace std;
using namespace boost;

