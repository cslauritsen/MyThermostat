#include "all.hpp"

using namespace MyThermostat;
using namespace std;
int main(int argc, char** argv) {

	SetPointRecord model;
	memset(&model, 0, sizeof(model));

	model.heatcool=HEAT;
	model.setpoint=5;
	model.hr=12;
	model.min=0;

	Thermostat th;

	th.copyToAll(&model);
	cout << "Copied." << endl;
	th.save();
	cout << "Saved." << endl;

	cout << "Done." << endl;
}
