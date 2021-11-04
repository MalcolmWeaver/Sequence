#include <iostream>
#include "sequence.h"

using coen79_lab6::sequence;

void printSequence(sequence &s) {
        sequence seq(s);
        seq.start();

        // Loop to print the sequence.
        while(seq.is_item()) {
        	std::cout << seq.current() << " ";
                seq.advance();
                }
	std::cout << std::endl;
}
        

int main(){
	
	sequence s1;
	s1.attach(12);
	printSequence(s1);
	s1.insert(15);
	printSequence(s1);
	s1.remove_current();	
	printSequence(s1);
}
