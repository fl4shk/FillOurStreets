#ifndef ga_class_hpp
#define ga_class_hpp

#include "misc_includes.hpp"

class Ga
{
private:		// variables
	std::string __to_find;
	Prng __prng;


	std::vector<std::string> __genomes;

	size_t __pop_size; 
	double __crossmut_rate;


public:		// functions
	Ga(const std::string& s_to_find, size_t s_pop_size=20, 
		double s_crossmut_rate=0.25);
	~Ga();


	gen_getter_by_con_ref(to_find);

	int operator () ();


private:		// functions
	gen_getter_by_ref(genomes);
	gen_getter_and_setter_by_val(pop_size);
	gen_getter_and_setter_by_val(crossmut_rate);

	size_t fitness(const std::string& some_genome) const;
	inline size_t max_fitness() const
	{
		return to_find().size();
	}

	void crossover(std::string& a, std::string& b);
	void mutate(std::string& a, std::string& b);
	void randomize_genome(std::string& a);

	inline auto prng()
	{
		return __prng();
	}

};

#endif		// ga_class_hpp
