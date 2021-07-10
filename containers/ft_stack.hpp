#ifndef FT_STACK_H
#define FT_STACK_H

#include "ft_list.hpp"
#include "ft_vector.hpp"
#include "ft_deque.hpp"

namespace ft{
template <class T, class Container = ft::deque<T> >

class stack{
	typedef T value_type;
	typedef Container container_type;
	Container _cntr;
	
	template <class D, class Cont>
	friend bool operator== (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator!= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator<  (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator<= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator>  (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator>= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs);
	public:
		explicit stack (const Container& ctnr = Container()){
			_cntr = ctnr;}

		bool empty() const{
			return (_cntr.empty());}
			
		size_t size() const{
			return (_cntr.size());}	
		
		value_type& top(){
			return (_cntr.back());}

		const value_type& top() const{
			return (_cntr.back());}
			
		void push (const value_type& val){
			_cntr.push_back(val);}
			
		void pop(){
			_cntr.pop_back();}
			
};
	
template <class D, class Cont>
bool operator== (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr == rhs._cntr);};

template <class D, class Cont>
bool operator!= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr != rhs._cntr);};

template <class D, class Cont>
bool operator<  (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr < rhs._cntr);};

template <class D, class Cont>
bool operator<= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr <= rhs._cntr);};

template <class D, class Cont>
bool operator>  (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr > rhs._cntr);};

template <class D, class Cont>
bool operator>= (const stack<D,Cont>& lhs, const stack<D,Cont>& rhs){
	return (lhs._cntr >= rhs._cntr);};
}
#endif 
