#ifndef MYTHERMOSTATH
#define MYTHERMOSTATH
#include <string>
namespace MyThermostat {
/** value to add to temp F setpoints */
const int setpointOffset = 58;
const int setpointMax = 31;
const int setpointMin = 0;
enum Weekday { ANY, SUN, MON, TUE, WED, THU, FRI, SAT };
enum Minute { ZERO, QUARTER_PAST, HALF_PAST, QUARTER_TILL };
enum Mode { HEAT, COOL };
#pragma pack(push, 1)
class SetPointRecord {
private:
  Mode mode : 1;
  Weekday weekday : 3;
  unsigned int setpoint : 5;
  unsigned int hr : 5;
  Minute min : 2;

public:
  inline Mode getMode() { return mode; }
  std::string getModeAsString();
  inline void setMode(Mode x) { mode = x; }
  void incrMode();

  inline Minute getMinutes() { return min; }
  inline void setMinutes(Minute x) { min = x; }
  void setMinutes(int x);

  inline bool isOff() { return 31 == hr; }
  inline void setOff() {  hr = 31; }

  inline int getHour() { return hr; }
  inline void setHour(int x) { hr = x; }

  inline int getSetpoint() { return setpointOffset + setpoint; }
  inline void setSetpoint(int x) { setpoint = x - setpointOffset; }
  void incrSetPoint();
  void decrSetPoint();

  inline Weekday getWeekday() { return weekday; }
  inline void setWeekday(Weekday x) { weekday = x; }
  void setWeekday(int x);

  void incrWeekday();
  void decrWeekday();

  void incrMinute();
  void decrMinute();
};

class Thermostat {
public:
  static const int maxSchedules = 35;
  SetPointRecord schedule[maxSchedules]; // Allows 5 transitions per day
  void save();
  void copyToAll(SetPointRecord *model);
};

} // namespace MyThermostat
#endif
#pragma pack(pop)
