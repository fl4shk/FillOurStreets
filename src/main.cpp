#include "ga_class.hpp"
#include <stdlib.h>


int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printerr("Usage:  ", argv[0], " pop_size crossover_rate ",
			"mutation_rate\n");
		exit(1);
	}

	const int pop_size = atoi(argv[1]);
	const double crossover_rate = atof(argv[2]);
	const double mutation_rate = atof(argv[3]);

	if (pop_size <= 2)
	{
		printerr("Population size too small (must be at least 3)\n");
		exit(1);
	}

	if ((crossover_rate <= 0.0f) || (crossover_rate >= 1.0f)
		|| (mutation_rate <= 0.0f) || (mutation_rate >= 1.0f))
	{
		printerr("Crossover and mutation rates must be ",
			"greater than 0.0f but less than 1.0f\n");
		exit(1);
	}

	Ga ga("Banks wants to empty the banks, "
		"fill our streets with banks, "
		"and run a bank making operation out of his banks.",
		pop_size, crossover_rate, mutation_rate);

	ga.print_genomes();

	return ga();
}
