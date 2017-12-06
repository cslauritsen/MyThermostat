
#include "all.hpp"
using namespace MyThermostat;
#ifndef ARDUINO
#include <ncurses.h>
#endif

const char *choices[] = {
	"Sunday"
	, "Monday"
	, "Tuesday"
	, "Wednesday"
	, "Thursday"
	, "Friday"
	, "Saturday"
};

int main() {
  int spos = 0;
  Thermostat t;
  t.load();
  SetPointRecord *sr = &t.setpoints[spos];
  int ch;
#ifndef ARDUINO
  initscr();            /* Start curses mode 		*/
  raw();                /* Line buffering disabled	*/
  keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
  noecho();             /* Don't echo() while we do getch */

  bool saved = false;
  for (int c = 0; c != 'q'; c = getch()) {
    move(0, 0);
    switch (c) {
    case 0:
      break;
    case 'm':
      sr->incrMode();
      break;
    case 'e':
      sr->setEnabled(!sr->isEnabled());
      break;
    case '+':
      sr->incrSetPoint();
      break;
    case '-':
      sr->decrSetPoint();
      break;
    case 's':
      spos = (spos + 1) % t.maxSetpoints;
      sr = &t.setpoints[spos];
      break;
    case 'w':
      sr->incrWeekday();
      break;
    case 'M':
      sr->incrMinute();
      break;
    case 'H':
      sr->setHour((sr->getHour() + 1) % 24);
      break;
    case 'u':
      if (sr->getUnits() == FAHRENHEIT) {
        sr->setUnits(CELSIUS);
      } else {
        sr->setUnits(FAHRENHEIT);
      }
      break;
    case 'S':
      t.save();
      saved = true;
    default:
      break;
    }

    const char *modeStr = sr->getModeAsString();
    clear();
    printw("Mode:     %s\n", modeStr);
    printw("Index:    %d\n", spos);
    printw("Enabled:  %s\n", sr->isEnabled() ? "Y" : "N");
    printw("DOW:      %s\n", sr->getWeekdayAsString());
    printw("Hour:Min  %d:%d\n", sr->getHour(), sr->getMinutes());
    printw("Current:  %d °%c\n", static_cast<int>(sr->convert(72.1)),
           sr->getUnits() == FAHRENHEIT ? 'F' : 'C');
    if (OFF != sr->getMode()) {
      printw("Setpoint: %d °%c\n", sr->getSetpoint(),
             sr->getUnits() == FAHRENHEIT ? 'F' : 'C');
    }
    if (saved) {
      printw("Saved.\n");
      saved = false;
    }
    refresh(); /* Print it on to the real screen */
  }
  endwin(); /* End curses mode		  */
#endif

  return 0;
}
