#include "../ft_queue.hpp"
#include "../ft_list.hpp"
#include <queue>
#include <string>
#include <list>
#include <vector>
#include <iostream>

template <class st_, class my_, class val_>
void queue_push(st_& st, my_& my, const val_& val){
	st.push(val);
	my.push(val);}
	
template <class st_, class my_>
void queue_read(st_& st, my_& my){
	std::cout << "front|st "  << st.front() << " | " << \
	my.front() << " my" << std::endl;
	std::cout << "back |st "  << st.back() << " | " << \
	my.back() << " my" << std::endl;}
	
template <class st_, class my_>
void queue_pop(st_& st, my_& my){
	st.pop();
	my.pop();}
	
template <class st_, class my_>
void queue_sizes(st_& st, my_& my){
	std::cout << "size |st " << st.size() << " | " << \
	my.size() << " my" << std::endl;}
	

void queue_check(void)
{
	std::cout << "queue with list" << std::endl;
	std::queue<std::string, std::list<std::string> > st;
	ft::queue<std::string, ft::list<std::string> > my;
	
	queue_push(st, my, "one");
	queue_push(st, my, "two");
	queue_push(st, my, "three");
	
	queue_read(st, my);
	queue_sizes(st, my);
	queue_pop(st, my);
	std::cout << "my.empty() = " << my.empty() << std::endl;
	std::cout << "pop" << std::endl;
	queue_read(st, my);
	queue_sizes(st, my);
	my.pop();
	my.pop();
	my.pop();
	my.pop();
	queue_read(st, my);
	queue_sizes(st, my);
	my.front() = "four";
	my.back() = "zero";
	st.front() = "four";
	st.back() = "zero";
	std::cout << "my.empty() = " << my.empty() << std::endl;
	
	std::cout << std::endl << "queue with deque" << std::endl;
	std::queue<int> st1;
	ft::queue<int> my1;
	
	queue_push(st1, my1, 1);
	queue_push(st1, my1, 2);
	queue_push(st1, my1, 3);
	
	queue_read(st1, my1);
	queue_sizes(st1, my1);
	queue_pop(st1, my1);
	std::cout << "my1.empty() = " << my1.empty() << std::endl;
	std::cout << "pop" << std::endl;
	queue_read(st1, my1);
	queue_sizes(st1, my1);
	my1.pop();
	my1.pop();
	my1.pop();
	my1.pop();
	queue_read(st1, my1);
	queue_sizes(st1, my1);
	std::cout << "my1.empty() = " << my1.empty() << std::endl;

	std::cout << std::endl << "queue with std::list" << std::endl;
	std::queue<std::string, std::list<std::string> > st3;
	ft::queue<std::string, ft::list<std::string> > my3;
	
	queue_push(st3, my3, "one");
	queue_push(st3, my3, "two");
	queue_push(st3, my3, "three");
	
	queue_read(st3, my3);
	queue_sizes(st3, my3);
	queue_pop(st3, my3);
	std::cout << "my3.empty() = " << my3.empty() << std::endl;
	std::cout << "pop" << std::endl;
	queue_read(st3, my3);
	queue_sizes(st3, my3);
	queue_pop(st3, my3);
	queue_read(st3, my3);
	queue_sizes(st3, my3);
	queue_pop(st3, my3);
	std::cout << "my3.empty() = " << my3.empty() << std::endl;
	
} 
