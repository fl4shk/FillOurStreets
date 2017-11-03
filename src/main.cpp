#include "ga_class.hpp"
#include <stdlib.h>

void tester(const double crossover_rate, const double mutation_rate);

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

	//tester(crossover_rate, mutation_rate);



	//Ga ga("Banks wants to empty the banks, "
	//	"fill our streets with banks, "
	//	"and run a bank making operation out of his banks.",
	//	pop_size, crossover_rate, mutation_rate);

	Ga ga("0ooo oooo aaaa bbbb",
		pop_size, crossover_rate, mutation_rate);

	ga.print_genomes();

	return ga();
}



void tester(const double crossover_rate, const double mutation_rate)
{
	//static constexpr double scale_amount = 100'000'000;
	static constexpr double scale_amount = 100;
	//Prng prng;

	//for (size_t i=0; i<5; ++i)
	for (double some_val=0.0f; some_val<100.0f; some_val+=0.1f)
	{
		//const double some_val = static_cast<double>(prng());

		printout(//some_val, ":  ", 
			((fmod(some_val, scale_amount)) / scale_amount), 

			"\t\t",


			//strappcom2
			//(crossover_rate,
			//mutation_rate), 

			//"\t\t",

			strappcom2
			(val_meets_percentage(some_val, scale_amount, crossover_rate),
			val_meets_percentage(some_val, scale_amount, mutation_rate)),
			"\n");
	}
}
