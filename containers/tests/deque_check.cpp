#include "../ft_deque.hpp"
#include <deque>
#include <string>
#include <iostream>

template<class st_, class my_>
void print_deq(st_& st, my_& my){
	unsigned int cnt = 0;
	while (cnt < st.size())
		std::cout << st[cnt++] << " ";
	std::cout << " |st " << st.size() << std::endl;
	cnt = 0;
	while (cnt < my.size())
		std::cout << my[cnt++] << " ";
	std::cout << " |my " << my.size() << std::endl;}

void deque_check(void)
{
	std::deque<std::string> st(3, "hw");
	ft::deque<std::string> my(3, "hw");
	print_deq(st, my);
	
	std::cout << std::endl << "Assign" << std::endl;
	my.assign(4, "hello");
	st.assign(4, "World");
	print_deq(st, my);
	std::cout << "re-Assign" << std::endl;
	my.assign(st.begin(), st.end());
	print_deq(st, my);
	
	std::cout << std::endl << "copy construct" << std::endl;
	std::deque<std::string> st2(st);
	ft::deque<std::string> my2(my);
	print_deq(st2, my2);
	
	std::cout << std::endl << "Front = Hello & Back = Now" << std::endl;
	st.front() = "Hello";
	my.front() = "Hello";
	st.back() = "Now";
	my.back() = "Now";
	print_deq(st, my);
	
	std::cout << std::endl << "Push_front & push_back" << std::endl;
	st2.push_front("start");
	st2.push_back("end");
	my2.push_front("start");
	my2.push_back("end");
	print_deq(st2, my2);
	
	std::cout << std::endl << "Front = Hello & Back = Now" << std::endl;
	st.pop_front();
	my.pop_front();
	st.pop_back();
	my.pop_back();
	print_deq(st, my);
	
	std::cout << std::endl << "Insert" << std::endl;
	st.insert(++st.begin(), "Hello");
	my.insert(++my.begin(), "Hello");
	print_deq(st, my); std::cout << std::endl;
	st.insert(++st.begin(), 5, "hw");
	my.insert(++my.begin(), 5, "hw");
	print_deq(st, my); std::cout << std::endl;
	st.insert(--st.end(), st2.begin(), st2.end());
	my.insert(--my.end(), my2.begin(), my2.end());
	print_deq(st, my); std::cout << std::endl;
	
	std::cout << std::endl << "Erase" << std::endl;
	std::deque<std::string>::iterator st_it = st.begin();
	ft::deque<std::string>::iterator my_it = my.begin();
	st_it += 4;
	my_it += 4;
	st.erase(st_it);
	my.erase(my_it);
	print_deq(st, my); std::cout << std::endl;
	st_it = st.begin() + 4;
	my_it = my.begin() + 4;
	std::deque<std::string>::iterator st_it2 = st_it + 4;
	ft::deque<std::string>::iterator my_it2 = my_it + 4;
	st.erase(st_it, st_it2);
	my.erase(my_it, my_it2);
	print_deq(st, my); std::cout << std::endl;
	
	std::cout << std::endl << "Operator[] & at" << std::endl;
	st2[3] = "here!";
	my2[3] = "here!";
	try {
		st2.at(999);}
	catch (std::exception& ex){
		std::cout << ex.what() << std::endl;}
		try {
	my2.at(999);}
	catch (std::exception& ex){
		std::cout << ex.what() << std::endl;}
	print_deq(st2, my2);
	
	std::cout << std::endl << "Resize" << std::endl;
	st.resize(5);
	my.resize(5);
	print_deq(st, my);
	std::cout << std::endl;
	st.resize(10, "resize");
	my.resize(10, "resize");
	print_deq(st, my);
	
	
	std::cout << std::endl << "swap" << std::endl;
	std::cout << "#1" <<std::endl;
	print_deq(st, my);
	std::cout << "#2" <<std::endl;
	print_deq(st2, my2);
	swap(st, st2);
	swap(my, my2);
	std::cout << "#1" <<std::endl;
	print_deq(st, my);
	std::cout << "#2" <<std::endl;
	print_deq(st2, my2);
	
	std::cout << std::endl << "relational operators" << std::endl;
	if (st2 != st && my2 != my)
		std::cout << "my2 != my" << std::endl;
	if (st2 < st && my2 < my)
		std::cout << "my2 < my" << std::endl;
	if (st > st2 && my > my2)
		std::cout << "my > my2" << std::endl;
	st2 = st;
	my2 = my;
	std::cout << "my2 = my" << std::endl;
	if (st2 == st && my2 == my)
		std::cout << "my2 == my" << std::endl;
}