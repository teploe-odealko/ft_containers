
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
#include "../vector.hpp"
#include "stack"
#include "../stack.hpp"




template<class container_type, class element_type>
class Tester {

protected:
	std::string container_name;
	std::vector<std::string> valuable_methods;
	container_type container;


public:
	Tester(container_type container):  container(container) {

	}
//	bool if_vector() {
//		if (typeid(container_type) == typeid(ft::vector<element_type>)
//		|| typeid(container_type) == typeid(std::vector<element_type>))
//			return true;
//		return false;
//	}
//
//	bool if_stack() {
//		if (typeid(container_type) == typeid(ft::stack<element_type>)
//		|| typeid(container_type) == typeid(std::stack<element_type>))
//			return true;
//		return false;
//	}


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

	virtual void run_test() = 0;
	virtual void print_state() = 0 ;




};


#endif //CONTAINERS_TESTER_HPP
