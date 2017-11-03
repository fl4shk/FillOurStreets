#ifndef ga_class_hpp
#define ga_class_hpp

#include "misc_includes.hpp"

class Ga
{
private:		// variables
	std::string __to_find;
	Prng __prng;


	std::vector<std::string> __genomes, __next_genomes;

	size_t __pop_size; 
	double __crossover_rate, __mutation_rate;


public:		// functions
	Ga(const std::string& s_to_find, size_t s_pop_size=20, 
		double s_crossover_rate=0.7f, double s_mutation_rate=0.25f);
	~Ga();


	gen_getter_by_con_ref(to_find);
	void print_genomes() const;

	int operator () ();

	gen_getter_by_con_ref(genomes);
	gen_getter_by_con_ref(next_genomes);


private:		// functions
	gen_getter_by_ref(genomes);
	gen_getter_by_ref(next_genomes);
	gen_getter_and_setter_by_val(pop_size);
	gen_getter_and_setter_by_val(crossover_rate);
	gen_getter_and_setter_by_val(mutation_rate);


	size_t fitness(const std::string& geno) const;
	inline size_t max_fitness() const
	{
		return to_find().size();
	}


	void crossover(const std::string& geno_a, const std::string& geno_b, 
		std::string& out_geno_a, std::string& out_geno_b,
		size_t start_index, size_t past_end_index);
	void mutate(std::string& out_geno, 
		size_t start_index, size_t past_end_index);
	inline void randomize_genome(std::string& out_geno)
	{
		if (out_geno.size() != max_fitness())
		{
			printerr("ga::fitness():  eek!\n");
			exit(1);
		}

		////do
		////{
		//	for (size_t i=0; i<max_fitness(); ++i)
		//	{
		//		out_geno.at(i) = get_random_printable_char();
		//	}
		////} while (fitness(out_geno) < 10);

		////printout(out_geno, ":  ", fitness(out_geno), "\n");
		mutate(out_geno, 0, max_fitness());
	}

	char get_random_printable_char();

	inline auto prng()
	{
		return __prng();
	}


	size_t tournament(size_t start_index, size_t past_end_index) const;
};

#endif		// ga_class_hpp
