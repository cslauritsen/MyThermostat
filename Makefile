all: run
run: run.cpp MyThermostat.cpp MyThermostat.h all.hpp
	c++ -o run run.cpp MyThermostat.cpp

clean:
	rm -f *.o *.err *.out core run
