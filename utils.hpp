#pragma once


#include <cstddef>
#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
    class out_of_range: std::exception {
    public:
        explicit out_of_range (const std::string& what_arg);
    };

    template<class T, T v>
    struct integral_constant {
        static const bool value = v;
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const { return value; }
    };
    struct true_type : public ft::integral_constant<bool, true> {};
    struct false_type : public ft::integral_constant<bool, false> {};
    template <class T> struct is_integral : public false_type {};
    template <> struct is_integral<bool> : public true_type {};
    template <> struct is_integral<char> : public true_type {};
    template <> struct is_integral<char16_t> : public true_type {};
    template <> struct is_integral<char32_t> : public true_type {};
    template <> struct is_integral<wchar_t> : public true_type {};
    template <> struct is_integral<signed char> : public true_type {};
    template <> struct is_integral<short int> : public true_type {};
    template <> struct is_integral<int> : public true_type {};
    template <> struct is_integral<long int> : public true_type {};
    template <> struct is_integral<long long int> : public true_type {};
    template <> struct is_integral<unsigned char> : public true_type {};
    template <> struct is_integral<unsigned short int> : public true_type {};
    template <> struct is_integral<unsigned int> : public true_type {};
    template <> struct is_integral<unsigned long int> : public true_type {};
    template <> struct is_integral<unsigned long long int> : public true_type {};

    template<bool B, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

//	template <class InputIter>
//	typename ft::iterator_traits<InputIter>::difference_type
//	distance(InputIter first, InputIter last, ft::input_iterator_tag)
//	{
//		typename ft::iterator_traits<InputIter>::difference_type r(0);
//		for (; first != last; ++first)
//			++r;
//		return r;
//	}
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) return false;
            else if (*first1<*first2) return true;
            ++first1; ++first2;
        }
        return (first2!=last2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1!=last1) {
            if (*first1 != *first2)   // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class T> void swap ( T& a, T& b )
    {
        T c(a); a=b; b=c;
    }


    template <class InputIter>
    typename std::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last, std::input_iterator_tag)
    {
        typename std::iterator_traits<InputIter>::difference_type r(0);
        for (; first != last; ++first)
            ++r;
        return r;
    }

    template <class RandIter>
    typename std::iterator_traits<RandIter>::difference_type
    distance(RandIter first, RandIter last, std::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIter>
    typename ft::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last, ft::input_iterator_tag)
    {
        typename ft::iterator_traits<InputIter>::difference_type r(0);
        for (; first != last; ++first)
            ++r;
        return r;
    }

    template <class RandIter>
    typename ft::iterator_traits<RandIter>::difference_type
    distance(RandIter first, RandIter last, ft::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIter>
    typename ft::iterator_traits<InputIter>::difference_type
    distance(InputIter first, InputIter last)
    {
        return distance(first, last, typename ft::iterator_traits<InputIter>::iterator_category());
    }

}

//namespace std {
//    template <class T, class A>
//    void swap(ft::vector<T, A>& v1, ft::vector<T, A>& v2 ) { v1.swap(v2); }
//
//    template <class Key, class T, class Compare, class A>
//    void swap(ft::map<Key, T, Compare, A>& m1, ft::map<Key, T, Compare, A>& m2 ) { m1.swap(m2); }
//
//    template<class Key, class Compare, class A>
//    void swap(ft::set<Key, Compare, A>& s1, ft::set<Key, Compare, A>& s2) { s1.swap(s2); }
//}
