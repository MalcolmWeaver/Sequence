//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init() // only member functions can call this. No other file should call it
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    
    	sequence::~sequence(){
    		list_clear(head_ptr);
    	}
    
    	// 	NON-CONST MEMBER FUNCTIONS
    	void sequence::operator =(const sequence& source){
    		list_clear(this->head_ptr);	// must free old stuff before changine everything
	    	
	    	list_copy(source.head_ptr, head_ptr, tail_ptr); // memory leak
	    	std::size_t loc;
	    	node* myCursor;
	    	many_nodes = source.many_nodes;
	    	if(source.precursor == NULL){
	    		precursor = NULL;
	    		cursor = head_ptr;
	    		if(tail_ptr){assert(tail_ptr->link() == NULL);}
	    		return;
	    	}
	    	else
	    	{
	    		for(loc=1, myCursor = source.head_ptr; myCursor != source.precursor; ++loc, myCursor = myCursor->link()){
	    			assert(myCursor != NULL);
	    		}
	    	
	    		precursor = list_locate(head_ptr, loc);
	    		cursor = precursor->link();
	    		if(precursor){assert(precursor->link() == cursor);}
	    		return;
	    	}
    	}
    	
    	void sequence::start( ){
    		if(!head_ptr)
    		{
	    		std::cout << "Nothing in the list" << std::endl;
	    		return;
    		}
    		cursor = head_ptr;
    		precursor = NULL;
    		return;
    	}
	
	void sequence::end( )
	{
		if(!head_ptr)
    		{
    			std::cout << "Nothing in the list" << std::endl;
    			return;
    		}
    		cursor = head_ptr;
    		precursor = NULL;
    		while(cursor->link()){
    			precursor = cursor;
    			cursor = cursor->link();
    		}
    		assert(cursor->link() == NULL);
    		assert(precursor->link() == cursor);
    		return;
	}
    	
    	void sequence::attach(const value_type& entry){
		if(!is_item())
		{
			if(!precursor)
			{
				//empty list
				assert(many_nodes == 0);
				list_head_insert(head_ptr, entry);	// memory leak
				cursor = head_ptr;
				tail_ptr = head_ptr;
			}
			else
			{
				//going to the end of list
				list_insert(precursor, entry);
				cursor = precursor->link();
				tail_ptr = cursor;
			}
		}
		else
		{
			list_insert(cursor, entry);
			precursor = cursor;
			cursor = cursor->link();
			if(cursor->link() == NULL){tail_ptr = cursor;} // case where cursor originally pointed to last node
		}
		++many_nodes;
    	}
    	
    	void sequence::insert(const value_type& entry){
    		if(!is_item())
		{
			list_head_insert(head_ptr, entry);
			//head_ptr is updated
			cursor = head_ptr;
			precursor = NULL;
		}
		else{
			if(!precursor)
			{
			//empty list or 1 node
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				if(cursor->link())
				{
				tail_ptr = cursor->link();
				}
			}
			else
			{
				list_insert(precursor, entry);
				cursor = precursor->link(); 
			}
		}
		++many_nodes;
    	}
    	
    	void sequence::remove_current(){
    		assert(is_item());
    		if(!precursor){
    			//removing head
			if(tail_ptr == head_ptr){tail_ptr = NULL;}
			list_head_remove(head_ptr);
    		}
    		else
    		{
    			list_remove(precursor);
    			cursor = precursor->link();
    			if(!cursor){
    				tail_ptr = precursor;
    				return;
    			}
    		}
    		--many_nodes;
    	}
    	
    	
    	//	CONST MEMBER FUNCTIONS
    	void sequence::advance( ){
    		assert(is_item());
    		precursor = cursor;
    		cursor = cursor->link();
    		
    	}
    	
    	sequence::size_type sequence::size( ) const{
    		return many_nodes;
    	}

	bool sequence::is_item( ) const{
		if(cursor){return true;}
		else{return false;}
	}
	
	sequence::value_type sequence::current( ) const{
		assert(is_item());
		return cursor->data();
	}
    
}
