#include "all.hpp"

using namespace MyThermostat;
using namespace std;
int main(int argc, char** argv) {

	SetPointRecord model;
	memset(&model, 0, sizeof(model));

	model.setMode(HEAT);
	model.setSetpoint(60);
	model.incrSetPoint();
	model.setHour(12);
	model.setMinutes(ZERO);

	cout << "Setpoint: " << model.getSetpoint() << endl;

	cout << "Weekday Incr test:" << endl;
	model.setWeekday(ANY);
	cout << "Weekday: " << model.getWeekday() << endl;
	for (int i=0; i < 8; i++) {
		model.incrWeekday();
		cout << "Weekday: " << model.getWeekday() << endl;
	}

	cout << "Weekday Decr test" << endl;
	model.setWeekday(ANY);
	cout << "Weekday: " << model.getWeekday() << endl;
	for (int i=0; i < 8; i++) {
		model.decrWeekday();
		cout << "Weekday: " << model.getWeekday() << endl;
	}

	cout << "minute Incr test:" << endl;
	model.setMinutes(QUARTER_TILL);
	cout << "minute: " << model.getMinutes() << endl;
	for (int i=0; i < 8; i++) {
		model.incrMinute();
		cout << "minute: " << model.getMinutes() << endl;
	}

	cout << "minute Decr test" << endl;
	model.setWeekday(ZERO);
	cout << "minute: " << model.getMinutes() << endl;
	for (int i=0; i < 8; i++) {
		model.decrMinute();
		cout << "minute: " << model.getMinutes() << endl;
	}


	Thermostat th;

	th.copyToAll(&model);
	cout << "Copied." << endl;
	th.save();
	cout << "Saved." << endl;

	cout << "Done." << endl;
}
