#ifndef MYTHERMOSTATH
#define MYTHERMOSTATH

namespace MyThermostat {
enum Weekdays { SUN, MON, TUE, WED, THU, FRI, SAT };
enum Minutes { ZERO, QUARTER_PAST, HALF_PAST, QUARTER_TILL };
enum SprType { HEAT, COOL };
/** value to add to temp F setpoints */
const int spr_offset = 58;
#pragma pack(push, 1)
class SetPointRecord
{
public:
	unsigned int heatcool		:1;
	unsigned int weekday 		:3;
	unsigned int setpoint		:5;
	unsigned int hr 		:5;
	unsigned int min 		:2;
};

class Thermostat {
	public:
	static const int maxSchedules = 35;
	SetPointRecord schedule[maxSchedules]; // Allows 5 transitions per day
	void save();
	void copyToAll(SetPointRecord *model);
};

}
#endif
#pragma pack(pop)
