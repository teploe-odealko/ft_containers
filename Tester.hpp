
//
// Created by Brittni Ashleigh on 5/11/22.
//

#ifndef CONTAINERS_TESTER_HPP
#define CONTAINERS_TESTER_HPP

#include <iostream>
#include "vector"
#include "stack"
#include "map"
template<class T>
class Tester {

private:
	std::vector<std::string> valuable_methods;

public:
	Tester(const std::vector<std::string>& valuable_methods):
	valuable_methods(valuable_methods) {}

	void print_state(T t) {

		for(std::vector<std::string>::iterator it = valuable_methods.begin(); it != valuable_methods.end(); ++it) {
			if (*it == "value_type") {
//				std::cout << ((std::map<int, int>) t);
			}
			else if (*it == "container_type") {
				std::cout << t.container_type;
			}
			else if (*it == "size_type") {
				std::cout << t.size_type;
			}
		}

	}

//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};


#endif //CONTAINERS_TESTER_HPP
