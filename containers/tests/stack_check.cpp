#include "../ft_stack.hpp"
#include <stack>
#include <string>
#include <list>
#include <vector>
#include <iostream>

template <class st_, class my_, class val_>
void stack_push(st_& st, my_& my, const val_& val){
	st.push(val);
	my.push(val);}
	
template <class st_, class my_>
void stack_read(st_& st, my_& my){
	std::cout << st.top() << " st|my " << \
	my.top() << std::endl;}
	
template <class st_, class my_>
void stack_pop(st_& st, my_& my){
	st.pop();
	my.pop();}
	
template <class st_, class my_>
void stack_sizes(st_& st, my_& my){
	std::cout << st.size() << " }st size|my size{ " << \
	my.size() << std::endl;}
	

void stack_check(void)
{
	std::cout << "Stack with list" << std::endl;
	std::stack<std::string, std::list<std::string> > st;
	ft::stack<std::string, ft::list<std::string> > my;
	
	stack_push(st, my, "one");
	stack_push(st, my, "two");
	stack_push(st, my, "three");
	
	stack_read(st, my);
	stack_sizes(st, my);
	stack_pop(st, my);
	std::cout << "my.empty() = " << my.empty() << std::endl;
	stack_read(st, my);
	stack_sizes(st, my);
	my.pop();
	my.pop();
	my.pop();
	my.pop();
	stack_read(st, my);
	stack_sizes(st, my);
	std::cout << "my.empty() = " << my.empty() << std::endl;
	
	std::cout << std::endl << "Stack with deque" << std::endl;
	std::stack<int> st1;
	ft::stack<int> my1;
	
	stack_push(st1, my1, 1);
	stack_push(st1, my1, 2);
	stack_push(st1, my1, 3);
	
	stack_read(st1, my1);
	stack_sizes(st1, my1);
	stack_pop(st1, my1);
	std::cout << "my1.empty() = " << my1.empty() << std::endl;
	stack_read(st1, my1);
	stack_sizes(st1, my1);
	my1.pop();
	my1.pop();
	my1.pop();
	my1.pop();
	stack_read(st1, my1);
	stack_sizes(st1, my1);
	std::cout << "my1.empty() = " << my1.empty() << std::endl;
	
	std::cout << std::endl << "Stack with vector" << std::endl;
	std::stack<double, std::vector<double> > st2;
	ft::stack<double, ft::vector<double> > my2;
	
	stack_push(st2, my2, 1.5);
	stack_push(st2, my2, 2.25);
	stack_push(st2, my2, 3.1);
	
	stack_read(st2, my2);
	stack_sizes(st2, my2);
	stack_pop(st2, my2);
	std::cout << "my2.empty() = " << my2.empty() << std::endl;
	stack_read(st2, my2);
	stack_sizes(st2, my2);
	my2.pop();
	my2.pop();
	my2.pop();
	my2.pop();
	st2.pop();
	st2.pop();
	stack_read(st2, my2);
	stack_sizes(st2, my2);
	std::cout << "my2.empty() = " << my2.empty() << std::endl;
	
	std::cout << std::endl << "Stack with std::list" << std::endl;
	std::stack<std::string, std::list<std::string> > st3;
	ft::stack<std::string, ft::list<std::string> > my3;
	
	stack_push(st3, my3, "one");
	stack_push(st3, my3, "two");
	stack_push(st3, my3, "three");
	
	stack_read(st3, my3);
	stack_sizes(st3, my3);
	stack_pop(st3, my3);
	std::cout << "my3.empty() = " << my3.empty() << std::endl;
	stack_read(st3, my3);
	stack_sizes(st3, my3);
	stack_pop(st3, my3);
	stack_read(st3, my3);
	stack_sizes(st3, my3);
	stack_pop(st3, my3);
	std::cout << "my3.empty() = " << my3.empty() << std::endl;
	
} 
