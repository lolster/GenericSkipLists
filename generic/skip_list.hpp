#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__

#define DEBUG 1

#include <functional>
#include <memory>
#include <limits>

#if DEBUG
#include <iostream>
#endif

/*
	See: http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/FIGS/skip-list22.gif
*/

template <
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>
> class skip_list {
public:
	//Member types
	using allocator_type   =  Allocator;
	using value_type       =  typename std::allocator_traits<allocator_type>::value_type;
	using pointer          =  typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer    =  typename std::allocator_traits<allocator_type>::const_pointer;
	using reference        =  value_type&;
	using const_reference  =  const value_type&;
	using size_type        =  std::size_t;
	
	//TODO
	// using difference_type = 
	// using iterator = 
	// using const_iterator = 
	// using reverse_iterator = 
	// using const_reverse_iterator = 

private:
	const size_type h_; // max height of the skip list - doesn't change for now
	size_type n_; // counter for number of nodes in the list
	Compare comp = Compare();
	Allocator alloc = Allocator();
	struct node_ {
		using node_type_t = long;
		
		//class consts
		static const node_type_t HEAD_NODE = 1;
		static const node_type_t DATA_NODE = 2;
		static const node_type_t TAIL_NODE = 3;

		//make this pointer to save data
		pointer data_;
		const node_type_t type_;
		node_ *next_;
		node_ *prev_;
		node_ *top_;
		node_ *bottom_;
		explicit node_(pointer data = nullptr, node_type_t type = DATA_NODE, node_ *next = nullptr, node_ *prev = nullptr, 
			node_ *top = nullptr, node_ *bottom = nullptr)
		: data_(data), next_(next), prev_(prev), top_(top), bottom_(bottom), type_(type) {

		}

		~node_() {
			// i am such an idiot
			// delete next_;
			// delete prev_;
			// delete top_;
			// delete bottom_;
			// std::cout << "Delete me\n";
			// No RA, therefore no RD
		}
	};

	//pointers to head and tail
	node_ *head_;
	node_ *tail_; //exclusive

public:
	//TODO
	// 1. Iterators
	// 2. insert and all other list operations
	// 3. All ctors
	skip_list(size_type h = 1)
	: h_(h), n_(0) {
		// TODO
		// make a stack of head and tail nodes about ye (h_) high
		// please work
		head_ = new node_(nullptr, node_::HEAD_NODE);
		tail_ = new node_(nullptr, node_::TAIL_NODE);
		head_->next_ = tail_;
		tail_->prev_ = head_;
		node_ *h_t = head_;
		node_ *t_t = tail_;
		for(size_type i = 1; i < h_; ++i) {
			// TODO - make more efficient
			h_t->bottom_ = new node_(nullptr, node_::HEAD_NODE);
			h_t->bottom_->top_ = h_t;
			t_t -> bottom_ = new node_(nullptr, node_::TAIL_NODE);
			t_t->bottom_->top_ = t_t;
			h_t->bottom_->next_ = t_t->bottom_;
			t_t->bottom_->prev_ = h_t->bottom_;
			h_t = h_t->bottom_;
			t_t = t_t->bottom_;
		}
	}

	~skip_list() {
		// Logic:
		// Iterate through each level and delete the nodes across the level
		for(size_type i = 0; i < h_; ++i) {
			node_ *next_level = head_->bottom_;
			while(head_) {
				node_ *temp = head_;
				head_ = head_->next_;
				delete temp;
				std::cout << "one\n";
			}
			head_ = next_level;
		}
	}

	// member functions
	// TODO
	// operator=
	// assign

	allocator_type get_allocator() {
		return alloc;
	}

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
	};
};

#endif