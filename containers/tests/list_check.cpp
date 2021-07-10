#include "../ft_list.hpp"
#include <list>
#include <iostream>
#include <cmath>

#define asize(x) sizeof(x)/sizeof(x[0])

bool revsort(const int a, const int b)
	{
		if (a > b)
			return true;
		return false;
	}

bool is_near (double first, double second)
  { return (fabs(first-second)<5.0); }
 
template <class stl, class myl>
void print_list(stl& st, myl& my)
{
	typename stl::iterator stit = st.begin();
	typename myl::iterator myit = my.begin();
	
	while (stit != st.end())
		std::cout << *stit++ << " ";
	
	std::cout << "|st " << st.size() << std::endl;
	while (myit != my.end())
		std::cout << *myit++ << " ";
	std::cout << "|my " << my.size() << std::endl;
}


template <class T>
void print_reverse(std::list<T> st, ft::list<T> my)
{
	typename std::list<T>::reverse_iterator stit = st.rbegin();
	typename ft::list<T>::reverse_iterator myit = my.rbegin();
	
	while (myit != my.rend())
	{
		std::cout << *stit++;
		std::cout.width(15);
		std::cout << *myit++ << std::endl;
	}
	std::cout << "end list" << std::endl;
}

void list_checking(void)
{
	std::list<std::string> st(5, "st");
	ft::list<std::string> my(5, "my");
	print_list(st, my);
	
	ft::list<std::string> my1(st.begin(), st.end());
	*my1.begin() = "toto";
	*(--my1.end()) = "tutu";
	*st.begin() = "toto";
	*(--st.end()) = "tutu";
	print_list(st, my1);
	std::cout << std::endl;
	
	std::cout << "Pop back" << std::endl;
	my1.pop_back();
	st.pop_back();
	print_list(st, my1);
	std::cout << std::endl;

	std::cout << "Pop front" << std::endl;
	my1.pop_front();
	st.pop_front();
	print_list(st, my1);
	my1.pop_front();
	my1.pop_front();
	my1.pop_front();
	my1.pop_front();
	my1.pop_front();
	my1.pop_front();
	my1.pop_back();
	my1.pop_back();
	my1.pop_back();
	
	
	int myints[] = {1, 2, 3, 4, 5, 6};
	int myints1[] = {11, 21, 31, 41, 51, 61, 71, 81};
	int myints2[] = {120, 220, 320};
	std::list<int> sti;
	ft::list<int> myi;
	
	if (sti.empty() && myi.empty())
		std::cout << "myi is empty" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Assign" << std::endl;
	sti.assign(myints, myints + asize(myints));
	myi.assign(myints, myints + asize(myints));
	print_list(sti, myi);
	print_reverse<int>(sti, myi);
	std::cout << std::endl;
	
	
	sti.assign(myints1, myints1 + asize(myints1));
	myi.assign(myints1, myints1 + asize(myints1));
	print_list(sti, myi);
	std::cout << std::endl;
	
	sti.assign(myints2, myints2 + asize(myints2));
	myi.assign(myints2, myints2 + asize(myints2));
	print_list(sti, myi);
	
	
	std::cout << std::endl << "Resize + Insert" << std::endl;
	sti.resize(1);
	myi.resize(1);
	print_list(sti, myi);
	std::list<int> sti1(sti);
	ft::list<int> myi1(myi);
	sti1.push_back(8888);
	myi1.push_back(8888);
	

	sti1.insert(sti1.end(), myints1, myints1 + asize(myints1));
	myi1.insert(myi1.end(), myints1, myints1 + asize(myints1));
	print_list(sti1, myi1);
	sti1.insert(++sti1.begin(), myints, myints + asize(myints));
	myi1.insert(++myi1.begin(), myints, myints + asize(myints));
	print_list(sti1, myi1);
	sti = sti1;
	myi = myi1;
	print_list(sti, myi);
	std::cout << std::endl;
	std::cout << "st max size " << st.max_size() << std::endl;
	std::cout << "my max size " << my.max_size() << std::endl;
	
	std::cout << std::endl << "SWAP" << std::endl;
	myi.front() = 10000000;
	myi1.front() = 11111111;
	myi.resize(5);
	myi1.resize(5);
	myi.swap(myi1);
	sti.front() = 10000000;
	sti1.front() = 11111111;
	sti.resize(5);
	sti1.resize(5);
	sti.swap(sti1);
	print_list(myi, myi1);
	
	std::cout << "___________" << std::endl;
	print_list(sti, myi);
	print_list(sti1, myi1);
	std::cout << "___________" << std::endl;
	std::cout << "SPLICE" << std::endl;
	sti.splice(++sti.begin(), sti1);
	myi.splice(++myi.begin(), myi1);
	
	
	myi.push_back(88888);
	sti.push_back(88888);
	print_list(sti, myi);
	
	std::cout << std::endl << "REMOVE" << std::endl;
	sti.remove(2);
	myi.remove(2);
	print_list(sti, myi);
	
	std::cout << std::endl << "Sort" << std::endl;
	sti.sort();
	myi.sort();
	print_list(sti, myi);
	
	std::cout << std::endl << "sort reverse" << std::endl;
	sti.sort(revsort);
	myi.sort(revsort);
	print_list(sti, myi);
	
	std::cout << std::endl << "Unique" << std::endl;
	sti.unique();
	myi.unique();
	print_list(sti, myi);
	
	double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                       12.77, 73.35, 72.25, 15.3,  72.25 };
  	std::list<double> stdou(mydoubles,mydoubles+10);
	ft::list<double> mydou(mydoubles,mydoubles+10);
	
	
	std::cout << std::endl << "UNIQUE(with param)" << std::endl;
	print_list(stdou, mydou);
	stdou.sort();
	mydou.sort();
	stdou.unique(is_near);
	mydou.unique(is_near);
	print_list(stdou, mydou);
	
	std::cout << std::endl << "Merge" << std::endl;
	sti1 = sti;
	myi1 = myi;
	int odds[] = {1, 3, 5, 7};
	int even[] = {2, 4, 6, 8};
	sti1.assign(odds, odds + 4);
	myi1.assign(odds, odds + 4);
	sti.assign(even, even + 4);
	myi.assign(even, even + 4);
	sti1.sort(revsort);
	myi1.sort(revsort);
	myi.sort(revsort);
	sti.sort(revsort);
	std::cout << "sti, myi" << std::endl;
	print_list(sti, myi);
	std::cout << "sti1, myi1" << std::endl;
	print_list(sti1, myi1);
	sti1.merge(sti, revsort);
	myi1.merge(myi, revsort);
	std::cout << "merged sti1, myi1" << std::endl;
	print_list(sti1, myi1);
	std::cout << sti.size() << "  " <<  sti.empty() << std::endl;
	std::cout << myi.size() << "  " <<  myi.empty() << std::endl;
	ft::list<int> newone;
	myi = newone;
	std::cout << "size after operator = " << myi.size() << std::endl;
	std::list<int> newtwo;
	if (&(newtwo.back()) == &(newtwo.front()) && \
			&(newone.back()) == &(newone.front()))
		std::cout << "ok\n";
		
	std::cout << std::endl << "relational operators " << std::endl;
	if (myi1 != myi)
		std::cout << "myi1 != myi" << std::endl;
	std::cout << "myi = myi1" << std::endl;
	myi = myi1;
	if (myi1 == myi)
		std::cout << "myi1 == myi" << std::endl;
	myi.pop_back();
	if (myi < myi1)
		std::cout << "myi < myi1" << std::endl;
	myi1.pop_front();
	myi1.pop_front();
	if (myi > myi1)
		std::cout << "myi > myi1" << std::endl;
		
		
	std::cout << "---------" << std::endl;
	ft::list<int>::iterator it = myi.begin();
	while (it != myi.end())
		std::cout << *it++ << " ";
	std::cout << "myi " << myi.size() << std::endl;
	it = myi1.begin();
	while (it != myi1.end())
		std::cout << *it++ << " ";
	std::cout << "myi1 " << myi1.size() << std::endl << "SWAP" << std::endl;
	swap(myi, myi1);
	it = myi.begin();
	while (it != myi.end())
		std::cout << *it++ << " ";
	std::cout << "myi " << myi.size()  << std::endl;
	it = myi1.begin();
	while (it != myi1.end())
		std::cout << *it++ << " ";
	std::cout << "myi1 " << myi1.size()  << std::endl;
}
 
