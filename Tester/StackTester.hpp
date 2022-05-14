#pragma once

#include <iostream>
#include "vector"
#include "stack"
#include "map"
#define COUNT 5
#include "vector"
#include "../vector.hpp"
#include "stack"
#include "../stack.hpp"
#include "Tester.hpp"

template<class container_type, class element_type>
class StackTester: public Tester<container_type, element_type> {

private:


public:
	StackTester(container_type container):
		Tester<container_type, element_type>(container) {
	}



	void print_state() {
		std::cout<< "Container state:" << std::endl;

		std::cout << "empty: " << this->container.empty() << std::endl;
		std::cout << "size: " << this->container.size() << std::endl;
		if (this->container.size())
			std::cout << "top: " << this->container.top() << std::endl;
		else
			std::cout << "top: " << "-" << std::endl;


		std::cout << std::endl;
	}


	void run_test() {
		print_state();
		this->test_push();
		this->test_pop();
	}

};


