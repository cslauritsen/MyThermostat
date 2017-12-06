#include "all.hpp"
using namespace std;
namespace MyThermostat {

void Thermostat::save() {
  // Reinterpret the data fields in the class as an array of bytes
  // that can be persisted, one byte at a time
  uint8_t *bytes = reinterpret_cast<uint8_t *>(this->setpoints);
#ifndef ARDUINO
  std::cout << "sizeof(this.schedule)" << sizeof(this->setpoints) << std::endl;
  ofstream f;
  f.open("sched.out", ios::out | ios::binary);
  for (int i = 0; i < sizeof(this->setpoints); i++) {
    f << *bytes;
    bytes++;
  }
  f.close();
#endif
}

void Thermostat::load() {

  uint8_t *bytes = reinterpret_cast<uint8_t *>(this->setpoints);
#ifndef ARDUINO
  std::cout << "Loading saved data" << std::endl;
  ifstream f;
  f.open("sched.out", ios::in | ios::binary);
  for (int i = 0; i < sizeof(SetPointRecord) * maxSetpoints; i++) {
    f >> *bytes;
    bytes++;
  }
  f.close();
#endif
}

void Thermostat::copyToAll(SetPointRecord *model) {
  for (int t = 0; t < Thermostat::maxSetpoints; t++) {
    SetPointRecord *pSpr = &this->setpoints[t];
    memcpy(pSpr, model, sizeof(SetPointRecord));
    pSpr->setWeekday(FRI);
  }
}

} // namespace MyThermostat
