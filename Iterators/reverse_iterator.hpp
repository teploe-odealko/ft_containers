#pragma once

#include "../iterator_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {
    template<class IteratorType>
    class reverse_iterator: public ft::vector_iterator<IteratorType> {

	public:

		reverse_iterator() : ft::vector_iterator<IteratorType>() {};

		reverse_iterator(typename ft::vector_iterator<IteratorType>::pointer ptr = 0)
        : ft::vector_iterator<IteratorType>(ptr) {};

        template<class I>
		reverse_iterator(reverse_iterator<I> &it) : ft::vector_iterator<IteratorType>(it.base()) {};

		virtual ~reverse_iterator() {}



		reverse_iterator &operator++() {
            this->_ptr--;
			return *this;
		}

		reverse_iterator &operator--() {
			this->_ptr++;
			return *this;
		}

		reverse_iterator operator+(typename ft::vector_iterator<IteratorType>::difference_type n) const {
			return this->_ptr - n;
		}

		reverse_iterator operator-(typename ft::vector_iterator<IteratorType>::difference_type n) const {
			return this->_ptr + n;
		}

		bool operator>(const reverse_iterator<typename ft::vector_iterator<IteratorType>::iterator_type > &it) const {
            return this->_ptr < it.base();
        }

		bool operator<(const reverse_iterator<typename ft::vector_iterator<IteratorType>::iterator_type > &it) const {
            return this->_ptr > it.base();
        }

		bool operator>=(const reverse_iterator<typename ft::vector_iterator<IteratorType>::iterator_type > &it) const {
            return this->_ptr <= it.base();
        }

		bool operator<=(const reverse_iterator<typename ft::vector_iterator<IteratorType>::iterator_type > &it) const {
            return this->_ptr >= it.base();
        }

		reverse_iterator operator+=(typename ft::vector_iterator<IteratorType>::difference_type n) {
			this->_ptr -= n;
			return *this;
		}

		reverse_iterator operator-=(typename ft::vector_iterator<IteratorType>::difference_type n) {
			this->_ptr += n;
			return *this;
		}

        typename ft::vector_iterator<IteratorType>::reference operator[]
        (typename ft::vector_iterator<IteratorType>::difference_type n) const {
            return this->_ptr[-n];
        }

	};
}
