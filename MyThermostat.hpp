#ifndef MYTHERMOSTATH
#define MYTHERMOSTATH

namespace MyThermostat {
/** value to add to temp F setpoints */
const int setpointOffset = 58;
const int setpointMax = 31;
const int setpointMin = 0;
const int modeCount = 4;
enum Weekday { ANY, SUN, MON, TUE, WED, THU, FRI, SAT };
enum Minute { ZERO, QUARTER_PAST, HALF_PAST, QUARTER_TILL };
enum Mode { OFF, HEAT, COOL, AUTO };
enum Units { FAHRENHEIT, CELSIUS };
#pragma pack(push, 1)
class SetPointRecord {
private:
  Weekday weekday : 3;
  unsigned int setpoint : 5;

  Mode mode : 2;
  Units units : 1;
  unsigned int hr : 5;

  Minute min : 2;

public:
  inline Units getUnits() { return units; }
  inline void setUnits(Units x) { units = x; }

  inline Mode getMode() { return mode; }
  const char *getModeAsString();
  inline void setMode(Mode x) { mode = x; }
  void incrMode();

  inline Minute getMinutes() { return min; }
  inline void setMinutes(Minute x) { min = x; }
  void setMinutes(int x);

  inline int getHour() { return hr; }
  inline void setHour(int x) { hr = x; }

  inline int getSetpoint() {
    return convert(setpointOffset + setpoint);
  }

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

  inline float toCelsius(float f) {
    f -= 32.0;
    f *= 5.0 / 9.0;
    return f;
  }

  inline float toFahrenheit(float c) {
    c *= 9.0 / 5.0;
    c += 32.0;
    return c;
  }

  inline float convert(float c) {
      if (CELSIUS == units) {
        return toCelsius(c);
      }
      return c;
  }

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
