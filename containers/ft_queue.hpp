#ifndef FT_QUEUE_H
#define FT_QUEUE_H

#include "ft_deque.hpp"

namespace ft{
template <class T, class Container = ft::deque<T> >

class queue{
	typedef T value_type;
	typedef Container container_type;
	Container _cntr;
	
	template <class D, class Cont>
	friend bool operator== (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator!= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator<  (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator<= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator>  (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);

	template <class D, class Cont>
	friend bool operator>= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs);
	public:
		explicit queue (const Container& ctnr = Container()){
			_cntr = ctnr;}

		bool empty() const{
			return (_cntr.empty());}
			
		size_t size() const{
			return (_cntr.size());}
			
		value_type& front(){
			return (_cntr.front());}
			
		const value_type& front() const{
			return (_cntr.front());}
		
		value_type& back(){
			return (_cntr.back());}

		const value_type& back() const{
			return (_cntr.back());}
			
		void push (const value_type& val){
			_cntr.push_back(val);}
			
		void pop(){
			_cntr.pop_front();}
			
};
	
template <class D, class Cont>
bool operator== (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr == rhs._cntr);};

template <class D, class Cont>
bool operator!= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr != rhs._cntr);};

template <class D, class Cont>
bool operator<  (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr < rhs._cntr);};

template <class D, class Cont>
bool operator<= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr <= rhs._cntr);};

template <class D, class Cont>
bool operator>  (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr > rhs._cntr);};

template <class D, class Cont>
bool operator>= (const queue<D,Cont>& lhs, const queue<D,Cont>& rhs){
	return (lhs._cntr >= rhs._cntr);};
}

#endif 
