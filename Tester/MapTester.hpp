#pragma once

#include "Tester.hpp"
#include <iostream>
#include "vector"
#include "stack"
#include "map"
#define COUNT 5
#include "list"



template<class container_type, class element_type>
class MapTester: public Tester<container_type, element_type> {

private:

public:
	MapTester(container_type container):
			Tester<container_type, element_type>(container){}

	void print_state() {
		std::cout << "Vector state:" << std::endl;

		std::cout << "empty: " << this->container.empty() << std::endl;
		std::cout << "size: " << this->container.size() << std::endl;
		std::cout << "max_size: " << this->container.max_size() << std::endl;
		std::cout << "elements: [";
		for (typename container_type::iterator it = this->container.begin(); it < this->container.end(); it++)
			std::cout << *it << ", ";
		std::cout << "]" << std::endl;

		std::cout << std::endl;

	}

	void test_assign(){
		this->container.assign(COUNT, 9);
		print_state();

//        this->container.assign(2147483647, 1);
//        print_state();
	}

	void test_assign_iterator(){
		container_type tmp_cont;
		tmp_cont.assign(COUNT, 1);
		this->container.assign(tmp_cont.begin(), tmp_cont.end());
		print_state();
	}

    void test_biderect_it () {
        std::list<element_type> lst;
        typename std::list<element_type>::iterator lst_it;
        for (int i = 1; i < 5; ++i)
            lst.push_back(i * 3);

        container_type vct(lst.begin(), lst.end());
        print_state();

        lst_it = lst.begin();
        for (int i = 1; lst_it != lst.end(); ++i)
            *lst_it++ = i * 5;
        vct.assign(lst.begin(), lst.end());
        print_state();

        vct.insert(vct.end(), lst.rbegin(), lst.rend());
        print_state();
    }

    void	checkErase(container_type  &vct,
                       typename container_type::iterator it)
    {
        static int i = 0;
        std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
        print_state();
    }

    void test_erase() {
        container_type vct(10);


        for (unsigned long int i = 0; i < vct.size(); ++i)
            vct[i] = (vct.size() - i);
        print_state();

        checkErase(vct, vct.erase(vct.begin() + 2));

        checkErase(vct, vct.erase(vct.begin()));
        checkErase(vct, vct.erase(vct.end() - 1));

        checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
        checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

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

        this->container.insert(this->container.end() - 1, 2, 6);
        print_state();




	}

    void test_swap(){
        container_type tmp_cont;
        tmp_cont.assign(COUNT, 1);
//        this->container.swap(tmp_cont);
//        print_state();
        ft::swap(this->container, tmp_cont);
        print_state();
    }

    template <typename Ite_1, typename Ite_2>
    void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
    {
        std::cout << (first < second) << std::endl;
        std::cout << (first <= second) << std::endl;
        std::cout << (first > second) << std::endl;
        std::cout << (first >= second) << std::endl;
        if (redo)
            ft_eq_ope(second, first, 0);
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

        const int size = 5;
        container_type vct(size);
        typename container_type::iterator it_0(vct.begin());
        typename container_type::iterator it_1(vct.end());
        typename container_type::iterator it_mid;

        typename container_type::const_iterator cit_0 = vct.begin();
        typename container_type::const_iterator cit_1;
        typename container_type::const_iterator cit_mid;

        for (int i = size; it_0 != it_1; --i)
            *it_0++ = i;
        print_state();
        it_0 = vct.begin();
        cit_1 = vct.end();
        it_mid = it_0 + 3;
        cit_mid = it_0 + 3;
        cit_mid = cit_0 + 3;
        cit_mid = it_mid;

        std::cout << std::boolalpha;
        std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

        std::cout << "\t\tft_eq_ope:" << std::endl;
        // regular it
        ft_eq_ope(it_0 + 3, it_mid);
        ft_eq_ope(it_0, it_1);
        ft_eq_ope(it_1 - 3, it_mid);
        // const it
        ft_eq_ope(cit_0 + 3, cit_mid);
        ft_eq_ope(cit_0, cit_1);
        ft_eq_ope(cit_1 - 3, cit_mid);
        // both it
        ft_eq_ope(it_0 + 3, cit_mid);
        ft_eq_ope(it_mid, cit_0 + 3);
        ft_eq_ope(it_0, cit_1);
        ft_eq_ope(it_1, cit_0);
        ft_eq_ope(it_1 - 3, cit_mid);
        ft_eq_ope(it_mid, cit_1 - 3);
    }


    void test_iterator() {
        const int size = 5;
        container_type vct(size);
        typename container_type::iterator it = vct.begin();
        typename container_type::const_iterator ite = vct.begin();

        for (int i = 0; i < size; ++i)
            it[i] = (size - i) * 5;

        it = it + 5;
        it = 1 + it;
        it = it - 4;
        std::cout << *(it += 2) << std::endl;
        std::cout << *(it -= 1) << std::endl;

        *(it -= 2) = 42;
        *(it += 2) = 21;

        std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
        std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

        std::cout << "(it == const_it): " << (ite == it) << std::endl;
        std::cout << "(const_ite - it): " << (ite - it) << std::endl;
        std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

        print_state();
    }

    void test_iterator_arrow() {
        const int size = 5;
        container_type vct(size);
        typename container_type::iterator it(vct.begin());
        typename container_type::const_iterator ite(vct.end());

        for (int i = 1; it != ite; ++i)
            *it++ = i;
        print_state();

        it = vct.begin();
        ite = vct.begin();

        std::cout << *(++ite) << std::endl;
        std::cout << *(ite++) << std::endl;
        std::cout << *ite++ << std::endl;
        std::cout << *++ite << std::endl;



        std::cout << *(++it) << std::endl;
        std::cout << *(it++) << std::endl;
        std::cout << *it++ << std::endl;
        std::cout << *++it << std::endl;

        std::cout << *(--ite) << std::endl;
        std::cout << *(ite--) << std::endl;
        std::cout << *--ite << std::endl;
        std::cout << *ite-- << std::endl;


        std::cout << *(--it) << std::endl;
        std::cout << *(it--) << std::endl;
        std::cout << *it-- << std::endl;
        std::cout << *--it << std::endl;
    }

    void test_rite() {
        const int size = 5;
        container_type vct(size);
        typename container_type::iterator it_ = vct.begin();
        typename container_type::reverse_iterator it(it_);

        for (int i = 0; i < size; ++i)
            vct[i] = (i + 1) * 5;
        print_state();

        std::cout << (it_ == it.base()) << std::endl;
        std::cout << (it_ == (it + 3).base()) << std::endl;

        std::cout << *(it.base() + 1) << std::endl;
        std::cout << *(it - 3) << std::endl;
        std::cout << *(it - 3).base() << std::endl;
        it -= 3;
        std::cout << *it.base() << std::endl;

        std::cout << "TEST OFFSET" << std::endl;
        std::cout << *(it) << std::endl;
        std::cout << *(it).base() << std::endl;
        std::cout << *(it - 0) << std::endl;
        std::cout << *(it - 0).base() << std::endl;
        std::cout << *(it - 1).base() << std::endl;

        it = vct.rbegin();
        typename container_type::const_reverse_iterator ite = vct.rbegin();

        for (int i = 0; i < size; ++i)
            it[i] = (size - i) * 5;

        it = it + 5;
        it = 1 + it;
        it = it - 4;
        std::cout << *(it += 2) << std::endl;
        std::cout << *(it -= 1) << std::endl;

        *(it -= 2) = 42;
        *(it += 2) = 21;

        std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

        std::cout << "(it == const_it): " << (ite == it) << std::endl;
        std::cout << "(const_ite - it): " << (ite - it) << std::endl;
        std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
    }

	void run_test() {
		print_state();
//		this->test_assign();
//		this->test_assign_iterator();
//		this->test_clear();
//		this->test_reserve();
		this->test_insert();
//
//
//
//        this->test_comp_operators();
//        this->test_swap();
//        this->test_biderect_it();
//        this->test_erase();
//        this->test_iterator();
//        this->test_iterator_arrow();
//        this->test_rite();

	};


//	Tester(const Tester &tester);
//
//	~Tester();
//
//	Tester &operator=(const Tester &tester);
};

