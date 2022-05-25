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
    protected:
		pointer _ptr;
	public:

		vector_iterator(pointer ptr = 0) : _ptr(ptr) {};

        template<class I>
		vector_iterator(const vector_iterator<I> &it) : _ptr(it.base()) {};

		virtual ~vector_iterator() {}

        pointer base() const { return _ptr; }

        vector_iterator& operator=(const vector_iterator& other)
        {
            if (this == &other)
                return *this;
            _ptr = other._ptr;
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

        template<class I>
		bool operator==(const vector_iterator<I> &it) const { return _ptr == it.base(); }

        template<class I>
		bool operator!=(const vector_iterator<I> &it) const { return _ptr != it.base(); }

		vector_iterator &operator--() {
			_ptr--;
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

//        template<class I>
//		friend vector_iterator<I> operator+(size_t n, const vector_iterator<I> &iter) {
//			return iter + n;
//		}

//        template <typename T>
//        ptrdiff_t operator-(const vector_iterator<T>& it) { return this->base() - it.base(); }
//
//		vector_iterator operator-(difference_type n) const {
//			return _ptr - n;
//		}

//		friend vector_iterator<iterator_type> operator-(size_t n, const vector_iterator<iterator_type> &iter) {
//			return iter - n;
//		}
        vector_iterator operator-(difference_type n) const { return _ptr - n; }

        template <typename T>
        ptrdiff_t operator-(const vector_iterator<T>& it) { return this->base() - it.base(); }

        pointer operator->() { return _ptr; }

        template<class I>
		bool operator>(const vector_iterator<I> &it) const { return _ptr > it.base(); }

        template<class I>
		bool operator<(const vector_iterator<I> &it) const { return _ptr < it.base(); }

        template<class I>
		bool operator>=(const vector_iterator<I> &it) const { return _ptr >= it.base(); }

        template<class I>
		bool operator<=(const vector_iterator<I> &it) const { return _ptr <= it.base(); }

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

    template <typename T>
    vector_iterator<T> operator+(size_t n, const vector_iterator<T> &iter) { return iter + n; }

    template <typename T>
    ptrdiff_t operator-(const vector_iterator<T>& lhi, const vector_iterator<T>& rhi) { return lhi.base() - rhi.base(); }
}
