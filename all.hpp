#include "MyThermostat.hpp"

#if defined(__APPLE__) || defined(__linux)
#include <fstream>
#include <iostream>
#include <ostream>

#endif

#if defined(__linux) || defined(ARDUINO)
#include <stdint.h>
#include <string.h>
#endif
