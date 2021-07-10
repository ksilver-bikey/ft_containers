#include "../ft_map.hpp"
#include <map>
#include <string>
#include <iostream>
struct revsort{
bool operator()(const int a, const int b) const{
	if (a > b)
		return true;
	return false;}};

template<class st>
void full_map(int n, std::string str, st& sti){
	std::pair<int, std::string> pair;
	
	pair.second = str;
	while (n-- > 0){
		pair.first = n;
		sti.insert(pair);}}

template<class map_>
void print_map(map_& st)
{
	typename map_::iterator it = st.begin();
	while (it != st.end())
		std::cout << "\"" << it->first << ":" << (it++)->second << "\"  ";
	
}

template<class map_, class _map>
void print_maps(map_ st, _map my){
	print_map(st);
	std::cout << " |st" << std::endl;
	print_map(my);
	std::cout << " |my" << std::endl << std::endl;}

void map_check(void)
{
	std::cout << "Reverse" << std::endl;
	std::map<int, std::string,  revsort> st_sir;
	ft::map<int, std::string, revsort> ft_sir;
	full_map(5, "hw", st_sir);
	full_map(5, "hw", ft_sir);
	print_maps(st_sir, ft_sir);
	
	std::cout << "iteration constr" << std::endl;
	std::map<int, std::string> st_si1(st_sir.begin(), st_sir.end());
	ft::map<int, std::string> ft_si1(ft_sir.begin(), ft_sir.end());
	print_maps(st_si1, ft_si1);
	
	std::cout << "copy constr" << std::endl;
	full_map(7, "Hello", st_si1);
	full_map(7, "Hello", ft_si1);
	std::map<int, std::string> st_si2(st_si1);
	ft::map<int, std::string> ft_si2(ft_si1);
	print_maps(st_si2, ft_si2);
	
	std::map<int, std::string>::reverse_iterator srit = st_si2.rbegin();
	ft::map<int, std::string>::reverse_iterator frit = ft_si2.rbegin();
	
	std::cout << "Reverse itterator" << std::endl;
	while (frit != ft_si2.rend())
		std::cout << (srit++)->first << " st | my " << (frit++)->first << std::endl;
	
	std::cout << std::endl << st_si1.max_size() << " st max size" << std::endl;
	std::cout << ft_si1.max_size() << " my max size" << std::endl << std::endl;
	
	std::cout << "Erase" << std::endl;
	std::map<int, std::string>::iterator sit = st_si2.begin();
	ft::map<int, std::string>::iterator fit = ft_si2.begin();
	std::map<int, std::string>::iterator sit2 = --st_si2.end();
	ft::map<int, std::string>::iterator fit2 = --ft_si2.end();
	st_si2.erase(2);
	ft_si2.erase(2);
	print_maps(st_si2, ft_si2);
	for (int i = 3; i > 0; i--){
		++sit; ++fit;}
	st_si2.erase(sit);
	ft_si2.erase(fit);
	print_maps(st_si2, ft_si2);
	sit = st_si2.begin();
	fit = ft_si2.begin();
	++sit; ++fit;
	st_si2.erase(sit, sit2);
	ft_si2.erase(fit, fit2);
	print_maps(st_si2, ft_si2);
	
	std::cout << "Insert" << std::endl << "_si1" << std::endl;
	print_maps(st_si1, ft_si1);
	sit = ++st_si1.begin();
	fit = ++ft_si1.begin();
	sit2 = --st_si1.end();
	fit2 = --ft_si1.end();
	++sit; ++fit;
	--sit2; --fit2;
	st_si2.insert(sit, sit2);
	ft_si2.insert(fit, fit2);
	print_maps(st_si2, ft_si2);
	
	std::pair<int, std::string> pair_;
	pair_.first = 777;
	pair_.second = "World";
	st_si2.insert(pair_);
	ft_si2.insert(pair_);
	if (st_si2.insert(pair_).second == false)
		std::cout << st_si2.insert(pair_).first->first << \
									" already here" << std::endl;
	if (ft_si2.insert(pair_).second == false)
		std::cout << ft_si2.insert(pair_).first->first << \
									" already here" << std::endl;
	print_maps(st_si2, ft_si2);
	
	pair_.first = 308;
	pair_.second = "onemore";
	st_si2.insert(sit2, pair_);
	ft_si2.insert(fit2, pair_);
	print_maps(st_si2, ft_si2);
	pair_.first = 333;
	pair_.second = "inclusive";
	//st_si2.insert(333, "exclusive");
	st_si2.insert(sit2, pair_);
	ft_si2.insert(333, "exclusive");
	print_maps(st_si2, ft_si2);
	std::map<int, std::string>::key_compare s_comp = st_si2.key_comp();
	ft::map<int, std::string>::key_compare f_comp = ft_si2.key_comp();
	if (f_comp(500, 1500) && s_comp(500, 1500) && \
				!f_comp(2500, 1500) && !s_comp(2500, 1500))
		std::cout << "comps work" << std::endl;
	
	
	std::pair<int, std::string> pair_2;
	std::map<int, std::string>::value_compare sv_comp = st_si1.value_comp();
	ft::map<int, std::string>::value_compare fv_comp = ft_si1.value_comp();
	pair_2.first = 403;
	pair_2.second = "inclusive";
	std::cout << sv_comp(pair_, pair_2) << std::endl;
	std::cout << fv_comp(pair_, pair_2) << std::endl;
	std::cout << "value comps work" << std::endl;
	
	std::cout << std::endl << "Operator[]" << \
						std::endl << "_si2[308]" << std::endl;
	std::cout << st_si2[308] << " -st | my- " << ft_si2[308] << std::endl;
	std::cout << "_si2[5]" << std::endl;
	std::cout << st_si2[5] << " -st | my- " << ft_si2[5] << std::endl;
	
	std::cout << std::endl << "Clear()" << std::endl;
	print_maps(st_sir, ft_sir);
	st_sir.clear();
	ft_sir.clear();
	print_maps(st_sir, ft_sir);
	st_si2[5] = "five here";
	ft_si2[5] = "five here";
	std::cout << std::endl << "Count(308)" << std::endl;
	std::cout << st_si2.count(308) << " -st | my- " << ft_si2.count(308)\
														<< std::endl;
	std::cout << "Count(309)" << std::endl;
	std::cout << st_si2.count(309) << " -st | my- " << ft_si2.count(309)\
														<< std::endl;
	print_maps(st_si2, ft_si2);
	
	std::cout << std::endl << "lower_bound(5)" << std::endl;
	std::cout << st_si2.lower_bound(5)->first << ":"\
		<< st_si2.lower_bound(5)->second << " -st | my- ";
	std::cout << ft_si2.lower_bound(5)->first << ":"\
		<< ft_si2.lower_bound(5)->second << std::endl;
		
	std::cout << std::endl << "upper_bound(5)" << std::endl;
	std::cout << st_si2.upper_bound(5)->first << ":"\
		<< st_si2.upper_bound(5)->second << " -st | my- ";
	std::cout << ft_si2.upper_bound(5)->first << ":"\
		<< ft_si2.upper_bound(5)->second << std::endl;
		
	std::cout << std::endl << "equal_range(308)" << std::endl;
	std::cout << "first" << std::endl;
	std::cout << st_si2.equal_range(308).first->first << ":"\
		<< st_si2.equal_range(308).first->second << " -st | my- ";
	std::cout << ft_si2.equal_range(308).first->first << ":"\
		<< ft_si2.equal_range(308).first->second << std::endl;
		std::cout << "second" << std::endl;
	std::cout << st_si2.equal_range(308).second->first << ":"\
		<< st_si2.equal_range(308).second->second << " -st | my- ";
	std::cout << ft_si2.equal_range(308).second->first << ":"\
		<< ft_si2.equal_range(308).second->second << std::endl;
		
	
	std::cout << std::endl << "swap()" << std::endl;
	std::cout << "t_si1" << std::endl;
	print_maps(st_si1, ft_si1);
	std::cout << "t_si2" << std::endl;
	print_maps(st_si2, ft_si2);
	swap(st_si1, st_si2);
	std::cout << "swaped" << std::endl;
	swap(ft_si1, ft_si2);
	std::cout << "t_si1" << std::endl;
	print_maps(st_si1, ft_si1);
	std::cout << "t_si2" << std::endl;
	print_maps(st_si2, ft_si2);
	
	std::cout << std::endl << "relational operators" << std::endl;
	if (st_si2 != st_si1 && ft_si2 != ft_si1)
		std::cout << "ft_si2 != ft_si1" << std::endl;
	if (st_si2 < st_si1 && ft_si2 < ft_si1)
		std::cout << "ft_si2 < ft_si1" << std::endl;
	if (st_si1 > st_si2 && ft_si1 > ft_si2)
		std::cout << "ft_si1 > ft_si2" << std::endl;
	st_si2 = st_si1;
	ft_si2 = ft_si1;
	std::cout << "ft_si2 = ft_si1" << std::endl;
	if (st_si2 == st_si1 && ft_si2 == ft_si1)
		std::cout << "ft_si2 == ft_si1" << std::endl;
}
