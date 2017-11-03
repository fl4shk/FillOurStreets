#include "ga_class.hpp"
#include <stdlib.h>


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printerr("Usage:  ", argv[0], " pop_size crossmut_rate\n");
		exit(1);
	}

	const int pop_size = atoi(argv[1]);
	const double crossmut_rate = atof(argv[2]);

	if (pop_size <= 2)
	{
		printerr("Population size too small\n");
		exit(1);
	}

	if ((crossmut_rate <= 0.0f) || (crossmut_rate >= 1.0f))
	{
		printerr("Crossover/mutation rate must be greater than 0.0f but",
			" less than 1.0f\n");
		exit(1);
	}

	Ga ga("Banks wants to empty the banks, "
		"fill our streets with banks, "
		"and run a bank making operation out of his banks.",
		pop_size, crossmut_rate);

	return ga();
}
