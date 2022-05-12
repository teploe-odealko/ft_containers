
//
// Created by Brittni Ashleigh on 5/10/22.
//

#pragma once

#include <memory>

namespace ft {

	template<class T, class Alloc = std::allocator <T> >
	class vector {

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
//		typedef ft::vector_iterator<pointer> iterator;
//		typedef ft::vector_iterator<const_pointer> const_iterator;
//		typedef ft::reverse_iterator<iterator> reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit vector (const allocator_type& alloc = allocator_type()):
			_allocator(alloc), _cap(0), _size(0), _ptr(NULL) {}
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()): _allocator(alloc), _cap(0) {

		}
//		template <class InputIterator>
//		vector (InputIterator first, InputIterator last,
//				const allocator_type& alloc = allocator_type()) {
//
//		}
//		vector (const vector& x) {
//
//		}


		size_type size() const {
			return _size;
		}

		bool empty() const {
			return _size == 0;
		}

		template <class InputIterator>
//		void assign (InputIterator first, InputIterator last) {};
		void assign (size_type n, const value_type& val) {
			clear();
			_allocator.allocate(n);
		};
		void clear() {
			while (_size--) {
				_allocator.destroy(_ptr[_size]);
			}
		};

		void reserve (size_type n) {
			if (n > _cap) {
				pointer *new_ptr = _allocator.allocate(n);
				if (_ptr)
				{
					int s = _size;
					while(s--){
						new_ptr[s] = _ptr[s];
						_allocator.destroy(_ptr[s]);
					}
					_allocator.dealocate(_ptr);
				}
				_ptr = new_ptr;
				_cap = n;
			}
		};

	private:
		allocator_type _allocator;
		pointer _ptr;
		size_type _size;
		size_type _cap;
		
	};
}