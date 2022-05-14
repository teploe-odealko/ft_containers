#pragma once

#include "../iterator_traits.hpp"

namespace ft {


	template<class IteratorType>
	class vector_iterator {
	public:
		typedef IteratorType iterator_type;
		typedef typename ft::random_access_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference reference;
	private:
		pointer _ptr;
	public:

		vector_iterator() : _ptr(NULL) {};

		vector_iterator(pointer ptr) : _ptr(ptr) {};

		vector_iterator(vector_iterator<iterator_type> &it) : _ptr(it.base()) {};

		virtual ~vector_iterator() {}

		pointer base() const { return _ptr; }

		vector_iterator &operator=(const vector_iterator &it) {
			if (this != &it) {
				_ptr = it.base();
			}
			return *this;
		}

		vector_iterator &operator++() {
			_ptr++;
			return *this;
		}

		vector_iterator operator++(int) {
			vector_iterator prev(*this);
			operator++();
			return prev;
		}

		bool operator==(const vector_iterator<iterator_type> &it) const { return _ptr == it.base(); }

		bool operator!=(const vector_iterator<iterator_type> &it) const { return _ptr != it.base(); }

		vector_iterator &operator--() {
			_ptr++;
			return *this;
		}

		vector_iterator operator--(int) {
			vector_iterator prev(*this);
			operator--();
			return prev;
		}

		vector_iterator operator+(difference_type n) const {
			return _ptr + n;
		}

		friend vector_iterator<iterator_type> operator+(size_t n, const vector_iterator<iterator_type> &iter) {
			return iter + n;
		}

		vector_iterator operator-(difference_type n) const {
			return _ptr - n;
		}

		friend vector_iterator<iterator_type> operator-(size_t n, const vector_iterator<iterator_type> &iter) {
			return iter - n;
		}

		bool operator>(const vector_iterator<iterator_type> &it) const { return _ptr > it.base(); }

		bool operator<(const vector_iterator<iterator_type> &it) const { return _ptr < it.base(); }

		bool operator>=(const vector_iterator<iterator_type> &it) const { return _ptr >= it.base(); }

		bool operator<=(const vector_iterator<iterator_type> &it) const { return _ptr <= it.base(); }

		vector_iterator operator+=(difference_type n) {
			_ptr += n;
			return *this;
		}

		vector_iterator operator-=(difference_type n) {
			_ptr -= n;
			return *this;
		}

		reference operator*() { return *_ptr; }

		reference operator[](difference_type n) const { return _ptr[n]; }

	};
}
