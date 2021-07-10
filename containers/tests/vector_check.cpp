#include <string>
#include <vector>
#include <iostream>
#include "../ft_vector.hpp"


template <class T>
void print_vector(std::vector<T>* st, ft::vector<T>* my)
{
	int cnt = -1;
	std::cout << std::endl;
	
		while (++cnt < (int)st->size())
			std::cout << (*st)[cnt] << " ";
		std::cout << " |st " << st->size() << \
				"/" << st->capacity() << std::endl;
	cnt = -1;

		while (++cnt < (int)my->size())
			std::cout << (*my)[cnt] << " ";
		std::cout << " |my " << my->size() << \
				"/" << my->capacity() << std::endl;
}

void vector_check(void)
{
	int ints[] = {1, 2, 3, 4, 5, 6, 8, 9 ,10 , 11, 12, 13, 14};
	std::vector<int> st_one(&ints[6], ints + 11);
	ft::vector<int> my_one(&ints[6], ints + 11);
	std::cout << std::endl << "one";
	print_vector(&st_one, &my_one);
	
	std::vector<std::string> st_two(6, "hw");
	ft::vector<std::string> my_two(6, "hw");
	std::cout << std::endl << "two";
	print_vector(&st_two, &my_two);
	
	std::vector<int> st_three(st_one);
	ft::vector<int> my_three(my_one);
	std::cout << std::endl << "three";
	print_vector(&st_three, &my_three);
		
	st_two[3] = "Hello";
	my_two[3] = "Hello";
	std::cout << std::endl << "_two[3] = \"Hello\"";
	print_vector(&st_two, &my_two);
	
	//st_two[7777] = "g";
	//my_two[7777] = "g";
	
	std::cout << std::endl << "resize three";
	st_three.resize(10);
	my_three.resize(10);
	print_vector(&st_three, &my_three);
	
	std::cout << std::endl << "resize two";
	st_two.resize(2);
	my_two.resize(2);
	print_vector(&st_two, &my_two);
	
	std::cout << std::endl << "reserve three";
	st_three.reserve(30);
	my_three.reserve(30);
	print_vector(&st_three, &my_three);
	
	std::cout << std::endl << "reserve two";
	st_two.reserve(1);
	my_two.reserve(1);
	print_vector(&st_two, &my_two);
	std::cout << st_two[3] << "  " << my_two[3] << std::endl;
	
	std::cout << std::endl << "_two.at()" << std::endl;
	try {
		st_two.at(7777) = "g";}
	catch (std::out_of_range &ex){
		std::cout << "standart " << ex.what() << std::endl;}
		
	try {
		my_two.at(7777) = "g";}
	catch (std::out_of_range &ex){
		std::cout << "standart " << ex.what() << std::endl;}
	
	std::cout << std::endl << "FRONT" << std::endl;
	std::cout << "st_one: " << st_one.front() << "  ";
	std::cout << "my_one: " << my_one.front() << std::endl;
	std::cout << "BACK" << std::endl;
	std::cout << "st_one: " << st_one.back() << "  ";
	std::cout << "my_one: " << my_one.back() << std::endl;
	
	std::cout << std::endl << "_one.push_back()";
	print_vector(&st_one, &my_one);
	st_one.push_back(777);
	my_one.push_back(777);
	print_vector(&st_one, &my_one);
	
	std::cout << std::endl << "_one.pop_back()";
	st_one.pop_back();
	my_one.pop_back();
	print_vector(&st_one, &my_one);
	
	ft::vector<std::string>::iterator my_it = my_two.begin();
	std::vector<std::string>::iterator st_it = st_two.begin();
	++st_it;
	++my_it;
	std::cout << std::endl << "_two.insert()";
	st_two.insert(st_it, 3, "Hello");
	my_two.insert(my_it, 3, "Hello");
	print_vector(&st_two, &my_two);
	
	my_it = my_two.begin();
	st_it = st_two.begin();
	++st_it; ++st_it;
	++my_it; ++my_it;
	st_two.insert(st_it, "World");
	my_two.insert(my_it, "World");
	print_vector(&st_two, &my_two);
	
	std::vector<std::string> temp_str(4, "itter");
	st_two.insert(st_it, temp_str.begin(), temp_str.end());
	my_two.insert(my_it, temp_str.begin(), temp_str.end());
	print_vector(&st_two, &my_two);
	
	std::cout << std::endl << "_two.assign()";
	st_two.assign(temp_str.begin(), temp_str.end());
	my_two.assign(temp_str.begin(), temp_str.end());
	print_vector(&st_two, &my_two);
	
	st_two.assign(5, "asgn");
	my_two.assign(5, "asgn");
	print_vector(&st_two, &my_two);
	
	std::cout << std::endl << "_one.erase()";
	ft::vector<int>::iterator my_thr_it = my_three.begin() + 1;
	std::vector<int>::iterator st_thr_it = st_three.begin() + 1;	
	print_vector(&st_three, &my_three);
	st_three.erase(st_thr_it);
	my_three.erase(my_thr_it);
	print_vector(&st_three, &my_three);
	ft::vector<int>::iterator my_thr_it2 = my_three.begin() + 7;
	std::vector<int>::iterator st_thr_it2 = st_three.begin() + 7;

 	my_thr_it = my_three.begin() + 2;
	st_thr_it = st_three.begin() + 2;
	st_three.erase(st_thr_it, st_thr_it2);
	my_three.erase(my_thr_it, my_thr_it2);
	print_vector(&st_three, &my_three);
	
	std::cout << std::endl << ".clear()";
	st_one.clear();
	my_one.clear();
	print_vector(&st_one, &my_one);
	
	st_one = st_three;
	my_one = my_three;
	print_vector(&st_one, &my_one);
	if (my_one == my_three)
		std::cout << "my_one == my_three" <<std::endl;
	my_one.push_back(90);
	st_one.push_back(90);
	my_three.push_back(91);
	if (my_one != my_three)
		std::cout << "my_one != my_three" <<std::endl;
		
	if (my_one < my_three)
		std::cout << "my_one < my_three" <<std::endl;
	my_three.pop_back();
	my_three.pop_back();
	st_three.pop_back();
	if (my_one > my_three)
		std::cout << "my_one > my_three" <<std::endl;
		
		
	std::cout << std::endl << "swap(three, one)";
	print_vector(&st_three, &my_three);
	std::cout << "three" << std::endl;
	print_vector(&st_one, &my_one);
	std::cout << "one" << std::endl;
	swap(st_three, st_one);
	swap(my_three, my_one);
	print_vector(&st_three, &my_three);
	std::cout << "three" << std::endl;
	print_vector(&st_one, &my_one);
	std::cout << "one" << std::endl;
} 
