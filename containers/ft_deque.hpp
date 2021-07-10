#ifndef FT_deque_H
#define FT_deque_H

#include <stdexcept>
#include <sstream>
#include <limits>
#include <algorithm>
namespace ft{

template < class T>
class deque
{
	struct deque_unit
	{
		struct deque_unit* next;
		struct deque_unit* prev;
		T data;
		deque_unit() : next(NULL), prev(NULL){}
		deque_unit(const T& data) : next(NULL), prev(NULL), data(data){}
		deque_unit& operator=(T& for_copy){
			data = for_copy; return (*this);}
		deque_unit(const deque_unit& for_copy) : next(NULL), prev(NULL){
			data = for_copy.data;}
		~deque_unit(){};};
		
	deque_unit *new_ex(const deque_unit& val = deque_unit()){
		deque_unit *tmp = new deque_unit(val);
		if (tmp == NULL)
			throw std::bad_alloc();
		return (tmp);}
	
	deque_unit* _back;
	deque_unit* _front;
	unsigned int _count;

	void _elem_move(deque_unit* move, deque_unit *stay){
		if (move->next == NULL || stay->next == NULL)
			return ;
		_bound(move->prev, move->next);
		_bound(stay->prev, move);
		_bound(move, stay);
		return ;}

	void _merging(deque& x){
		if (_back->prev == NULL){
				_front = x._front;
				_back->prev = x._back->prev;}
			else {
				_bound(_back->prev, x._front);
				_bound(x._back->prev, _back);
			}
			x._back->prev = NULL;
			x._front = NULL;
			x._count = 0;}

	void _bound(deque_unit* left, deque_unit* rigth){
		if (left != NULL)
			left->next = rigth;
		if (rigth != NULL)
			rigth->prev = left;}

	void _insertion(deque_unit *pos, const T& val){
		deque_unit *tmp = new_ex(val);
		if (tmp == NULL)
			throw std::exception();
		if (pos == NULL || pos->prev == NULL){
			if (_front == NULL)
				_bound(tmp, _back);
			else
				_bound(tmp, _front);
			_front = tmp;}
		else {
			_bound(pos->prev, tmp);
			_bound(tmp, pos);}
		++_count;}
		
	bool _deletion(deque_unit *pos){
		if (pos == NULL || pos->next == NULL)
			return (false);
		_bound(pos->prev, pos->next);
		delete pos;
		--_count;
		return (true);}
		
  	public:
		class iterator {
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			protected:
				deque_unit* _act;
			public:
				iterator() : _act(NULL){}
				
				iterator(const iterator& for_copy) : _act(for_copy._act){}
				
				iterator(deque_unit* act) : _act(act){}
				
				iterator(const deque_unit* act) : 
								_act(const_cast<deque_unit *>(act)){}

				void operator= (const iterator& for_copy){
					_act = for_copy._act;}
				
				void operator= (deque_unit* for_copy){
					_act = for_copy;}
				
				iterator& operator++(void){
					if (_act->next == NULL)
						return (*this);
					_act = _act->next;
					return (*this);}
				
				iterator operator++(int){
					iterator for_out(*this);
					++(*this);
					return (for_out);}
					
				iterator operator+(int n){
					iterator for_out(*this);
					if (n > 0){
						while (n-- > 0)
							++for_out;}
					else{
						while (n++ < 0)
							--for_out;}
					return (for_out);}
					
				iterator operator-(int n){
					iterator for_out(*this);
					if (n < 0){
						while (n-- < 0)
							++for_out;}
					else{
						while (n++ > 0)
							--for_out;}
					return (for_out);}
					
				iterator operator+=(int n){
					if (n > 0){
						while (n-- > 0)
							++(*this);}
					else{
						while (n++ < 0)
							--(*this);}
					return (*this);}
					
				iterator operator-=(int n){
					if (n < 0){
						while (n-- < 0)
							++(*this);}
					else{
						while (n++ > 0)
							--(*this);}
					return (*this);}
				
				iterator& operator--(void){
					if (_act->prev == NULL)
						return (*this);
					_act = _act->prev;
					return (*this);}
				
				iterator operator--(int){
					iterator for_out;
					for_out = *this;
					--(*this);
					return (for_out);}
				
				T* operator->(){
					return (&(_act->data));}
				
				T& operator*(){
					return (_act->data);}
				
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
				
				const_iterator(deque_unit* act) : iterator(act){}
				
				const_iterator(iterator& for_copy) : iterator(for_copy){}
				
				const T* operator->(){
					return (&iterator::_act->data);}
				
				const T& operator*(){
					return (iterator::_act->data);}
					
				virtual ~const_iterator(){};};
		
	  	class reverse_iterator : virtual public iterator {
			public:
				reverse_iterator() : iterator() {}
				
				reverse_iterator(deque_unit* act) : iterator(act){}
				
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
				
				const_reverse_iterator(deque_unit* act) : reverse_iterator(act){}
				
				const_reverse_iterator(iterator& for_copy) : reverse_iterator(for_copy){}
				
				const T* operator->(){
						return (&reverse_iterator::iterator::_act->data);}
					
				const T& operator*(){
						return (reverse_iterator::iterator::_act->data);}};
	
	private:
		
		class _open_iterator : virtual public iterator{
			public:
				_open_iterator(const iterator& it) : iterator(it){}
				virtual ~_open_iterator(){}
				deque_unit *get_deque_unit(){
					return (iterator::_act);}};
					
		deque_unit* _get_deque_unit_from_iter(const iterator& it){
			_open_iterator tmp(it);
			return (tmp.get_deque_unit());}
	
	public:
	
		deque (){
			_back =  new_ex();
			_front = NULL;
			_count = 0;}
		
		explicit deque (size_t n, const T& val = T()){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			for (unsigned int cnt = 0; cnt < n; cnt++)//{
				push_back(val);}
				
		deque (int n, const int& val){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			for (unsigned int cnt = 0; cnt < n; cnt++)//{
				push_back(val);}
	
		~deque(){
			clear();
			delete _back;}

		template <class InputIterator>
  		deque (InputIterator first, InputIterator last){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			assign(first, last);}
		
		deque (const deque& for_copy){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			deque_unit* runner = for_copy._front;
			while (runner != for_copy._back){
				push_back(runner->data);
				runner = runner->next;}}
			
		deque& operator=(const deque& for_copy){
			clear();
			deque_unit* runner = for_copy._front;
			if (runner == NULL)
				return (*this);
			while (runner != for_copy._back){
				push_back(runner->data);
				runner = runner->next;}
			return (*this);}

		unsigned long max_size(void) const{
			return (std::numeric_limits<std::ptrdiff_t>::max() / 
										(sizeof(deque_unit)));}

		bool empty() const{
			if (_front == NULL)
				return true;
			return false;}
			
		unsigned long size() const{
			return (_count);}
	
		iterator begin(){
			iterator tmp;
			if (_front == NULL)
				tmp = _back;
			else 
				tmp = _front;
			return (tmp);}
			
		const_iterator begin() const{
			const_iterator tmp;
			if (_front == NULL)
				tmp = _back;
			else 
				tmp = _front;
			return (tmp);}

		iterator end(){
			iterator tmp(_back);
			return (tmp);}
			
		const_iterator end() const{
			const_iterator tmp(_back);
			return (tmp);}

		reverse_iterator rbegin(){
			reverse_iterator tmp(_back);
			return (tmp);};
		
		const_reverse_iterator rbegin() const{
			const_reverse_iterator tmp(_back);
			return (tmp);};
			
		reverse_iterator rend(){
			reverse_iterator tmp;
			if (_front == NULL)
				tmp = _back;
			else 
				tmp = _front;
			return (tmp);}
			
		const_reverse_iterator rend() const{
			const_reverse_iterator tmp;
			if (_front == NULL)
				tmp = _back;
			else 
				tmp = _front;
			return (tmp);}

		T& front(){
			if (_front == NULL)
				return (_back->data);
			return (_front->data);}

		const T& front() const{
			if (_front == NULL)
				return (_back->data);
			return (_front->data);}
			
		T& back(){
			if (_back->prev == NULL)
				return (_back->data);
			return (_back->prev->data);}

		const T& back() const{
			if (_back->prev == NULL)
				return (_back->data);
			return (_back->prev->data);}
			
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last){
			clear();
			while (first != last)
				push_back(*first++);}
				
		void assign (unsigned int n, const T& val){
			clear();
			while (n-- > 0)
					push_back(val);}

		void push_back (const T& val){
			deque_unit *tmp = new_ex(val);
			++_count;
			if (_front == NULL){
				_front = tmp;
				_bound(_front, _back);
				return;}
			_bound(_back->prev, tmp);
			_bound(tmp, _back);}
				
		void push_front (const T& val){
			deque_unit *tmp = new_ex(val);
			if (_front == NULL)
				_bound(tmp, _back);
			else
				_bound(tmp, _front);
			_front = tmp;
			++_count;}
			
		void pop_back(){
			deque_unit *tmp = _back->prev;
			if (tmp == NULL || _count == 0)
				return;
			if (tmp == _front)
				_front = NULL;
			_bound(tmp->prev, _back);
			delete tmp;
			--_count;}
			
		void pop_front(){
			deque_unit *tmp = _front;
			if (_front == NULL  || _count == 0)
				return;
			if (_front->next == _back){
				_front = NULL;
				_back->prev = NULL;}
			else{
				_front = _front->next;
				_front->prev = NULL;}
			delete tmp;
			--_count;}
			
		iterator insert (iterator position, const T& val){
			deque_unit *tmp = _get_deque_unit_from_iter(position);
			_insertion(tmp, val);
			return (--position);}
			
		void insert (iterator position, unsigned long n, const T& val){
			deque_unit *tmp = _get_deque_unit_from_iter(position);
			if (tmp == NULL)
				return ;
			while (n-- > 0)
				_insertion(tmp, val);}
		
		template <class InputIterator>
    	void insert (iterator position, 
								InputIterator first, InputIterator last){
			deque_unit *tmp = _get_deque_unit_from_iter(position);
			if (tmp == NULL)
				return ;
			while (first != last)
				_insertion(tmp, *first++);}
				
		iterator erase (iterator position){
			deque_unit *tmp = _get_deque_unit_from_iter(position);
			++position;
			_deletion(tmp);
			return (position);}

		iterator erase (iterator first, iterator last){
			deque_unit *tmp;
			while (!(void *)0){
				tmp = _get_deque_unit_from_iter(first++);
				if ((_deletion(tmp) == false) || (first == last))
					break;}
			last = tmp;
			return (last);};
			
		void swap(deque& for_copy){
			deque_unit *tmp;
			tmp = for_copy._front;
			for_copy._front = _front;
			_front = tmp;
			tmp = for_copy._back;
			for_copy._back = _back;
			_back = tmp;
			for_copy._count += _count;
			_count = for_copy._count - _count;
			for_copy._count -= _count;};
		
		T& operator[] (size_t n){
			deque_unit *runner = _front;
			while (n > 0){
				runner = runner->next;
				--n;}
			return (runner->data);};

		const T& operator[] (size_t n) const{
			deque_unit *runner = _front;
			while (n > 0){
				runner = runner->next;
				--n;}
			return (runner->data);}
			
		T& at (size_t n){
			if (n >= _count){
				std::stringstream out;
				out << "deque::range_check: _n (which is " << n \
					<< ")>= this->size() (which is " << _count << ")";
				throw (std::out_of_range(out.str()));}
			deque_unit *runner = _front;
			while (n < 0){
				runner = runner->next;
				--n;}
			return (runner->data);}
			
		const T& at (size_t n) const{
			if (n >= _count){
				std::stringstream out;
				out << "deque::range_check: _n (which is " << n \
					<< ")>= this->size() (which is " << _count << ")";
				throw (std::out_of_range(out.str()));}
			deque_unit *runner = _front;
			while (n < 0){
				runner = runner->next;
				--n;}
			return (runner->data);}

		void resize (long n, T val = T()){
			if (n == 0)
				clear();
			deque_unit *runner;
			if (_front == NULL){
				assign(n, val);
				return ;}
			runner = _front;
			while (!(void *)0){
				runner = runner->next;
				if (--n < 1 || runner == _back)
					break ;}
			if (n < 1)
				erase(runner, end());
			else if (runner == _back){
				insert(runner, n, val);}}
				
		void clear(){
			if (_front == NULL)
				return ;
			deque_unit* forward = _front;
			deque_unit* backward;
			while (forward->next != NULL){
				backward = forward;
				forward = forward->next;
				delete backward;}
			_front = NULL;
			_back->prev = NULL;
			_count = 0;
			}
};
template <class T>
bool operator== (const deque<T>& lhs, const deque<T>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	typename deque<T>::iterator left_it = lhs.begin();
	typename deque<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end())
		if (*left_it++ != *right_it++)
			return false;
	return true;}
	
template <class T>
bool operator!= (const deque<T>& lhs, const deque<T>& rhs){
	if (lhs == rhs)
		return false;
	return true;}
	
template <class T>
bool operator< (const deque<T>& lhs, const deque<T>& rhs){
	typename deque<T>::iterator left_it = lhs.begin();
	typename deque<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it < *right_it)
		return true;
	return false;}
	
template <class T>
bool operator> (const deque<T>& lhs, const deque<T>& rhs){typename deque<T>::iterator left_it = lhs.begin();
	typename deque<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it > *right_it)
		return true;
	return false;}
	
template <class T>
bool operator<= (const deque<T>& lhs, const deque<T>& rhs){
	if (lhs.size() > rhs.size())
		return false;
	return true;}
	
template <class T>
bool operator>= (const deque<T>& lhs, const deque<T>& rhs){
	if (lhs.size() < rhs.size())
		return false;
	return true;}
}
template <class T>
void swap (ft::deque<T>& x, ft::deque<T>& y){
	x.swap(y);};

#endif