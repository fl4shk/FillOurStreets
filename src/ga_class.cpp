#include "ga_class.hpp"

Ga::Ga(const std::string& s_to_find, size_t s_pop_size, 
	double s_crossover_rate, double s_mutation_rate)
	: __to_find(s_to_find), __pop_size(s_pop_size),
	__crossover_rate(s_crossover_rate), __mutation_rate(s_mutation_rate)
{
	__genomes.resize(pop_size());

	for (auto& geno : genomes())
	{
		geno.resize(max_fitness());
		randomize_genome(geno);
		//geno.at(4) = ' ';
		//geno.at(9) = ' ';
		//geno.at(14) = ' ';
	}
	//printout("\n");

	//print_genomes();
	//printout("\n");

	//crossover(genomes().at(0), genomes().at(1), 
	//	genomes().at(0), genomes().at(1),
	//	5, 7);
	//printout("\n");
}

Ga::~Ga()
{
}

void Ga::print_genomes() const
{
	for (const auto& geno : genomes())
	{
		//printout(geno, ":  ", fitness(geno), "\n");
		printout(geno, "\t\tfitness:  ", fitness(geno), "\n");
	}
}

int Ga::operator () ()
{
	return 0;
}

size_t Ga::fitness(const std::string& geno) const
{
	if (geno.size() != max_fitness())
	{
		printerr("ga::fitness():  eek!\n");
		exit(1);
	}

	size_t ret = 0;

	for (size_t i=0; i<geno.size(); ++i)
	{
		if (geno.at(i) == to_find().at(i))
		{
			++ret;
		}
	}

	return ret;
}

void Ga::crossover(const std::string& geno_a, const std::string& geno_b, 
	std::string& out_geno_a, std::string& out_geno_b,
	size_t start_index, size_t past_end_index)
{
	std::string temp_geno_a = geno_a;
	std::string temp_geno_b = geno_b;

	for (size_t i=start_index; i<past_end_index; ++i)
	{
		// For safety
		if (i >= max_fitness())
		{
			printerr("Ga::crossover():  Eek! ", 
				strappcom2(start_index, past_end_index, max_fitness()),
				"\n");
			exit(1);
		}

		temp_geno_a.at(i) = geno_b.at(i);
		temp_geno_b.at(i) = geno_a.at(i);
	}

	out_geno_a = std::move(temp_geno_a);
	out_geno_b = std::move(temp_geno_b);
}

void Ga::mutate(std::string& out_geno, 
	size_t start_index, size_t past_end_index)
{
	for (size_t i=start_index; i<past_end_index; ++i)
	{
		out_geno.at(i) = get_random_printable_char();
	}
}


char Ga::get_random_printable_char()
{
	char ret;

	do
	{
		const auto rand_val = prng();
		ret = static_cast<char>(rand_val % (sizeof(char) << 8));
	} while (!isprint(ret));
	//while (!(ret >= 'a' && ret <= 'z'));
	//while (!isalpha(ret));
	//while (!(ret >= 'A' && ret <= 'Z'));

	return ret;
}


//size_t Ga::tournament(size_t start_index, size_t past_end_index) const
//{
//	size_t ret_index = start_index;
//
//	for (size_t i=start_index+1; i<past_end_index; ++i)
//	{
//		if (fitness(genomes().at(ret_index))
//			< fitness(genomes().at(i)))
//		{
//			ret_index = i;
//		}
//	}
//
//	return ret_index;
//}
