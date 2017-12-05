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
  unsigned int enabled  :1; // whether to ignore or use this record
  Mode mode : 2;
  Units units : 1;
  unsigned int hr : 5;

  Minute min : 2;
  unsigned int _reserved :4;

public:
  SetPointRecord() {
    enabled = 0;
    mode=HEAT;
    setpoint = setpointMin;
    units = FAHRENHEIT;
    hr = 6;
    min = ZERO;
  }

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
  const char * getWeekdayAsString();

  void incrWeekday();
  void decrWeekday();

  void incrMinute();
  void decrMinute();

  bool isEnabled() { return 1==enabled; }
  void setEnabled(bool x) { enabled = x ? 1 : 0; }

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
  static const int maxSetpoints = 35;
  SetPointRecord setpoints[maxSetpoints]; // Allows 5 transitions per day
  void save();
  void copyToAll(SetPointRecord *model);
  Thermostat() {
    for (int i=0; i < maxSetpoints; i++) {
      setpoints[i] = SetPointRecord();
      setpoints[i].setWeekday(i/5 + 1);
    }
  }
  ~Thermostat() {   }
};

} // namespace MyThermostat
#endif
#pragma pack(pop)
