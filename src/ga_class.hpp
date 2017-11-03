#ifndef ga_class_hpp
#define ga_class_hpp

#include "misc_includes.hpp"

class Ga
{
private:		// variables
	std::string __to_find;
	Prng __prng;


public:		// functions
	Ga(const std::string& s_to_find);
	~Ga();


	gen_getter_by_con_ref(to_find);

	int operator () ();


private:		// functions
	inline auto prng()
	{
		return __prng();
	}

};

#endif		// ga_class_hpp
