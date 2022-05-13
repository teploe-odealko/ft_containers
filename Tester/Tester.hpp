
//
// Created by Brittni Ashleigh on 5/11/22.
//

#ifndef CONTAINERS_TESTER_HPP
#define CONTAINERS_TESTER_HPP

#include <iostream>
#include "vector"
#include "stack"
#include "map"
#define COUNT 5
#include "vector"
#include "vector.hpp"
#include "stack"
#include "stack.hpp"


template<class element_type>
class ContainerMethods :
		public ft::stack<element_type>, public std::stack<element_type>,
		public ft::vector<element_type>, public std::vector<element_type>
{

};


template<class container_type, class element_type>
class Tester {

private:
	std::string container_name;
	std::vector<std::string> valuable_methods;
	container_type container;


public:
	Tester(const std::string& container_name, container_type container): container_name(container_name), container(container) {
		if (container_name == "stack") {
			valuable_methods.push_back("empty");
			valuable_methods.push_back("size");
			valuable_methods.push_back("top");
			srand(1);
		}
		else if (container_name == "vector") {
//			valuable_methods.push_back("begin");
//			valuable_methods.push_back("end");
//			valuable_methods.push_back("rbegin");
//			valuable_methods.push_back("rend");

			valuable_methods.push_back("size");
//			valuable_methods.push_back("max_size");
//			valuable_methods.push_back("capacity");
			valuable_methods.push_back("empty");
//			valuable_methods.push_back("front");
//			valuable_methods.push_back("back");
			srand(1);
		}
	}

	bool if_vector() {
		if (typeid(container_type) == typeid(ft::vector<element_type>)
		|| typeid(container_type) == typeid(std::vector<element_type>))
			return true;
		return false;
	}

	bool if_stack() {
		if (typeid(container_type) == typeid(ft::stack<element_type>)
		|| typeid(container_type) == typeid(std::stack<element_type>))
			return true;
		return false;
	}

	void print_state() {
		std::cout<< "Container state:" << std::endl;
		for(std::vector<std::string>::iterator it = valuable_methods.begin(); it != valuable_methods.end(); ++it) {
			if (*it == "empty" && (if_stack() || if_vector())) {
				std::cout << "empty: " << (container).empty() << std::endl;
			}
			else if (*it == "size" && (if_stack() || if_vector())) {
				std::cout << "size: " << (container).size() << std::endl;
			}
			else if ( *it == "top" && if_stack()) {
				if (container.size())
					std::cout << "top: " << (dynamic_cast<ContainerMethods<element_type> >(container)).top() << std::endl;
				else
					std::cout << "top: " << "-" << std::endl;
			}
		}
		std::cout << std::endl;
	}

	element_type create_random_element() {
		return element_type(rand());
	}

	void test_push() {
		for (int i = 0; i < COUNT; i++)
		{
			container.push(create_random_element());
			print_state();
		}
	}

	void test_pop() {
		while (container.size() != 0)
		{
			container.pop();
			print_state();
		}
	}

	void run_test() {
		if (if_vector())
			test_vector();
		else if (typeid(container_type) != typeid(std::vector<element_type>) && if_stack())
			test_stack();
	}

	void test_stack() {
		print_state();
		test_push();
		test_pop();
	}

	void test_vector() {

	}



//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};


#endif //CONTAINERS_TESTER_HPP
