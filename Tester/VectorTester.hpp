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


template<class element_type>
class ContainerMethods :
		public ft::stack<element_type>, public std::stack<element_type>,
		public ft::vector<element_type>, public std::vector<element_type>
{

};


template<class container_type, class element_type>
class VectorTester: public Tester<container_type, element_type> {

private:

public:
	VectorTester(container_type container):
			Tester<container_type, element_type>(container){}

	void print_state() {
		std::cout << "Vector state:" << std::endl;

		std::cout << "empty: " << this->container.empty() << std::endl;
		std::cout << "size: " << this->container.size() << std::endl;
		std::cout << "max_size: " << this->container.max_size() << std::endl;
		std::cout << "capacity: " << this->container.capacity() << std::endl;
		if (this->container.size()) {
//			std::cout << "rbegin: " << *(this->container.rbegin()) << std::endl;
//			std::cout << "rend: " << *(this->container.rend()) << std::endl;
			std::cout << "front: " << this->container.front() << std::endl;
			std::cout << "back: " << this->container.back() << std::endl;
		}
		else {
//			std::cout << "rbegin: " << "-" << std::endl;
//			std::cout << "rend: " << "-" << std::endl;
			std::cout << "front: " << "-" << std::endl;
			std::cout << "back: " << "-" << std::endl;
		}
		std::cout << "elements: [";
		for (typename container_type::iterator it = this->container.begin(); it < this->container.end(); it++)
			std::cout << *it << ", ";
		std::cout << "]" << std::endl;

		std::cout << std::endl;


	}

	void test_assign(){
		this->container.assign(COUNT, 9);
		print_state();
	}

	void test_assign_iterator(){
		container_type tmp_cont;
		tmp_cont.assign(COUNT, 1);
		this->container.assign(tmp_cont.begin(), tmp_cont.end());
		print_state();
	}

	void test_clear(){
		this->container.clear();
		print_state();
	}

	void test_reserve(){
		this->container.reserve(10);
		print_state();
	}


	void test_insert(){
		this->container.insert(this->container.begin(), 4, this->create_random_element());
		print_state();

		this->container.insert(this->container.begin() + 2, 6, this->create_random_element());
		print_state();
	}

    void test_comp_operators(){
        container_type container_same(this->container);
        container_type container_smaller;
        std::cout << "COMPARISON OPERATORS" << std::endl;
        std::cout << "a == a: " << (this->container == container_same) << std::endl;
        std::cout << "a != a: " << (this->container != container_same) << std::endl;
        std::cout << "a < a: " << (this->container < container_smaller) << std::endl;
        std::cout << "a > a: " << (this->container > container_smaller) << std::endl;
        std::cout << "a <= a: " << (this->container <= container_smaller) << std::endl;
        std::cout << "a >= a: " << (this->container >= container_smaller) << std::endl;
        std::cout << std::endl;

    }

    void test_destructor(){
        this->container.~vector();
    }

	void run_test() {
		print_state();
		this->test_assign();
		this->test_assign_iterator();
		this->test_clear();
		this->test_reserve();
		this->test_insert();

        this->test_comp_operators();
        this->test_destructor();

	};


//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};

