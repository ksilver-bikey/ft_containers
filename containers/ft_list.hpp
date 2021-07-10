#ifndef FT_LIST_H
#define FT_LIST_H

#include <limits>
#include <stdexcept>

namespace ft{
template < class T>
class list
{
	struct list_unit
	{
		struct list_unit* next;
		struct list_unit* prev;
		T data;
		list_unit() : next(NULL), prev(NULL){}
		list_unit(const T& data) : next(NULL), prev(NULL), data(data){}
		list_unit& operator=(T& for_copy){
			data = for_copy; return (*this);}
		list_unit(const list_unit& for_copy) : next(NULL), prev(NULL){
			data = for_copy.data;}
		~list_unit(){};};
	
	struct _less{
		bool operator()(const T& a, const T& b) const{
		if (a < b)
			return true;
		return false;}};
	
	list_unit *new_ex(const list_unit& val = list_unit()){
		list_unit *tmp = new list_unit(val);
		if (tmp == NULL)
			throw std::bad_alloc();
		return (tmp);}
	
	list_unit* _back;
	list_unit* _front;
	unsigned int _count;
	
	template <class Compare>
	bool _be_sorted(Compare comp){
		if (_back->prev == NULL || _back->prev->prev == NULL)
			return true;
		list_unit *runner = _back->prev->prev;
		while (runner != NULL){
			if (comp(runner->next->data, runner->data))
				return false;
			runner = runner->prev;}
		return (true);}

	void _elem_move(list_unit* move, list_unit *stay){
		if (move->next == NULL || stay->next == NULL)
			return ;
		_bound(move->prev, move->next);
		_bound(stay->prev, move);
		_bound(move, stay);
		return ;}

	void _merging(list& x, char dir = 'b'){
		if (_back->prev == NULL){
			_front = x._front;
			_back->prev = x._back->prev;}
		else if (dir == 'b'){
			_bound(_back->prev, x._front);
			_bound(x._back->prev, _back);}
		else {
			_bound(x._back->prev, _front);
			_front = x._front;}
		_count += x._count;
		x._back->prev = NULL;
		x._front = NULL;
		x._count = 0;}
		
	void _bound(list_unit* left, list_unit* rigth){
		if (left != NULL)
			left->next = rigth;
		if (rigth != NULL)
			rigth->prev = left;}

	void _insertion(list_unit *pos, const T& val){
		list_unit *tmp = new_ex(val);
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
		
	bool _deletion(list_unit *pos){
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
				list_unit* _act;
			public:
				iterator() : _act(NULL){}
				
				iterator(const iterator& for_copy) : _act(for_copy._act){}
				
				iterator(list_unit* act) : _act(act){}
				
				iterator(const list_unit* act) : 
								_act(const_cast<list_unit *>(act)){}

				void operator= (const iterator& for_copy){
					_act = for_copy._act;}
				
				void operator= (list_unit* for_copy){
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
				
				const_iterator(list_unit* act) : iterator(act){}
				
				const_iterator(iterator& for_copy) : iterator(for_copy){}
				
				const T* operator->(){
					return (&iterator::_act->data);}
				
				const T& operator*(){
					return (iterator::_act->data);}
					
				virtual ~const_iterator(){};};
		
	  	class reverse_iterator : virtual public iterator {
			public:
				reverse_iterator() : iterator() {}
				
				reverse_iterator(list_unit* act) : iterator(act){}
				
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
				
				const_reverse_iterator(list_unit* act) : reverse_iterator(act){}
				
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
				list_unit *get_list_unit(){
					return (iterator::_act);}};
					
		list_unit* _get_list_unit_from_iter(const iterator& it){
			_open_iterator tmp(it);
			return (tmp.get_list_unit());}
	
	public:
	
		list (){
			_back =  new_ex();
			_front = NULL;
			_count = 0;}
		
		explicit list (size_t n, const T& val = T()){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			for (unsigned int cnt = 0; cnt < n; cnt++)//{
				push_back(val);}
				
		list (int n, const int& val){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			for (unsigned int cnt = 0; cnt < n; cnt++)//{
				push_back(val);}
	
		~list(){
			clear();
			delete _back;
			}

		template <class InputIterator>
  		list (InputIterator first, InputIterator last){
			_back =  new_ex();
			_front = NULL;
			_count = 0;
			assign(first, last);}
		
		list (const list& for_copy){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			list_unit* runner = for_copy._front;
			while (runner != for_copy._back){
				push_back(runner->data);
				runner = runner->next;}
			}
			
		list& operator=(const list& for_copy){
			clear();
			list_unit* runner = for_copy._front;
			if (runner == NULL)
				return (*this);
			while (runner != for_copy._back){
				push_back(runner->data);
				runner = runner->next;}
			return (*this);}

		unsigned long max_size(void) const{
			return (std::numeric_limits<std::ptrdiff_t>::max() / 
										(sizeof(list_unit)));}

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
			list_unit *tmp = new_ex(val);
			++_count;
			if (_front == NULL){
				_front = tmp;
				_bound(_front, _back);
				return;}
			_bound(_back->prev, tmp);
			_bound(tmp, _back);}
				
		void push_front (const T& val){
			list_unit *tmp = new_ex(val);
			if (_front == NULL)
				_bound(tmp, _back);
			else
				_bound(tmp, _front);
			_front = tmp;
			++_count;}
			
		void pop_back(){
			list_unit *tmp = _back->prev;
			if (tmp == NULL || _count == 0)
				return;
			if (tmp == _front)
				_front = NULL;
			_bound(tmp->prev, _back);
			delete tmp;
			--_count;}
			
		void pop_front(){
			list_unit *tmp = _front;
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
			list_unit *tmp = _get_list_unit_from_iter(position);
			_insertion(tmp, val);
			return (--position);}
			
		void insert (iterator position, unsigned long n, const T& val){
			list_unit *tmp = _get_list_unit_from_iter(position);
			if (tmp == NULL)
				return ;
			while (n-- > 0)
				_insertion(tmp, val);}
		
		template <class InputIterator>
    	void insert (iterator position, 
								InputIterator first, InputIterator last){
			list_unit *tmp = _get_list_unit_from_iter(position);
			if (tmp == NULL)
				return ;
			while (first != last)
				_insertion(tmp, *first++);}
				
		iterator erase (iterator position){
			list_unit *tmp = _get_list_unit_from_iter(position);
			++position;
			_deletion(tmp);
			return (position);}

		iterator erase (iterator first, iterator last){
			list_unit *tmp;
			while (!(void *)0){
				tmp = _get_list_unit_from_iter(first++);
				if ((_deletion(tmp) == false) || (first == last))
					break;}
			last = tmp;
			return (last);};
			
		void swap(list& for_copy){
			list_unit *tmp;
			tmp = for_copy._front;
			for_copy._front = _front;
			_front = tmp;
			tmp = for_copy._back;
			for_copy._back = _back;
			_back = tmp;
			for_copy._count += _count;
			_count = for_copy._count - _count;
			for_copy._count -= _count;};
			
		void resize (long n, T val = T()){
			list_unit *runner;
			if ((_front == NULL) || (n-- == 0)){
				assign(n, val);
				return ;}
			runner = _front;
			while (!(void *)0){
				runner = runner->next;
				if (n-- < 1 || runner == _back)
					break ;}
			if (n < 1)
				erase(runner, end());
			else if (runner == _back){
				insert(runner, n, val);}}
				
		void clear(){
			if (_front == NULL)
				return ;
			list_unit* forward = _front;
			list_unit* backward;
			while (forward->next != NULL){
				backward = forward;
				forward = forward->next;
				delete backward;}
			_front = NULL;
			_back->prev = NULL;
			_count = 0;}
			
		void splice(iterator position, list& x, iterator first, iterator last){
			list_unit *tmp = _get_list_unit_from_iter(position);
			if ((x.empty() == true) || (tmp == NULL))
				return;
			while (first != last && first != x.end())
				_insertion(tmp, *first++);}
		
		void splice (iterator position, list& x, iterator i){
			splice(position, x, i, x.end());}
			
		void splice (iterator position, list& x){
			splice(position, x, x.begin(), x.end());}
			
		template <class Predicate>
  		void remove_if (Predicate pred){
			list_unit *forward = _back->prev;
			list_unit *backward;
			while (forward != NULL){
				backward = forward;
				forward = forward->prev;
				if (pred(backward->data) == true)
					_deletion(backward);}}
					
		void remove (const T& val){
			list_unit *forward = _back->prev;
			list_unit *backward;
			while (forward != NULL){
				backward = forward;
				forward = forward->prev;
				if (backward->data == val)
					_deletion(backward);}}
					
		void unique(){
			list_unit *runner = _back->prev;
			while (runner != NULL){
				if ((runner->next != _back) && 
							(runner->next->data == runner->data))
					_deletion(runner->next);
				runner = runner->prev;}}
					
		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred){
			list_unit *runner = _back->prev;
			while (runner != NULL){
				if ((runner->next != _back) && 
						binary_pred(runner->next->data,runner->data))
					_deletion(runner->next);
				runner = runner->prev;}}
	
		void sort(){
			sort(_less());}
		
		template <class Compare>
		void sort (Compare comp){
			if (_back->prev == NULL || _back->prev->prev == NULL)
				return;
			bool sorted = false;
			list_unit *left;
			while (sorted == false){
				sorted = true;
				left = _back->prev->prev;
				while (left != NULL){
					if (comp(left->next->data, left->data)){
						_elem_move(left->next, left);
						sorted = false;}
					left = left->prev;}}
			left = _back;
			while (left->prev != NULL)
				left = left->prev;
			_front = left;}
				
		void reverse(){
			list_unit *runner = _front->next;
			list_unit *tmp;
			_front->prev = _front->next;
			_front->next = _back;
			while (runner != _back){
				tmp = runner->next;
				runner->next = runner->prev;
				runner->prev = tmp;
				runner = runner->prev;}
			_back->prev->prev = NULL;
			tmp = _front;
			_front = _back->prev;
			_back->prev = tmp;}
			
		void merge (list& x){
			if (x.empty())
				return ;
			merge(x, _less());}
		/*	_merging(x);
			sort();}
		*/
		template <class Compare>
			void merge (list& x, Compare comp){
				if (x.empty())
					return ;
				if (!(_be_sorted(comp))){
					if (comp(x._front->data, _front->data))
						_merging(x, 'f');
					else
						_merging(x);} 
				else if (!(x._be_sorted(comp))){
					if (_back->prev){
						_bound(_back->prev->prev, x._front);
						_bound(x._back->prev, _back->prev);}
					else{
						_front = x._front;
						_bound(x._back->prev, _back);}}
				else{
					_merging(x);
					sort(comp);}
				x._front = NULL;
				x._back->prev = NULL;
				_count += x._count;
				x._count = 0;}

			
};
template <class T>
bool operator== (const list<T>& lhs, const list<T>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	typename list<T>::iterator left_it = lhs.begin();
	typename list<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end())
		if (*left_it++ != *right_it++)
			return false;
	return true;}
	
template <class T>
bool operator!= (const list<T>& lhs, const list<T>& rhs){
	if (lhs == rhs)
		return false;
	return true;}
	
template <class T>
bool operator< (const list<T>& lhs, const list<T>& rhs){
	if (lhs.size() < rhs.size())
		return true;
	else if (lhs.size() > rhs.size())
		return false;
	typename list<T>::iterator left_it = lhs.begin();
	typename list<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it < *right_it)
		return true;
	return false;}
	
template <class T>
bool operator> (const list<T>& lhs, const list<T>& rhs){
	if (lhs.size() > rhs.size())
		return true;
	else if (lhs.size() < rhs.size())
		return false;
	typename list<T>::iterator left_it = lhs.begin();
	typename list<T>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (*left_it != *right_it)
			break;
		left_it++;
		right_it++;}
	if (*left_it > *right_it)
		return true;
	return false;}
	
template <class T>
bool operator<= (const list<T>& lhs, const list<T>& rhs){
	if (lhs > rhs)
		return false;
	return true;}
	
template <class T>
bool operator>= (const list<T>& lhs, const list<T>& rhs){
	if (lhs < rhs)
		return false;
	return true;}
}
template <class T>
void swap (ft::list<T>& x, ft::list<T>& y){
	x.swap(y);};
#endif
