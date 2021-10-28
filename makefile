CC=g++

node: node.cpp node_test.cpp
	$(CC) node.cpp node_test.cpp -g -o runNode


