
#include "all.hpp"
using namespace MyThermostat;
#ifndef ARDUINO
#include <ncurses.h>
#endif
int main() {
  Thermostat t;
  SetPointRecord *sr = &t.schedule[0];
  int ch;
#ifndef ARDUINO
  initscr();            /* Start curses mode 		*/
  raw();                /* Line buffering disabled	*/
  keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
  noecho();             /* Don't echo() while we do getch */

  for (int c = 0; c != 'q'; c = getch()) {
    move(0,0);
    switch(c) {
      case 0:
        break;
      case 'm':
        sr->incrMode();
        break;
      case '+':
          sr->incrSetPoint();
          break;
      case '-':
          sr->decrSetPoint();
          break;
      case 'u':
        if (sr->getUnits() == FAHRENHEIT) {
          sr->setUnits(CELSIUS);
        }
        else {
          sr->setUnits(FAHRENHEIT);
        }
          break;
      default:
        break;
    }

    const char *modeStr = sr->getModeAsString();
    clear();
    printw("Mode:     %s\n", modeStr);
    printw("Current:  %d °%c\n", static_cast<int>(sr->convert(72.1)), sr->getUnits()==FAHRENHEIT ? 'F' : 'C');
    if (OFF != sr->getMode()) {
      printw("Setpoint: %d °%c\n", sr->getSetpoint(), sr->getUnits()==FAHRENHEIT ? 'F' : 'C');
    }
    refresh(); /* Print it on to the real screen */
  }
  endwin(); /* End curses mode		  */
  #endif

  return 0;
}
