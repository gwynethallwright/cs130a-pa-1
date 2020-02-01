All: array.out linkedlist.out
array.out: array.cpp
	g++ -std=c++17 -o array.out array.cpp
linkedlist.out: ll_2.cpp
	g++ -std=c++17 -o linkedlist.out ll_2.cpp
