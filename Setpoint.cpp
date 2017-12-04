#include "all.hpp"
using namespace std;
namespace MyThermostat {

void SetPointRecord::incrMode() {
  if (isOff()) {
    setMode(HEAT);
  }
  else if (HEAT == mode) {
    setMode(COOL);
  }
  else {
    setOff();
  }
}
string SetPointRecord::getModeAsString() {
  std::string ret("?");
  if (isOff()) {
    ret = "OFF";
  } else {
    switch (mode) {
    case HEAT:
      ret = "HEAT";
      break;
    case COOL:
      ret = "COOL";
      break;
    default:
      break;
    }
  }
  return ret;
}

void SetPointRecord::setMinutes(int x) {
  switch (x) {
  case 0:
    min = ZERO;
    break;
  case 1:
    min = QUARTER_PAST;
    break;
  case 2:
    min = HALF_PAST;
    break;
  case 3:
    min = QUARTER_TILL;
    break;
  }
}
void SetPointRecord::setWeekday(int x) {
  switch (x) {
  case 0:
    weekday = ANY;
    break;
  case 1:
    weekday = SUN;
    break;
  case 2:
    weekday = MON;
    break;
  case 3:
    weekday = TUE;
    break;
  case 4:
    weekday = WED;
    break;
  case 5:
    weekday = THU;
    break;
  case 6:
    weekday = FRI;
    break;
  case 7:
    weekday = SAT;
    break;
  default:
    break;
  }
}

void SetPointRecord::incrSetPoint() {
  if (setpoint < setpointMax) {
    setpoint++;
  }
}
void SetPointRecord::decrSetPoint() {
  if (setpoint > setpointMin) {
    setpoint--;
  }
}

void SetPointRecord::incrWeekday() {
  if (SAT == weekday) {
    weekday = ANY;
  } else {
    weekday = static_cast<Weekday>(static_cast<int>(weekday) + 1);
  }
}
void SetPointRecord::decrWeekday() {
  if (ANY == weekday) {
    weekday = SAT;
  } else {
    weekday = static_cast<Weekday>(static_cast<int>(weekday) - 1);
  }
}

void SetPointRecord::incrMinute() {
  if (QUARTER_TILL == min) {
    min = ZERO;
  } else {
    min = static_cast<Minute>(static_cast<int>(min) + 1);
  }
}
void SetPointRecord::decrMinute() {
  if (ZERO == min) {
    min = QUARTER_TILL;
  } else {
    min = static_cast<Minute>(static_cast<int>(min) - 1);
  }
}
} // namespace MyThermostat
