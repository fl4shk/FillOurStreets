#include "ga_class.hpp"

Ga::Ga(const std::string& s_to_find, size_t s_pop_size, 
	double s_crossmut_rate)
	: __to_find(s_to_find), __pop_size(s_pop_size),
	__crossmut_rate(s_crossmut_rate)
{
}

Ga::~Ga()
{
}

int Ga::operator () ()
{
	return 0;
}

size_t Ga::fitness(const std::string& some_genome) const
{
	if (some_genome.size() != max_fitness())
	{
		printerr("Ga::fitness():  Eek!\n");
		exit(1);
	}

	size_t ret = 0;

	for (size_t i=0; i<some_genome.size(); ++i)
	{
		if (some_genome.at(i) == to_find().at(i))
		{
			++ret;
		}
	}

	return ret;
}
