all: run curses

Setpoint.o: MyThermostat.hpp all.hpp Setpoint.cpp
	c++ -c Setpoint.cpp

MyThermostat.o: all.hpp MyThermostat.cpp MyThermostat.hpp
	c++ -c MyThermostat.cpp

run.o: run.cpp all.hpp 
	c++ -c run.cpp

run: run.o MyThermostat.o Setpoint.o
	c++ -o run run.o MyThermostat.o Setpoint.o

curses.o: curses.cpp MyThermostat.hpp all.hpp
	c++ -c curses.cpp

curses: curses.o MyThermostat.o Setpoint.o
	c++ curses.o MyThermostat.o Setpoint.o -o curses -lncurses

clean:
	rm -f *.o *.err *.out core run *.gch ncurses curses
