#ifndef FT_MAP_H
#define FT_MAP_H

#include <stdexcept>
#include <limits>

namespace ft{

template < class Key, class T, class Compare = std::less<Key> >
class map
{
	typedef std::pair<Key, T> pair_st;
	struct map_unit
	{
		struct map_unit* next;
		struct map_unit* prev;
		std::pair <Key, T> data;
		map_unit() : next(NULL), prev(NULL){}
		map_unit(const pair_st& data) : next(NULL), prev(NULL), data(data){}
		map_unit(const Key& key, const T& value) : 
			next(NULL), prev(NULL){
				data.first = key; data.second = value;}
		map_unit& operator=(map_unit& for_copy){
			data = for_copy.data;
			return (*this);}
		~map_unit(){};
	};

	Compare _comp;
	map_unit* _back;
	map_unit* _front;
	unsigned int _count;
	
	map_unit *new_ex(const pair_st& val = pair_st()){
		map_unit *tmp = new map_unit(val);
		if (tmp == NULL)
			throw std::bad_alloc();
		return (tmp);}

	void _bound(map_unit* left, map_unit* rigth){
		if (left != NULL)
			left->next = rigth;
		if (rigth != NULL)
			rigth->prev = left;}

	map_unit *_finding(map_unit *pos, const Key& val) const
	{
		if (pos == _back && _back->prev != NULL)
			pos = _back->prev;
		while (!(_comp(pos->data.first, val)) && pos->prev != NULL)
			pos = pos->prev;
		while (_comp(pos->data.first, val) && pos->next != NULL)
			pos = pos->next;
		return (pos);
	}
	
	bool _deletion(map_unit *pos){
		if (pos == NULL || pos->next == NULL)
			return (false);
		_bound(pos->prev, pos->next);
		delete pos;
		--_count;
		return (true);}
			
  	public:
		class value_compare{
		friend class map;
			protected:
		  		Compare vc_comp;
				value_compare () : vc_comp() {}
			public:
				typedef bool result_type;
				typedef pair_st first_argument_type;
				typedef pair_st second_argument_type;
				bool operator() (const pair_st& x, const pair_st& y) const{
					return vc_comp(x.first, y.first);}};
			
	  	typedef Compare key_compare;
		class iterator {
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			protected:
				map_unit* _act;
			public:
				iterator() : _act(NULL){}
				
				iterator(const iterator& for_copy) : _act(for_copy._act){}
				
				iterator(map_unit* act) : _act(act){}
				
				iterator(const map_unit* act) : 
								_act(const_cast<map_unit *>(act)){}

				void operator= (const iterator& for_copy){
					_act = for_copy._act;}
				
				void operator= (map_unit* for_copy){
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
				
				std::pair <Key, T>* operator->(){
					return (&(_act->data));}
				
				std::pair <Key, T>& operator*(){
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
				
				const_iterator(map_unit* act) : iterator(act){}
				
				const_iterator(iterator& for_copy) : iterator(for_copy){}
				
				const std::pair <Key, T>* operator->(){
					return (&iterator::_act->data);}
				
				const std::pair <Key, T>& operator*(){
					return (iterator::_act->data);}
					
				virtual ~const_iterator(){};};
		
	  	class reverse_iterator : virtual public iterator {
			public:
				reverse_iterator() : iterator() {}
				
				reverse_iterator(map_unit* act) : iterator(act){}
				
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
				
				const_reverse_iterator(map_unit* act) : reverse_iterator(act){}
				
				const_reverse_iterator(iterator& for_copy) : \
											reverse_iterator(for_copy){}
				
				const std::pair <Key, T>* operator->(){
						return (&reverse_iterator::iterator::_act->data);}
					
				const std::pair <Key, T>& operator*(){
						return (reverse_iterator::iterator::_act->data);}};
	
	private:
		
		class _open_iterator : virtual public iterator{
			public:
				_open_iterator(const iterator& it) : iterator(it){}
				virtual ~_open_iterator(){}
				map_unit *get_map_unit(){
					return (iterator::_act);}};
					
		map_unit* _get_map_unit_from_iter(const iterator& it){
			_open_iterator tmp(it);
			return (tmp.get_map_unit());}
			
		std::pair<map_unit*, bool> 
				_insertion(map_unit *pos, const pair_st& val){
			pos = _finding(pos, val.first);
			std::pair<map_unit*, bool> ret;
			if (pos != _back && pos->data.first == val.first){
				ret.first = pos;
				ret.second = false;
				return (ret);}
			map_unit *tmp = new_ex(val);
			if (val.first < pos->data.first || pos == _back){
				_bound(pos->prev, tmp);
				_bound(tmp, pos);}
			else if (pos->data.first < val.first){
				_bound(tmp, pos->next);
				_bound(pos, tmp);}
			++_count;
			if (_front != NULL && _front->prev == NULL);
			else
				_front = tmp;
			ret.first = tmp;
			ret.second = true;
			return (ret);}
	
	public:
	
		explicit map (const key_compare& comp = key_compare()){
			_back = new_ex(pair_st());
			_front = NULL;
			_count = 0;
			_comp = comp;}

		~map(){
			clear();
			delete _back;}

		template <class InputIterator>	
  		map (InputIterator first, InputIterator last,
     		const key_compare& comp = key_compare()){
			_back = new_ex(pair_st());
			_front = NULL;
			_count = 0;
			_comp = comp;
			while (first != last){
				_insertion(_back, *first);
				first++;}}
		
		map (const map& for_copy){
			_back = new_ex();
			_front = NULL;
			_count = 0;
			*this = for_copy;
			}
			
		map& operator=(const map& for_copy){
			clear();
			map_unit* runner = for_copy._front;
			if (runner == NULL)
				return (*this);
			while (runner != for_copy._back){
				_insertion(_back, runner->data);
				runner = runner->next;}
			return (*this);}

		unsigned long max_size(void) const{
			return (std::numeric_limits<std::ptrdiff_t>::max() / 
										(sizeof(map_unit)));}

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

		std::pair<iterator,bool> insert(const Key& key, const T& val){
			std::pair<Key, T> tmp(key, val);
			return (insert(tmp));}
		
		std::pair<iterator,bool> insert (const pair_st& val){
			std::pair<iterator,bool> ret;
			std::pair<map_unit*, bool> tmp;
			tmp = _insertion(_back, val);
			ret.first = tmp.first;
			ret.second = tmp.second;
			return (ret);}
		
		iterator insert (iterator position, const pair_st& val){
			position++;
			return (insert(val).first);}

		template <class InputIterator>
    	void insert (InputIterator first, InputIterator last){
			while (first != last)
				_insertion(_back, *first++);}
				
		void erase (iterator position){
			map_unit *tmp = _get_map_unit_from_iter(position);
			++position;
			_deletion(tmp);}

		void erase (iterator first, iterator last){
			map_unit *tmp;
			while (!(void *)0){
				tmp = _get_map_unit_from_iter(first++);
				if ((_deletion(tmp) == false) || (first == last))
					break;}
			last = tmp;}
			
		size_t erase (const Key& k){
			map_unit * tmp = _finding(_back, k);
			if (tmp->data.first != k)
				return (0);
			_deletion(tmp);
			return (1);	};
					
		void swap(map& for_copy){
			map_unit *tmp;
			tmp = for_copy._front;
			for_copy._front = _front;
			_front = tmp;
			tmp = for_copy._back;
			for_copy._back = _back;
			_back = tmp;
			for_copy._count += _count;
			_count = for_copy._count - _count;
			for_copy._count -= _count;}

		key_compare key_comp() const{
			return (Compare());}

		value_compare value_comp() const{
			return (value_compare());}
		
		T& operator[] (const Key& key){
			map_unit *tmp = _finding(_back, key);
			if (tmp->data.first == key)
				return (tmp->data.second);
			pair_st temp;
			temp.first = key;
			return _insertion(_back, temp).first->data.second;}
		
		void clear(){
			if (_front == NULL)
				return ;
			map_unit* forward = _front;
			map_unit* backward;
			while (forward->next != NULL){
				backward = forward;
				forward = forward->next;
				delete backward;}
			_front = NULL;
			_back->prev = NULL;
			_count = 0;}
			
		size_t count (const Key& k) const{
			if (_finding(_back, k)->data.first == k)
				return (1);
			return(0);}
			
		iterator lower_bound (const Key& k){
			map_unit *tmp = _finding(_back, k);
			if (tmp == _back && _back->prev != NULL)
				return (_back->prev);
			return (tmp);
		};
		const_iterator lower_bound (const Key& k) const{
			map_unit *tmp = _finding(_back, k);
			if (tmp == _back && _back->prev != NULL)
				return (_back->prev);
			return (tmp);
		};
		
		iterator upper_bound (const Key& k){
			map_unit *tmp = _finding(_back, k);
			if (tmp == _back && _back->prev != NULL)
				return (_back->prev);
			else if (tmp->data.first == k && tmp->next != _back)
				tmp = tmp->next;
			return (tmp);}
			
		const_iterator upper_bound (const Key& k) const{
			map_unit *tmp = _finding(_back, k);
			if (tmp == _back && _back->prev != NULL)
				return (_back->prev);
			else if (tmp->data.first == k && tmp->next != _back)
				tmp = tmp->next;
			return (tmp);}
			
		std::pair<const_iterator,const_iterator>equal_range(const Key& k) const{
			std::pair<iterator,iterator> ret;
			ret.first = lower_bound(k);
			ret.second = upper_bound(k);
			return (ret);};
			
		std::pair<iterator,iterator>equal_range (const Key& k){
			std::pair<iterator,iterator> ret;
			ret.first = lower_bound(k);
			ret.second = upper_bound(k);
			return (ret);}
};

template <class Key, class T, class Compare>
  bool operator== ( const map<Key,T,Compare>& lhs,
                    const map<Key,T,Compare>& rhs ){
	if (lhs.size() != rhs.size())
		return false;
	typename map<Key,T,Compare>::iterator left_it = lhs.begin();
	typename map<Key,T,Compare>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (left_it->first != right_it->first)
			return false;
		if (left_it->second != right_it->second)
			return false;
		++left_it;
		++right_it;}
	return true;}

template <class Key, class T, class Compare>
bool operator!= ( const map<Key,T,Compare>& lhs,
                    const map<Key,T,Compare>& rhs ){
	if (lhs == rhs)
		return false;
	return true;}
	
template <class Key, class T, class Compare>
bool operator<  ( const map<Key,T,Compare>& lhs,
                  const map<Key,T,Compare>& rhs ){
	if (lhs.size() < rhs.size())
		return true;
	else if (lhs.size() > rhs.size())
		return false;
	typename map<Key,T,Compare>::iterator left_it = lhs.begin();
	typename map<Key,T,Compare>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (left_it->first < right_it->first)
			return true;
		if (left_it->second < right_it->second)
			return true;
		++left_it;
		++right_it;}
	return false;}
	
template <class Key, class T, class Compare>
bool operator> ( const map<Key,T,Compare>& lhs,
                 const map<Key,T,Compare>& rhs ){
	if (lhs.size() > rhs.size())
		return true;
	else if (lhs.size() > rhs.size())
		return false;
	typename map<Key,T,Compare>::iterator left_it = lhs.begin();
	typename map<Key,T,Compare>::iterator right_it = rhs.begin();
	while (left_it != lhs.end()){
		if (left_it->first > right_it->first)
			return true;
		if (left_it->second > right_it->second)
			return true;
		++left_it;
		++right_it;}
	return false;}
	
template <class Key, class T, class Compare>
bool operator<= ( const map<Key,T,Compare>& lhs,
                  const map<Key,T,Compare>& rhs ){
	if (lhs.size() > rhs.size())
		return false;
	return true;}
	
template <class Key, class T, class Compare>
bool operator>= ( const map<Key,T,Compare>& lhs,
                  const map<Key,T,Compare>& rhs ){
	if (lhs.size() < rhs.size())
		return false;
	return true;}
}

template <class Key, class T, class Compare>
  void swap (ft::map<Key,T,Compare>& x, ft::map<Key,T,Compare>& y){
	  x.swap(y);}
#endif
