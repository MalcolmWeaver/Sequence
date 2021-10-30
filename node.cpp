// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <iostream>
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{

    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
		head_ptr = NULL;
		tail_ptr = NULL;

		if(start_ptr == NULL){
			return;
		}
		
		list_head_insert(head_ptr,start_ptr->data());
		if(start_ptr == end_ptr){	// directions unclear as to whether include the first or exclude last in 1 node case
			head_ptr->set_link(NULL);
			return;
		}
		tail_ptr = head_ptr;	// initializing tail_ptr for lists of size at least 1
		node* cursor = start_ptr->link();		
		while(cursor != end_ptr){
			assert(cursor);	// if cursor is Null, it means that end ptr did not come after start cursor
			list_insert(tail_ptr, cursor->data());
			tail_ptr = tail_ptr->link();
			cursor = cursor->link();		
		}
		tail_ptr->set_link(NULL);
	}
	
	void list_print (const node* head_ptr){
		const node* cursor = head_ptr;
		for (; cursor != NULL; cursor = cursor->link()){
			std::cout << "NODE: " << cursor->data() << "\t\t";
		}
		std::cout << std::endl;
	}
	
    	size_t list_occurrences(node* head_ptr, const node::value_type& target){
		size_t count(0);
		node * cursor = head_ptr;
		for(; cursor != NULL; cursor = cursor->link()){
			if(cursor->data() == target){
				++count;
			}
		} 
		return count;   	
    	}
    	
    	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
    		size_t len = list_length(head_ptr); 	// does not change head ptr
    		assert(position > 0 && position <= len + 1);
    		node * cursor = head_ptr;
    		if(position == 1){
    			list_head_insert(head_ptr, entry);
    			return;
    		}
    		else{
    			int i = 1;
    			for(; i < position - 1; ++i, cursor = cursor->link()){ // runs p - 2 times moving cursor from node 1 to node p - 1, so that inserting a new thing next makes it #p
    				assert(cursor != NULL);
    				
    			}
    			list_insert(cursor, entry);
    		}
    	}
    	
    	void list_remove_dups(node* head_ptr){
    		// Brute force O(n^2)
    		node* cursor1 = head_ptr, *cursor2, *tmp;
    		for(; cursor1 != NULL; cursor1 = cursor1->link()){
    			for(cursor2 = cursor1; cursor2->link() != NULL; ){
    				if(cursor2->link()->data() == cursor1->data()){
    					list_remove(cursor2);
    				}    			
    				else{
    					cursor2 = cursor2->link();
    				}
    			}
    		}
    	}

	//node* list_detect_loop (node* head_ptr){
	//	
	//}

}
