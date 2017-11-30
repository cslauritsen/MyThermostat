#include "all.hpp"
using namespace std;
namespace MyThermostat {

void Thermostat::save() {
	uint8_t *bytes = (uint8_t *) this->schedule;
#ifndef ARDUINO
	std::cout << "sizeof(this.schedule)" << sizeof(this->schedule) << std::endl;
	ofstream f;
	f.open("sched.out", ios::out|ios::binary);
	for (int i=0; i < sizeof(this->schedule); i++) {
		f << *bytes;
		bytes++;
	}
	f.close();
#endif
}

void Thermostat::copyToAll(SetPointRecord *model) {
		for (int t=0; t < Thermostat::maxSchedules; t++) {
			SetPointRecord *pSpr = &this->schedule[t];
			memcpy(pSpr, model, sizeof(SetPointRecord));
			pSpr->weekday = t%7;
		}
}
}
