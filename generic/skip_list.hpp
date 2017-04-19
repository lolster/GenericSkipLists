#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__

#include <functional>
#include <memory>
#include <limits>
// #include <iostream>

/*
	See: http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/FIGS/skip-list22.gif
*/

template <
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>
> class skip_list {
private:
	const size_type h_; // max height of the skip list - doesn't change for now
	size_type n_; // counter for number of nodes in the list
	Compare comp = Compare();
	Allocator alloc = Allocator();
	struct node_ {
		T data_;
		node_ *next_;
		node_ *prev_;
		node_ *top_;
		node_ *bottom_;
		explicit node_(T data = 0, node_ *next = nullptr, node_ *prev = nullptr, 
			node_ *top = nullptr, node_ *bottom = nullptr)
		: data_(data), next_(next), prev_(prev), top_(top), bottom_(bottom)
		{}
		~node_() {
			delete next;
			delete prev;
			delete top;
			delete bottom;
		}
	};
	node_ *head;
	node_ *tail; //exclusive
public:
	//Member types
	using value_type       =  T;
	using allocator_type   =  Allocator;
	using size_type        =  std::size_t;
	using reference        =  value_type&;
	using const_reference  =  const value_type&;
	using pointer          =  std::allocator_traits<allocator_type>::pointer;
	using const_pointer    =  std::allocator_traits<allocator_type>::const_pointer;
	//TODO
	// using difference_type = 
	// using iterator = 
	// using const_iterator = 
	// using reverse_iterator = 
	// using const_reverse_iterator = 


	skip_list(size_type h = 1)
	: h_(h), n_(0)
	{
		//TODO
		tail = new node_();
		head = tail;
	}
	~skip_list() {
		//TODO
		while(head != tail) {
			delete head++;
		}
		delete head;
	}

	//member functions
	//capacity
	bool empty() {
		return n_ == 0;
	}

	size_type size() {
		return n_;
	}

	size_type max_size() {
		return std::numeric_limits<size_type>::max();
	}

	//iterator:
	//TODO
	class Iterator {
	public:
	}
};

#endif