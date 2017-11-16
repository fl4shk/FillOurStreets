#include "ga_class.hpp"

Ga::Ga(const std::string& s_to_find, size_t s_pop_size, 
	double s_crossover_rate, double s_mutation_rate, 
	bool s_use_all_printable_chars)
	: __to_find(s_to_find), __pop_size(s_pop_size),
	__crossover_rate(s_crossover_rate), __mutation_rate(s_mutation_rate),
	__use_all_printable_chars(s_use_all_printable_chars)
{
	for (char c : to_find())
	{
		__valid_chars_set.insert(c);
	}

	__genomes.resize(pop_size());

	__num_iterations = 0;

	do
	{
		for (auto& geno : genomes())
		{
			geno.resize(max_past_end_index());
			randomize_genome(geno);
			//geno.at(4) = ' ';
			//geno.at(9) = ' ';
			//geno.at(14) = ' ';
		}
	} while (current_best_fitness() == 0);

	//printout("\n");

	//print_genomes();
	//printout("\n");

	//crossover(genomes().at(0), genomes().at(1), 
	//	genomes().at(0), genomes().at(1),
	//	5, 7);
	//printout("\n");

	//__make_selection_vec();
}

Ga::~Ga()
{
}

void Ga::print_genomes() const
{
	const auto some_best_fitness = current_best_fitness();
	for (const auto& geno : genomes())
	{
		//printout(geno, ":  ", fitness(geno), "\n");
		printout(geno, 
			"\t\tcurrent_best_fitness():  ", some_best_fitness, 
			"\t\tfitness:  ", fitness(geno), 
			"\n");
	}
}
const std::string Ga::get_solution() const
{
	for (const auto& geno : genomes())
	{
		if (fitness(geno) == max_fitness())
		{
			return geno;
		}
	}

	return "";
}

int Ga::operator () ()
{
	//for (size_t i=0; i<20; ++i)
	while (!has_reached_max_fitness())
	{
		iterate();
		print_genomes();
		//printout("\n");
	}

	return 0;
}

size_t Ga::fitness(const std::string& geno) const
{
	if (geno.size() != max_past_end_index())
	{
		printerr(strappcom2(geno.size(), max_past_end_index()), "\n");
		printerr("Ga::fitness():  Eek!\n");
		exit(1);
	}

	std::vector<size_t> num_consecutive_substrs;
	size_t ret = 0;

	for (size_t i=0; i<geno.size(); ++i)
	{
		if (geno.at(i) == to_find().at(i))
		{
			//++ret;
			//ret += 2;
			//ret += to_find().size();
			++ret;
		}
	}

	size_t consec = 0;

	for (size_t i=0; i<geno.size(); ++i)
	{
		if (geno.at(i) == to_find().at(i))
		{
			++consec;
		}
		else
		{
			num_consecutive_substrs.push_back(consec);
			consec = 0;
		}
	}
	if (consec != 0)
	{
		num_consecutive_substrs.push_back(consec);
	}

	{
	size_t temp = 0;
	for (const auto& iter : num_consecutive_substrs)
	{
		//ret += iter;
		if (temp < iter)
		{
			temp = iter;
		}
	}

	ret += temp;
	}

	return ret;
}

size_t Ga::current_best_fitness() const
{
	size_t ret = 0;
	for (const auto& geno : genomes())
	{
		const size_t some_fitness = fitness(geno);
		if (ret < some_fitness)
		{
			ret = some_fitness;
		}
	}

	return ret;
}

void Ga::__raw_crossover(const std::string& geno_a, 
	const std::string& geno_b, 
	std::string& out_geno_a, std::string& out_geno_b,
	size_t start_index, size_t past_end_index)
{
	std::string temp_geno_a = geno_a;
	std::string temp_geno_b = geno_b;

	for (size_t i=start_index; i<past_end_index; ++i)
	{
		// For safety
		if (i >= max_past_end_index())
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

void Ga::crossover_or_copy()
{
	size_t index_a = -1, index_b = -1;

	do
	{
		select_two(index_a, index_b);
	} while (index_a == index_b);

	if (!can_crossover())
	{
		if (!(prng() % 2))
		{
			next_genomes().push_back(genomes().at(index_a));
		}
		else
		{
			next_genomes().push_back(genomes().at(index_b));
		}
		//next_genomes().push_back(genomes().at(index_b));
	}
	else
	{
		std::string out_geno_a, out_geno_b;

		//__raw_crossover(genomes().at(index_a), genomes().at(index_b),
		//	out_geno_a, out_geno_b,
		//	(prng() % genomes().front().size()), genomes().front().size());

		{
			//const auto val_0 = (prng() % genomes().front().size()),
			//	val_1 = (prng() % genomes().front().size());
			const auto val_0 = (prng() % genomes().front().size()),
				val_1 = genomes().front().size() - 1;

			if (val_0 < val_1)
			{
				//__raw_mutate(old_next_genome, next_genomes().at(index),
				//	val_0, val_1 + 1);
				__raw_crossover(genomes().at(index_a),
					genomes().at(index_b),
					out_geno_a, out_geno_b,
					val_0, val_1 + 1);
			}
			else
			{
				//__raw_mutate(old_next_genome, next_genomes().at(index),
				//	val_1, val_0 + 1);
				__raw_crossover(genomes().at(index_a),
					genomes().at(index_b),
					out_geno_a, out_geno_b,
					val_1, val_0 + 1);
			}
		}

		if ((next_genomes().size() + 1) == genomes().size())
		{
			if (!(prng() % 2))
			{
				next_genomes().push_back(out_geno_a);
			}
			else
			{
				next_genomes().push_back(out_geno_b);
			}
		}
		else
		{
			next_genomes().push_back(out_geno_a);
			next_genomes().push_back(out_geno_b);
		}
	}
}

void Ga::__raw_mutate(const std::string& geno, std::string& out_geno, 
	size_t start_index, size_t past_end_index)
{
	out_geno = geno;

	for (size_t i=start_index; i<past_end_index; ++i)
	{
		//out_geno.at(i) = get_random_printable_char();
		out_geno.at(i) = get_random_valid_char();
	}
}

void Ga::mutate_maybe(size_t index)
{
	//next_genomes().at(index) = genomes().at(index);
	if (!can_mutate())
	{
		return;
	}

	const std::string old_next_genome = next_genomes().at(index);

	//__raw_mutate(old_next_genome, next_genomes().at(index),
	//	(prng() % old_next_genome.size()), old_next_genome.size());

	//const auto val_0 = (prng() % old_next_genome.size()),
	//	val_1 = (prng() % old_next_genome.size());
	const int val_0 = 0,
		val_1 = old_next_genome.size() - 1;

	if (val_0 < val_1)
	{
		__raw_mutate(old_next_genome, next_genomes().at(index),
			val_0, val_1 + 1);
	}
	else
	{
		__raw_mutate(old_next_genome, next_genomes().at(index),
			val_1, val_0 + 1);
	}
}


void Ga::select_two(size_t& out_index_a, size_t& out_index_b)
{
	out_index_a = selection_vec().at(prng() % selection_vec().size());
	out_index_b = selection_vec().at(prng() % selection_vec().size());
}

size_t Ga::get_worst_fitness() const
{
	size_t ret = current_best_fitness();

	for (const auto& iter : genomes())
	{
		const auto temp = fitness(iter);

		if (temp < ret)
		{
			ret = temp;
		}
	}

	return ret;
}

void Ga::__make_selection_vec()
{
	std::vector<std::vector<size_t>> temp_sel_vec;
	temp_sel_vec.resize(genomes().size());

	//for (const auto& geno : genomes())
	for (size_t i=0; i<genomes().size(); ++i)
	{
		//temp_sel_vec.at(i).resize(fitness(genomes().at(i)));
		//temp_sel_vec.at(i).resize(fitness(genomes().at(i)) * 2);
		//temp_sel_vec.at(i).resize(fitness(genomes().at(i)) * 3);
		//temp_sel_vec.at(i).resize(fitness(genomes().at(i)) * 2);
		temp_sel_vec.at(i).resize(fitness(genomes().at(i)));

		//// Need to have each thing represented by at least one part of the
		//// pie.
		//if (temp_sel_vec.at(i).size() == 0)
		//{
		//	temp_sel_vec.at(i).push_back(i);
		//}

		//else
		{
			for (auto& temp_sel : temp_sel_vec.at(i))
			{
				temp_sel = i;
			}
		}
	}

	//for (const auto& temp_vec : temp_sel_vec)
	//{
	//	for (const auto& temp_sel : temp_vec)
	//	{
	//		printout(temp_sel, ", ");
	//	}
	//	printout("\n");
	//}

	selection_vec().clear();
	for (const auto& temp_vec : temp_sel_vec)
	{
		for (const auto& temp_sel : temp_vec)
		{
			selection_vec().push_back(temp_sel);
		}
	}
}

void Ga::iterate()
{
	next_genomes().clear();
	//next_genomes().resize(genomes().size());

	__make_selection_vec();

	while (next_genomes().size() < genomes().size())
	{
		crossover_or_copy();
	}

	{
	const auto best_fitness = current_best_fitness();
	for (size_t i=0; i<next_genomes().size(); ++i)
	{
		if (fitness(genomes().at(i)) != best_fitness)
		{
			mutate_maybe(i);
		}
	}
	}

	genomes() = std::move(next_genomes());

	++__num_iterations;
}



//char Ga::get_random_printable_char()
char Ga::get_random_valid_char()
{
	char ret;

	if (!use_all_printable_chars())
	{
		do
		{
			const auto rand_val = prng();
			ret = static_cast<char>(rand_val % (sizeof(char) << 8));
		} while (valid_chars_set().count(ret) == 0);
	}
	else
	{
		do
		{
			const auto rand_val = prng();
			ret = static_cast<char>(rand_val % (sizeof(char) << 8));
		} while (!isprint(ret));
	}

	//while (!isprint(ret));
	//while (!(ret >= 'a' && ret <= 'z'));
	//while (!isalpha(ret));
	//while (!(ret >= 'A' && ret <= 'Z'));
	//while (!(isalnum(ret)));

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
