CC=g++

sequence: node.cpp sequence.cpp seq_test.cpp
	$(CC) node.cpp sequence.cpp seq_test.cpp -g -o runSequence
	./runSequence
	
node: node.cpp node_test.cpp
	$(CC) node.cpp node_test.cpp -g -o runNode
	./runNode

