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

template<
		typename T,
		typename Compare = std::less<T>,
		typename Allocator = std::allocator<T>
		> 
class skip_list {
public:

	// Member types
	using allocator_type   =  Allocator;
	using value_type       =  typename std::allocator_traits<allocator_type>::value_type;
	using pointer          =  typename std::allocator_traits<allocator_type>::pointer;

	using size_type        =  std::size_t; // Its just unsigned int - size_t sizeof(x)

private:
	const size_type h; // max height of the skip list - doesn't change for now
	size_type n; // counter for number of nodes in the list

	Compare comp = Compare();
	Allocator alloc = Allocator();
	
	// Node definition
	struct node {

		//make this pointer to save data
		pointer data;
		// pointer to its adjacent nodes
		node *next;
		node *prev;
		node *top;
		node *bottom;

		//constructor
		explicit node( pointer data = nullptr,
					   node *next = nullptr, 
					   node *prev = nullptr, 
					   node *top = nullptr, 
					   node *bottom = nullptr )
		: data(data), next(next), prev(prev), top(top), bottom(bottom) {

		}

		~node() {
			// i am such an idiot
			// delete next_;
			// delete prev_;
			// delete top_;
			// delete bottom_;
			// std::cout << "Delete me\n";
			// No RA, therefore no RD
		}

		//utility functions
		bool is_head() {
			return this->next == nullptr;
		}

		bool is_tail() {
			return this->prev == nullptr;
		}
	};

	//pointers to head and tail
	node *head;
	node *tail; //exclusive

public:

	skip_list(size_type h = 1)
	: h(h), n(0) {

		// make a stack of head and tail nodes about ye (h) high
		
		head = new node(); //Dummy Head node
		tail = new node(); //Dummy Tail node
		//init head and tails (empty skiplist)
		head->next = tail;
		tail->prev = head;

		node *h_stack = head;
		node *t_stack = tail;

		for(size_type i = 1; i < h; ++i) {
			// TODO - make more efficient
			h_stack -> bottom = new node();
			h_stack -> bottom -> top = h_stack;
			
			t_stack -> bottom = new node();
			t_stack -> bottom -> top = t_stack;
			
			h_stack -> bottom -> next = t_stack -> bottom;
			t_stack -> bottom -> prev = h_stack -> bottom;
			
			h_stack = h_stack -> bottom;
			t_stack = t_stack -> bottom;
		}
	}

	~skip_list() {
		// Logic:
		// Iterate through each level and delete the nodes across the level
		for(size_type i = 0; i < h; ++i) {
			node *next_level = head -> bottom;
			while(head) {
				node *temp = head;
				head = head -> next;
				delete temp;
				//std::cout << "one\n";
			}
			head = next_level;
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
		return n == 0;
	}

	size_type size() {
		return n;
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
