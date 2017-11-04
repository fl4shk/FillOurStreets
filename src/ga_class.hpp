#ifndef ga_class_hpp
#define ga_class_hpp

#include "misc_includes.hpp"


inline bool val_meets_percentage
	(double val, double scale_amount, double percentage)
{
	const double rem = fmod(val, scale_amount);
	const double scaled_percentage = percentage * scale_amount;

	return (rem < scaled_percentage);
}

class Ga
{
public:		// constants
	static constexpr double crossmut_scale_amount = 100'000'000;

private:		// variables
	std::string __to_find;
	Prng __prng;

	size_t __num_iterations = 0;

	std::vector<std::string> __genomes, __next_genomes;
	std::vector<size_t> __selection_vec;
	std::set<char> __valid_chars_set;

	size_t __pop_size; 
	double __crossover_rate, __mutation_rate;
	bool __use_all_printable_chars;




public:		// functions
	Ga(const std::string& s_to_find, size_t s_pop_size=300, 
		double s_crossover_rate=0.7f, double s_mutation_rate=0.01f,
		bool s_use_all_printable_chars=false);
	~Ga();


	void print_genomes() const;

	const std::string get_solution() const;

	int operator () ();

	gen_getter_by_con_ref(to_find);
	gen_getter_by_val(num_iterations);
	gen_getter_by_con_ref(valid_chars_set);
	gen_getter_by_con_ref(genomes);
	gen_getter_by_con_ref(next_genomes);
	gen_getter_by_val(use_all_printable_chars);


private:		// functions
	gen_getter_by_ref(genomes);
	gen_getter_by_ref(next_genomes);
	gen_getter_by_ref(selection_vec);
	gen_getter_by_con_ref(selection_vec);
	gen_getter_and_setter_by_val(pop_size);
	gen_getter_and_setter_by_val(crossover_rate);
	gen_getter_and_setter_by_val(mutation_rate);


	size_t fitness(const std::string& geno) const;
	inline size_t max_fitness() const
	{
		return to_find().size() * 2;
	}
	size_t current_best_fitness() const;
	inline size_t max_past_end_index() const
	{
		return to_find().size();
	}

	inline bool has_reached_max_fitness() const
	{
		return (current_best_fitness() == max_fitness());
	}


	void __raw_crossover(const std::string& geno_a, 
		const std::string& geno_b, 
		std::string& out_geno_a, std::string& out_geno_b,
		size_t start_index, size_t past_end_index);
	void crossover_or_copy();
	void __raw_mutate(const std::string& geno, std::string& out_geno, 
		size_t start_index, size_t past_end_index);
	void mutate_maybe(size_t index);
	void select_two(size_t& out_index_a, size_t& out_index_b);
	void __make_selection_vec();

	void iterate();


	inline void randomize_genome(std::string& out_geno)
	{
		if (out_geno.size() != max_past_end_index())
		{
			printerr("Ga::randomize_genome():  Eek!\n");
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
		__raw_mutate(out_geno, out_geno, 0, out_geno.size());
	}

	//char get_random_printable_char();
	char get_random_valid_char();

	inline auto prng()
	{
		return __prng();
	}

	inline bool can_crossover()
	{
		return __can_crossmut(crossover_rate());
	}
	inline bool can_mutate()
	{
		return __can_crossmut(mutation_rate());
	}
	inline bool __can_crossmut(double percentage)
	{
		return val_meets_percentage(static_cast<double>(prng()), 
			crossmut_scale_amount, percentage);
	}


	//size_t tournament(size_t start_index, size_t past_end_index) const;
};

#endif		// ga_class_hpp
