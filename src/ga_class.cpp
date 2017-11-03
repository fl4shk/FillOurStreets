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
	}
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

void crossover(std::string& geno_a, std::string& geno_b, 
	size_t start_index, size_t past_end_index);
void Ga::mutate(std::string& geno, size_t start_index, 
	size_t past_end_index)
{
	for (size_t i=start_index; i<past_end_index; ++i)
	{
		geno.at(i) = get_random_printable_char();
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

	return ret;
}


size_t Ga::tournament(size_t start_index, size_t past_end_index) const
{
	size_t ret_index = start_index;

	for (size_t i=start_index+1; i<past_end_index; ++i)
	{
		if (fitness(genomes().at(ret_index))
			< fitness(genomes().at(i)))
		{
			ret_index = i;
		}
	}

	return ret_index;
}
