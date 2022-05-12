
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
#define quote(x) #x




class ValuableMethods
{
public:
	virtual bool empty() = 0;
	virtual size_t size() = 0;

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
	}

	void print_state() {
		std::cout<< "Container state:" << std::endl;
		for(std::vector<std::string>::iterator it = valuable_methods.begin(); it != valuable_methods.end(); ++it) {
			if (*it == "empty") {
				std::cout << "empty: " << container.empty() << std::endl;
			}
			else if (*it == "size") {
				std::cout << "size: " << container.size() << std::endl;
			}
			else if (*it == "top") {
				if (container.size())
					std::cout << "top: " << container.top() << std::endl;
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

	void test_stack() {
		print_state();
		test_push();
		test_pop();
	}

	void run_test() {
		if (container_name == "stack")
			test_stack();
	}

//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};


#endif //CONTAINERS_TESTER_HPP
