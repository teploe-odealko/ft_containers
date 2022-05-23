
//
// Created by Brittni Ashleigh on 5/10/22.
//

#pragma once

#include <memory>
#include "Iterators/vector_iterator.hpp"
#include "Iterators/reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
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
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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

        ~vector()
        {
            clear();
            _allocator.deallocate(_ptr, _cap);
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
		void assign(
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                InputIterator last) {
			clear();
			reserve(ft::distance(first, last));
			insert(begin(), first, last);
		};

		void assign(size_type n, const value_type& val) {
			clear();
			reserve(n);
			insert(begin(), n, val);
		};

		void clear() {
            for (; _size > 0; _size--)
                _allocator.destroy(_ptr + _size);
		};


		void reserve (size_type n) {
			if (n > _cap) {
				pointer new_ptr = _allocator.allocate(n);
				if (_ptr)
				{
					int s = _size;
					while(s--){
						new_ptr[s] = _ptr[s];
						_allocator.destroy(_ptr + s);
					}
					_allocator.deallocate(_ptr, _cap);
				}
				_ptr = new_ptr;
				_cap = n;
			}
		};

		iterator begin() { return iterator(_ptr); };
		iterator end() { return iterator(_ptr + _size); };

		const_iterator begin() const { return const_iterator(_ptr); };
        const_iterator end() const { return const_iterator(_ptr + _size); };

		iterator insert (iterator position, const value_type& val) {
            size_type pos = ft::distance(begin(), position);
            insert(position, 1, val);
            return iterator(_ptr + pos);
		};

        void resize(size_type n, value_type value = value_type())
        {
            if (_size > n) {
                for (; _size > n; --_size)
                    _allocator.destroy(_ptr + _size - 1);
            }
            else {
                if (!_cap || n > 2 * _cap)
                    reserve(n);
                else if (n > _cap)
                    reserve(_cap * 2);
                for (; _size < n; ++_size)
                    _allocator.construct(_ptr + _size, value);
            }
        }

        void push_back(const value_type& value)
        {
            if (_size == _cap)
                resize(_size + 1, value);
            else
                _allocator.construct(_ptr + _size++, value);
        }

        void pop_back()
        {
            _allocator.destroy(_ptr + _size);
            _size--;
        }



		void insert (iterator position, size_type n, const value_type& val) {
			size_type pos = ft::distance(begin(), position);
			size_type new_cap;
			pointer new_ptr;
			size_type new_size = 0;
			if (_size + n > _cap) {
				new_cap = !_cap ? n : _cap * 2 < n + _size ? _size + n : _cap * 2;
				try {
					new_ptr = _allocator.allocate(new_cap);
                    move_tail(new_ptr, pos, n);
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
                move_tail(_ptr, pos, n);
				for (size_type i = 0; i < n; i++){
					_allocator.construct(_ptr + pos + i, val);
                    _size += 1;
                }
			}
		};

		template <class InputIterator>
		void insert (iterator position,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                     InputIterator last) {
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
					full_clear(new_ptr, new_size, new_cap);
					throw;
				}
			} else {
				for (size_type i = 0; i < n; i++)
				{
					_allocator.construct(_ptr + pos + i, value_type(*first));
					first++;
                    _size++;
				}
			}
		};

		reference front() { return *_ptr; }
		const_reference front() const { return *_ptr; }

		reference back() { return _ptr[_size - 1]; }
		const_reference back() const { return _ptr[_size - 1]; }

        reverse_iterator rbegin() { return reverse_iterator(_ptr + _size - 1); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_ptr + _size - 1); }
        reverse_iterator rend() { return reverse_iterator(_ptr-1); }
        const_reverse_iterator rend() const { return const_reverse_iterator(_ptr-1); }

        reference operator[](difference_type n) { return _ptr[n]; }
        const_reference operator[](difference_type n) const { return _ptr[n]; }

        reference at(size_type n)
        {
            check_range(n);
            return _ptr[n];
        }

        const_reference at(size_type n) const
        {
            check_range(n);
            return _ptr[n];
        }

        iterator erase(iterator position) { return erase(position, position + 1); }

        iterator erase(iterator first, iterator last)
        {
            size_type n = ft::distance(first, last);
            size_type tail_len = ft::distance(last, end());
            for (size_type i = 0; i < n; ++i) {
                _allocator.destroy(first.base() + i);
            }
            for (size_type i = 0; i < tail_len; ++i) {
                first.base()[i] = last.base()[i];
            }
            _size -= n;
            return first;
        }

        friend bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            if (lhs.size() == rhs.size()){
                return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
            }
            return false;
        };

        friend bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return !(lhs==rhs);
        };

        friend bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                               rhs.begin(), rhs.end());
        };

        friend bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return rhs<lhs;
        };

        friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return !(lhs > rhs);
        };

        friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return !(lhs < rhs);
        };

        void swap(vector& other)
        {
            ft::swap(_allocator, other._allocator);
            ft::swap(_ptr, other._ptr);
            ft::swap(_size, other._size);
            ft::swap(_cap, other._cap);
        }

        friend void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }


	private:
		allocator_type _allocator;
		pointer _ptr;
		size_type _size;
		size_type _cap;

        void check_range(size_type n) const
        {
            if (n >= _size)
                throw ft::out_of_range("index out of range");
        }

        void move_tail(pointer ptr, size_type start_pos, size_type new_elements_size){
            for (size_type i = 0; i < _size-start_pos; i++) {
                ptr[start_pos+new_elements_size+i] = _ptr[start_pos+i];
            }
        }

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