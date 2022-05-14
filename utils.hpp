#pragma once


#include <cstddef>
#include <iostream>
#include "iterator_traits.hpp"

namespace ft {

//	template <class InputIter>
//	typename ft::iterator_traits<InputIter>::difference_type
//	distance(InputIter first, InputIter last, ft::input_iterator_tag)
//	{
//		typename ft::iterator_traits<InputIter>::difference_type r(0);
//		for (; first != last; ++first)
//			++r;
//		return r;
//	}

	template <class RandIter>
	typename ft::iterator_traits<RandIter>::difference_type
	distance(RandIter first, RandIter last, ft::random_access_iterator_tag)
	{
		return last - first;
	}
}
