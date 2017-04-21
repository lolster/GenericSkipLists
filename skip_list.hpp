#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__

#define DEBUG 1

#include <functional>
#include <memory>
#include <limits>
#include <cstdlib>
#include <unistd.h> // for rand()

#if DEBUG
#include <iostream>
#include <vector>
#include <algorithm>
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
	using reference        =  value_type&;
	using const_pointer    =  typename std::allocator_traits<Allocator>::const_pointer;
	using const_reference  =  const value_type&;
	using size_type        =  std::size_t; // Its just unsigned int - size_t sizeof(x)

private:
	const size_type h; // max height of the skip list - doesn't change for now
	size_type n; // counter for number of nodes in the list

	allocator_type alloc = allocator_type();
	Compare comp;

	// Node definition
	struct node {

		//make this pointer to save data
		pointer data;
		// pointer to its adjacent nodes
		node *next;
		node *prev;
		node *top;
		node *bottom;
		
		//skip_list<T, Compare, Allocator>::comp;
		
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
			// Do not make mistake of deallocating data.
			// We will do it elsewhere
		}

		//utility functions
		bool is_head() const {
			return this->prev == nullptr && this->data == nullptr;
		}

		bool is_tail() const {
			return this->next == nullptr && this->data == nullptr;
		}

		static bool compare_me(	const skip_list<T, Compare, Allocator> *o, 
								const node& lhs, 
								const node& rhs) {
			if(lhs.is_head()) {
				std::cout << "Comparing with head\n" ;
				return true;
			}
			if(lhs.is_tail()) {
				std::cout << "Comparing with tail\n" ;
				return false;
			}	
			std::cout << lhs.data << "\t" << rhs.data << "\n";
			return o->comp(*(lhs.data),*(rhs.data));
		}
	};

	//pointers to head and tail
	node *head;
	node *tail; //exclusive
	
	bool should_propogate(){
		//auto temp = std::rand();
		//std::cout << "should prop rand val: " << temp << "\n";
		return std::rand() % 2 == 1;	
	}

public:

	skip_list(size_type h = 1)
	: h(h), n(0) {
		
		std::srand(getpid()); // Purely randomness
	
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
	
	
	void insert(const_reference data){
		node *mynode = new node(alloc.allocate(1));
		*(mynode -> data) = data;
		
		node *curr_ptr = head;
		
		// Finding pos to insert
		while( curr_ptr -> bottom != nullptr){
			std::cout << "Level Case\n";
			if( !( node::compare_me(this, *(curr_ptr -> next), *mynode) ) ){
				curr_ptr = curr_ptr -> bottom;
			}
			else{
				curr_ptr = curr_ptr -> next;
			}
		}	
		std::cout << "base case\n";
		while(node::compare_me(this, *(curr_ptr -> next), *mynode)){
				curr_ptr = curr_ptr -> next;
		}
		
		mynode -> next = curr_ptr -> next;
		mynode -> prev = curr_ptr;
		mynode -> next -> prev = mynode;
		curr_ptr -> next = mynode;
		
		// Adding node in upper level - if at all it is lucky
		while(should_propogate()/*true*/){
			// checking for node which has propogated
			while(curr_ptr != nullptr && curr_ptr -> top == nullptr){
				curr_ptr = curr_ptr -> prev;
			}
			// checking if it is in the top level
			if(curr_ptr == nullptr) {
				std::cout << "curr_ptr is nullptr\n"; 
				break;
			}
			// Inserting new node (mynode) in the current level
			curr_ptr = curr_ptr -> top;
			node *level_mynode = new node(mynode -> data);
			std::cout << "curr_ptr: " << curr_ptr << std::endl;
			level_mynode -> next = curr_ptr -> next;
			level_mynode -> prev = curr_ptr;
			level_mynode -> next -> prev = level_mynode;
			level_mynode -> bottom = mynode;
			curr_ptr -> next = level_mynode;
			mynode = level_mynode;
		}
		
		#if DEBUG
		node *temp = head;
		while(temp->bottom != nullptr) {
			temp = temp->bottom;
		}
		temp = temp->next;
		while(!temp->is_tail()){
			std::cout << *(temp->data) << "->";
			temp = temp->next;
		}
		std::cout << std::endl;
		#endif
	}
	
	
	#if DEBUG
	void pretty_print() {
		
		std::vector<std::vector<value_type>> idk;
		node *temp = head;
		
		
		while(temp -> bottom){
			temp = temp -> bottom;
		}
		while(temp){
			std::vector<value_type> level_vector;
			node *temp_temp = temp->next;
			while(temp_temp && !temp_temp->is_tail()){
				level_vector.push_back(*(temp_temp->data));
				temp_temp = temp_temp -> next;
			}
			//std::reverse(level_vector.begin(), level_vector.end());
			idk.push_back(level_vector);
			temp = temp -> top; 
		}
		
		std::for_each(idk.begin(), idk.end(), [](auto e){
			std::for_each(e.begin(), e.end(), [](auto v){
				std::cout << v << "->";
			});
			std::cout << "\n";
		});
		
		int j1 = 0;
		for(int i = idk.size() - 1; i > 0 ; --i){
			std::cout << "\nh\t";
			j1 = idk[i].size() - 1;
			for(int j = 0; j < idk[0].size(); ++j){
				// if level is empty
				if(idk[i].size() == 0){
					for(int j = 0; j < idk[0].size(); ++j){
						std::cout << "-" << "\t";	
					}
					break;
				}
				//std::cout << "if(" << idk[0][j] << "==" << idk[i][j1] << ")\n";
				if( idk[0][j] == idk[i][j1]){
					std::cout << idk[0][j] << "\t"; 
					j1--;
				}
				else{
					std::cout << "-" << "\t";
				}
				
			}
			std::cout << "t";
			j1 = 0;
		}
		
		//Special handle for base level
		std::cout << "\nh\t";
		for(int i = 0; i < idk[0].size(); i++){
			std::cout << idk[0][i] << "\t";
		}
		std::cout << "t";
		std::cout << "\n";
		
	}
	#endif
	
	void find(const_reference data) {
		node *mynode = new node(alloc.allocate(1));
		*(mynode -> data) = data;
		
		node *curr_ptr = head;
		
		// Finding pos to insert
		while( curr_ptr -> bottom != nullptr){
			std::cout << "Level Case\n";
			if( !( node::compare_me(this, *(curr_ptr -> next), *mynode) ) ){
				curr_ptr = curr_ptr -> bottom;
			}
			else{
				curr_ptr = curr_ptr -> next;
			}
		}	
		std::cout << "base case\n";
		while(node::compare_me(this, *(curr_ptr -> next), *mynode)){
				curr_ptr = curr_ptr -> next;
		}
	}
	
	
	
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
