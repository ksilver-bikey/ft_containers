#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <stdexcept>
#include <string>
#include <limits>
#include <sstream>

namespace ft{
template <class T>
class vector
{
	unsigned int _size;
	unsigned int _capacity;
	T* _data;
	
	void _copy(T* src, T* dst, int size){
		while (--size > -1)
			dst[size] = src[size];}
			
	void _copy_fw(T* src, T* dst, int size){
		int cnt = -1;
		--size;
		while (++cnt < size)
			dst[cnt] = src[cnt];}
	
	void _swap_int(unsigned int &one, unsigned int& two){
		one += two;
		two = one - two;
		one -= two;}
	
	T *new_ex(int n){
		T *tmp = new T[n];
		if (tmp == NULL)
			throw std::bad_alloc();
		return (tmp);}
	
	public:
		class iterator {
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			protected:
				T* _act;
			public:
				iterator() : _act(NULL) {}
				
				iterator(const iterator& for_copy) : _act(for_copy._act){}
				
				iterator(T* act) : 
							_act(act){}
				
				iterator(const T* act) :
								_act(const_cast<T *>(act)){}

				iterator(const T& act) : 
								_act(const_cast<T *>(&act)){}

				void operator= (const iterator& for_copy){
					_act = for_copy._act;}
				
				iterator& operator++(void){
					_act += 1;
					return (*this);}
				
				iterator operator++(int){
					iterator for_out(*this);
					++(*this);
					return (for_out);}
					
				iterator& operator+(int n){
					_act += n;
					return (*this);}
					
				iterator& operator-(int n){
					_act -= n;
					return (*this);}
				
				iterator& operator--(void){
					_act -= 1;
					return (*this);}
				
				iterator operator--(int){
					iterator for_out;
					for_out = *this;
					--(*this);
					return (for_out);}
				
				T* operator->(){
					return (_act);}
				
				T& operator*(){
					return (*_act);}
				
				bool operator==(const iterator& for_check){
					if (_act == for_check._act)
						return (true);
					return (false);}

				bool operator!=(const iterator& for_check){
					if (_act != for_check._act)
						return (true);
					return (false);}

				virtual ~iterator(){};
		};
		
		class const_iterator : virtual public iterator {
			public:
				const_iterator() : iterator(){}
				
				const_iterator(T* act) : iterator(act){}
				
				const_iterator(iterator& for_copy) : iterator(for_copy){}
				
				const T* operator->(){
					return (iterator::_act);}
				
				const T& operator*(){
					return (*(iterator::_act));}
					
				virtual ~const_iterator(){};};
		
	  	class reverse_iterator : virtual public iterator {
			public:
				reverse_iterator() : iterator() {}
				
				reverse_iterator(T* act) : iterator(act){}
				
				reverse_iterator(iterator& for_copy) : iterator(for_copy){}
				
				virtual ~reverse_iterator(){}
				
				reverse_iterator& operator++(void){
					iterator::operator--();
					return (*this);}
				
				reverse_iterator& operator++(int){
					iterator::operator--(1);
					return (*this);}
					
				reverse_iterator& operator--(void){
					iterator::operator++();
					return (*this);}
					
				reverse_iterator& operator--(int){
					iterator::operator++(1);
					return (*this);}};
	
		class const_reverse_iterator : virtual public reverse_iterator {
			public:
			
				const_reverse_iterator() : reverse_iterator() {}
				
				const_reverse_iterator(T* act) : reverse_iterator(act){}
				
				const_reverse_iterator(iterator& for_copy) : reverse_iterator(for_copy){}
				
				const T* operator->(){
						return (reverse_iterator::iterator::_act);}
					
				const T& operator*(){
						return (*(reverse_iterator::iterator::_act));}};

	vector (){
		_size = _capacity = 0;
		_data = new_ex(0);}
	
	explicit vector (size_t n, const T& val = T()){
		int cnt = n;
		_data = new_ex(n);
		_size = _capacity = cnt;
		while (--cnt > -1){
			_data[cnt] = val;}}
	
	vector (int n, const int& val){
		int cnt = n;
		_data = new_ex(n);
		_size = _capacity = cnt;
		while (--cnt > -1){
			_data[cnt] = val;}}

	template <class InputIterator>
    vector (InputIterator first, InputIterator last){
		int cnt = 1;
		InputIterator tmp = first;
		while (++first != last)
			++cnt;
		_size = _capacity = cnt;
		_data = new_ex(cnt);
		while (first != tmp){
			_data[--cnt] = *--first;}}

	vector& operator= (const vector& x){
		int cnt = _size = x._size;
		if (_capacity < _size){
			delete [] _data;
			_data = new_ex(_size);
			_capacity = _size;}
		while (--cnt > -1){
			_data[cnt] = x._data[cnt];}
		return (*this);}

	vector (const vector& x){
		_capacity = _size = 0;
		_data = NULL;
		*this = x;}
	
	virtual ~vector(void){
		delete [] _data;}
		
	iterator begin(){
		iterator tmp(_data);
		return (tmp);}
			
	const_iterator begin() const{
		const_iterator tmp(_data);
		return (tmp);}

	iterator end(){
		iterator tmp(&_data[_size - 1]);
		return (tmp);}
		
	const_iterator end() const{
		iterator tmp(&_data[_size - 1]);
		return (tmp);}

	reverse_iterator rbegin(){
		iterator tmp(&_data[_size - 1]);
		return (tmp);}
		
	const_reverse_iterator rbegin() const{
		iterator tmp(&_data[_size - 1]);
		return (tmp);}
			
	reverse_iterator rend(){
		const_iterator tmp(_data);
		return (tmp);}
			
	const_reverse_iterator rend() const{
		const_iterator tmp(_data);
		return (tmp);}

	T& operator[](int num){
		return (_data[num]);}
		
	unsigned long max_size(void) const{
			return (std::numeric_limits<std::ptrdiff_t>::max() / 
										(sizeof(T)));}
										
	unsigned long size(void) const{
		return (_size);}
	
	unsigned long capacity(void) const{
		return (_capacity);}
	
	void resize (size_t n, T val = T()){   ///проверить
		if (n > _size){
			T* tmp = new_ex(n + 1);
			for (int cnt = n; cnt > (int)_size - 1; --cnt)
				tmp[cnt] = val;
			_copy(_data, tmp, _size);
			delete [] _data;
			_data = tmp;
			_capacity = n;}
		_size = n;}
		
	void reserve (size_t n)
	{
		if (n > _capacity){
			T* tmp = new_ex(n + 1);
			for (int cnt = n; cnt > (int)_size - 1; --cnt)
				tmp[cnt] = T();
			_copy(_data, tmp, _size);
			delete [] _data;
			_data = tmp;
			_capacity = n;}
	}
	
	bool empty() const{
		if (_size == 0)
			return true;
		return false;
	}
	
	T& at (size_t n){
		if (n >= _size){
			std::stringstream out;
			out << "vector::range_check: __n (which is "\
						 << n << ") >= this->size() (which is " << _size << ")";
			throw (std::out_of_range(out.str()));}
		return (_data[n]);}

	const T& at (size_t n) const{
		if (n >= _size){
			std::stringstream out;
			out << "vector::range_check: __n (which is "\
						 << n << ") >= this->size() (which is " << _size << ")";
			throw (std::out_of_range(out.str()));}
		return (_data[n]);}
		
	T& front (void){
		return (_data[0]);}

	const T& front (void) const{
		return (_data[0]);}
		
	T& back (void){
		return (_data[_size == 0 ? 0 : _size - 1]);}

	const T& back (void) const{
		return (_data[_size == 0 ? 0 : _size - 1]);}
		
	void push_back (const T& val){
		if (_size < _capacity){
			_data[_size++] = val;
			return ;}
		T *tmp = new_ex(_capacity * 2);
		_copy(_data, tmp, _size);
		tmp[_size++] = val;
		_capacity *= 2;
		delete [] _data;
		_data = tmp;}
	
	void pop_back(){
		if (_size > 0)
			--_size;}
			
	iterator insert (iterator position, const T& val){
		if (position.operator->() < _data || 
							position.operator->() > &_data[_capacity]){
			throw std::exception();}
		if (_size < _capacity){
			_copy(position.operator->(), 
						position.operator->() + 1, 
							&_data[_size++] - position.operator->());
			*position = val;}
		else {
			int pos = position.operator->() - _data;
			T* tmp = new_ex(_capacity * 2);
			_copy(_data, tmp, pos);
			tmp[pos] = val;
			_copy(&_data[pos], &tmp[pos + 1], _size++ - pos);
			delete [] _data;
			_data = tmp;
			position = _data[pos];
			_capacity *= 2;}
		return (position);}
		
	 void insert (iterator position, size_t n, const T& val){
		if (position.operator->() < _data || 
							position.operator->() > &_data[_capacity]){
			throw std::exception();}
		int pos = position.operator->() - _data;
		if (_size + n < _capacity){
			_copy(position.operator->(), 
						position.operator->() + n, 
							&_data[_size] - position.operator->());
			_size += n;
			while ((int)--n > -1)
				_data[pos + n] = val;}
		else {
			_capacity *= 2;
			if (_capacity < n)
				_capacity = n;
			T* tmp = new_ex(_capacity);
			_copy(_data, tmp, pos);
			_copy(&_data[pos], &tmp[pos + n], _size - pos);
			_size += n;
			while ((int)--n > -1)
				tmp[pos + n] = val;
			delete [] _data;
			_data = tmp;}}
					
	template <class InputIterator>
   	void insert (iterator position, InputIterator first, InputIterator last){
		if (position.operator->() < _data || 
							position.operator->() > &_data[_capacity]){
			throw std::exception();}
		int pos = position.operator->() - _data;
		int n = 1;
		while (++first != last)
			++n;
		if (_size + n < _capacity){
			_copy(position.operator->(), 
						position.operator->() + n, 
							&_data[_size] - position.operator->());
			_size += n;		
			while ((int)--n > -1)
				_data[pos + n] = *--first;}
		else {
			_capacity *= 2;
			if ((int)_capacity < n)
				_capacity = n;
			T* tmp = new_ex(_capacity);
			_copy(_data, tmp, pos);
			_copy(&_data[pos], &tmp[pos + n], _size - pos);
			_size += n;
			while ((int)--n > -1)
				tmp[pos + n] = *--first;
			delete [] _data;
			_data = tmp;}}
			
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last){
		int n = 1;
		while (++first != last)
			++n;
		if (n > (int)_capacity){
			_capacity = n;
			T* tmp = new_ex(_capacity);
			delete [] _data;
			_data = tmp;}
		_size = n;
		while ((int)--n > -1)
				_data[n] = *--first;}
				
	void assign (size_t n, const T& val){
		_size = n;
		if (n > _capacity){
			T* tmp = new_ex(n);
			delete [] _data;
			_data = tmp;
			_capacity = _size;}
		while ((int)--n > -1)
				_data[n] = val;}
				
	iterator erase (iterator position){
		if (position.operator->() < _data || 
							position.operator->() > &_data[_capacity]){
			throw std::exception();}
		_copy_fw(position.operator->() + 1, 
						position.operator->(), 
							&_data[_size--] - position.operator->());
		return (position);}
	
	iterator erase (iterator first, iterator last){
		if (first.operator->() < _data || 
							first.operator->() > &_data[_capacity]){
			throw std::exception();}
		if (last.operator->() >= &_data[_size]){
			_size = (first.operator->() - _data);
			return _data[_size];}
		int len = last.operator->() - first.operator->();
		_copy_fw(last.operator->(), first.operator->(), len);
		_size -= len;
		return (first);}
		
	void swap (vector& x){
		_swap_int(x._size, _size);
		_swap_int(x._capacity, _capacity);
		T* tmp = x._data;
		x._data = _data;
		_data = tmp;}
		
	void clear(void){
		_size = 0;}
};
template <class T>
  	bool operator== (const vector<T>& lhs, const vector<T>& rhs)
	  {
		  if (lhs.size() != rhs.size())
		return false;
		typename vector<T>::iterator left_it = lhs.begin();
		typename vector<T>::iterator right_it = rhs.begin();
		while (left_it != lhs.end())
			if (*left_it++ != *right_it++)
				return false;
		if (*left_it != *right_it)
				return false;
		return true;}

template <class T>
bool operator!= (const vector<T>& lhs, const vector<T>& rhs){
	if (lhs == rhs)
		return false;
	return true;}
	
template <class T>
bool operator< (const vector<T>& lhs, const vector<T>& rhs){
	if (lhs.size() < rhs.size())
		return true;
	else if (lhs.size() > rhs.size())
		return false;
	typename vector<T>::iterator left_it = lhs.begin();
	typename vector<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it < *right_it)
		return true;
	return false;}
	
template <class T>
bool operator> (const vector<T>& lhs, const vector<T>& rhs){
	if (lhs.size() > rhs.size())
		return true;
	else if (lhs.size() < rhs.size())
		return false;
	typename vector<T>::iterator left_it = lhs.begin();
	typename vector<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it > *right_it)
		return true;
	return false;}
	
template <class T>
bool operator<= (const vector<T>& lhs, const vector<T>& rhs){
	if (lhs > rhs)
		return false;
	return true;}
	
template <class T>
bool operator>= (const vector<T>& lhs, const vector<T>& rhs){
	if (lhs < rhs)
		return false;
	return true;}

}
template <class T>
void swap (ft::vector<T>& x, ft::vector<T>& y){
	x.swap(y);};
#endif
