#include <ncurses.h>
#include "all.hpp"
using namespace MyThermostat;
int main() {
  Thermostat t;
  SetPointRecord *sr = &t.schedule[0];
  int ch;

  initscr();            /* Start curses mode 		*/
  raw();                /* Line buffering disabled	*/
  keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
  noecho();             /* Don't echo() while we do getch */

  for (int c = 0; c != 'q'; c = getch()) {
    move(0,1);
    std::string modeStr = sr->getModeAsString();
    printw("Mode: %s\n", &modeStr);
    printw("Mode2: %d\n", sr->getMode());
    printw("Current: %.1f\n", 72.1);
    printw("Setpoint: %d\n", sr->getSetpoint());
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
      default:
        printw("invalid key");
        break;
    }
    refresh(); /* Print it on to the real screen */
  }
  endwin(); /* End curses mode		  */

  return 0;
}
