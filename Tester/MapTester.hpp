#pragma once

#include "Tester.hpp"
#include <iostream>
#include "map"
#define COUNT 5
#include "list"
#include "../map.hpp"



template<class container_type, class element_type>
class MapTester {

private:
	std::string container_name;
	std::vector<std::string> valuable_methods;
	container_type container;

public:
	MapTester(container_type container): container(container) {}

	element_type create_random_element() {
		return element_type(rand(), rand());
	}

	void print_state() {
		std::cout << "Vector state:" << std::endl;

		std::cout << "empty: " << this->container.empty() << std::endl;
		std::cout << "size: " << this->container.size() << std::endl;
		std::cout << "max_size: " << this->container.max_size() << std::endl;
		std::cout << "elements: [";
		for (typename container_type::iterator it = this->container.begin(); it != this->container.end(); it++)
			std::cout << (*it).first << "-" << (*it).second << ", ";
		std::cout << "]" << std::endl;

		std::cout << std::endl;

	}


    void	checkErase(container_type  &vct,
                       typename container_type::iterator it)
    {
        static int i = 0;
        std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
        print_state();
    }



	void test_clear(){
		this->container.clear();
		print_state();
	}

	void test_insert(){
		container_type tmp;
		tmp.insert(this->create_random_element());
		tmp.insert( this->create_random_element());
		tmp.insert(this->create_random_element());
		this->container.insert(tmp.begin(), tmp.end());
		this->container.insert(this->create_random_element());
		this->container.insert(this->create_random_element());
		this->container.insert(this->create_random_element());
		print_state();

//        this->container.insert(this->container.end() - 1, 2, 6);
//        print_state();

	}

    void test_swap(){
        container_type tmp;
        tmp.insert(create_random_element());
        tmp.insert(create_random_element());
        tmp.insert(create_random_element());
        tmp.insert(create_random_element());
//        this->container.swap(tmp_cont);
//        print_state();
        ft::swap(this->container, tmp);
        print_state();
    }

    void test_comp_operators() {
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

	void test_erase() {
		element_type new_elem = create_random_element();

		this->container.insert(new_elem);
		print_state();
		this->container.erase(new_elem.first);
		print_state();
		this->container.erase(this->container.begin());
		print_state();
		this->container.erase(this->container.begin(), this->container.end());
		print_state();
	}


	void run_test() {
		print_state();

		this->test_clear();
		this->test_insert();
        this->test_comp_operators();
        this->test_swap();
		this->test_erase();


	};


//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};

