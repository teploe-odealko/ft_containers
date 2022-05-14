
//
// Created by Brittni Ashleigh on 5/10/22.
//

#pragma once

#include <memory>
#include "Iterators/vector_iterator.hpp"
#include "utils.hpp"

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
		typedef ft::vector_iterator<pointer> iterator;
		typedef ft::vector_iterator<const_pointer> const_iterator;
//		typedef ft::reverse_iterator<iterator> reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit vector (const allocator_type& alloc = allocator_type()):
			_allocator(alloc), _ptr(NULL), _size(0), _cap(0) {}

		explicit vector (size_type n,
						 const value_type& val = value_type(),
						 const allocator_type& alloc =allocator_type()):
		_allocator(alloc), _ptr(NULL), _size(0), _cap(0){
			assign(n, val);
		}

		template <class InputIterator>
		vector (InputIterator first,
				InputIterator last,
				const allocator_type& alloc = allocator_type()):
		_allocator(alloc), _ptr(NULL), _size(0), _cap(0){
			assign(first, last);
		}
//		vector (const vector& x) {
//
//		}

//		iterator begin() {
//
//		}
//		const_iterator begin() const;
		size_type capacity() const { return _cap; }
		size_type max_size() const {
			return _allocator.max_size();
		}
		size_type size() const { return _size; }
		bool empty() const { return _size == 0;	}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			clear();
			reserve(ft::distance(first, last));
			insert(begin(), first, last);
		};
		void assign (size_type n, const value_type& val) {
			clear();
			reserve(n);
			insert(begin(), n, val);
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

		iterator begin() { return iterator(_ptr); };
		iterator end() { return iterator(_ptr + _size); };
		const_iterator begin() const { return const_iterator(_ptr); };

		iterator insert (iterator position, const value_type& val) {
			insert(position, 1, val);
			return iterator(_ptr) + position;
		};

		void insert (iterator position, size_type n, const value_type& val) {
			size_type pos = ft::distance(begin(), position);
			size_type new_cap;
			pointer new_ptr;
			int new_size = 0;
			if (_size + n > _cap) {
				new_cap = !_cap ? n : _cap * 2 < n + _size ? _size + n : _cap * 2;
				try {
					new_ptr = _allocator.allocate(new_cap);
					for (; new_size < _size; new_size++)
						new_ptr[new_size] = _ptr[new_size];
					for (; new_size < n; ++new_size)
						_allocator.construct(new_ptr + new_size, val);
					replacement(new_ptr, new_size, new_cap);
				} catch (...) {
					full_clear(new_ptr + pos, new_size - pos, new_cap);
					throw;
				}
			} else {
				for (int i = 0; i < n; i++)
					_allocator.construct(_ptr + pos + i, val);
			}
		};

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			size_type n = ft::distance(first, last);
			size_type pos = ft::distance(begin(), position);
			size_type new_size = 0;
			size_type new_cap;
			pointer new_ptr;

			if (_size + n > _cap) {
				new_cap = _cap == 0 ? n : _cap * 2 < _size + n ? _size + n : _cap * 2;
				try {
					new_ptr = _allocator.allocate(new_cap);
					for (; new_size < pos; new_size++)
						new_ptr[new_size] = _ptr[new_size];
					while (first != last)
						_allocator.construct(new_ptr + new_size, value_type(*first));
					replacement(new_ptr, new_size, new_cap);
				} catch (...) {
					clear(new_ptr, new_size, new_cap);
					throw;
				}
			} else {
				for (int i = 0; i < n; i++)
				{
					_allocator.construct(_ptr + pos + i, value_type(*first));
					first++;
				}
			}
		};

		reference front() { return *_ptr; }

		const_reference front() const { return *_ptr; }

		reference back() { return _ptr[_size - 1]; }

		const_reference back() const { return _ptr[_size - 1]; }

	private:
		allocator_type _allocator;
		pointer _ptr;
		size_type _size;
		size_type _cap;

		void full_clear(pointer new_ptr, size_type new_size, size_type new_cap)
		{
			for (; new_size > 0; --new_size)
				_allocator.destroy(new_ptr + new_size - 1);
			_allocator.deallocate(new_ptr, new_cap);
		}

		void replacement(pointer new_ptr, size_type new_size, size_type new_cap)
		{
			_allocator.deallocate(_ptr, _cap);
			_size = new_size;
			_cap = new_cap;
			_ptr = new_ptr;
		}
		
	};

}