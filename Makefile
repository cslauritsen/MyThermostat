all: run curses
run: run.cpp MyThermostat.cpp MyThermostat.hpp all.hpp Setpoint.cpp
	c++ -o run run.cpp MyThermostat.cpp Setpoint.cpp

curses: all.hpp MyThermostat.cpp MyThermostat.hpp Setpoint.cpp curses.cpp
	c++ curses.cpp MyThermostat.cpp Setpoint.cpp -o curses -lncurses

clean:
	rm -f *.o *.err *.out core run *.gch ncurses curses
