#include "all.hpp"
using namespace std;
namespace MyThermostat {
void SetPointRecord::save() {
	uint8_t *bytes;
#ifdef __APPLE__
	std::cout << "sizeof(this)" << sizeof(this) << std::endl;

	ofstream f;
	f.open("test.out", ios::out | ios::binary);
	bytes = (uint8_t *) this;
	for (int i=0; i < sizeof(this); i++) {
		f << *bytes;
		bytes++;
	}
	f.close();
	
#endif
}

void Thermostat::save() {
	uint8_t *bytes;
#ifndef ARDUINO
	std::cout << "sizeof(this.schedule)" << sizeof(this->schedule) << std::endl;

	ofstream f;
	f.open("sched.out", ios::out|ios::binary);
	bytes = (uint8_t *) this->schedule;
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
