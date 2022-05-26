#pragma once

#include "tree.hpp"
#include "Iterators/map_iterator.hpp"
#include "Iterators/reverse_iterator.hpp"
#include "pair.hpp"

namespace ft {
    template<class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key, T> >
    >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef ft::map_iterator<Key, T, value_type*> iterator;
        typedef ft::map_iterator<Key, T, const value_type*> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map;
        protected:
            key_compare _comp;
            value_compare(key_compare comp) :_comp(comp) { }

        public:
            bool operator()(const value_type& x, const value_type& y) const {
                return _comp(x.first, y.first);
            }
        };

    private:
        tree<Key, T, Compare, Allocator> _tree;
        key_compare _key_compare;
        allocator_type _allocator;

    public:
        explicit map(
                const Compare& comp = key_compare(),
                const Allocator& alloc = allocator_type()
        ): _tree(), _key_compare(comp), _allocator(alloc) { }

        template<class InputIterator>
        map(
                InputIterator first,
                InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()
        ) :_tree(), _key_compare(comp), _allocator(alloc) { insert(first, last); }

        map(const map& other) { *this = other; }

        ~map() { }

        map& operator=(const map& other)
        {
			_allocator = other._allocator;
            _key_compare = other._key_compare;
            _tree = other._tree;
            return *this;
        }

        allocator_type get_allocator() const { return _allocator; }

        mapped_type& at(const Key& key) {
            iterator it = find(key);
            if (it==end()) {
                throw std::out_of_range("map");
            }
            return it->second;
        }

        const mapped_type& at(const Key& key) const {
            iterator it = find(key);
            if (it==end()) {
                throw std::out_of_range("map");
            }
            return it->second;
        }

        mapped_type& operator[](const key_type& key) {
            ft::pair<iterator, bool> res = insert(ft::pair<Key, mapped_type>(key, _tree.find(key)->data->second));
            return res.first->second;
        }

        reverse_iterator rbegin() { return reverse_iterator(_tree.end()); }
        const_reverse_iterator rbegin() const { return reverse_iterator(_tree.end()); }

        reverse_iterator rend() { return reverse_iterator(_tree.begin()); }
        const_reverse_iterator rend() const { return reverse_iterator(_tree.begin()); }

		iterator begin() { return iterator(_tree.begin()); }
		const_iterator begin() const { return const_iterator(_tree.begin()); }

		iterator end() { return iterator(_tree.end()); }
		const_iterator end() const { return const_iterator(_tree.end()); }

        size_type max_size() const { return _tree.max_size(); }
        size_type size() const { return _tree.size(); }
        bool empty() const { return _tree.size() == 0; }

        void clear() { _tree.clear(); }

        ft::pair<iterator, bool> insert(const value_type& val) { return _tree.insert(val); }

        iterator insert(iterator hint, const value_type& val) {
            (void) hint;
            return _tree.insert(val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for (; first!=last; ++first) {
                _tree.insert(value_type(first->first, first->second));
            }
        }

        void erase(iterator pos) { _tree.erase(pos->first); }

        void erase(iterator first, iterator last) {
            for (; first!=last;) {
                Key key = first->first;
                ++first;
                _tree.erase(key);
            }
        }

        size_type erase(const key_type& key) { return _tree.erase(key) ? 1 : 0; }

        void swap(map& other) {
            _tree.swap(other._tree);
            std::swap(_allocator, other._allocator);
            std::swap(_key_compare, other._key_compare);
        }

        size_type count(const key_type& key) const { return (_tree.find(key) != _tree.end()) ? 1 : 0; }

        iterator find(const key_type& key) { return iterator(_tree.find(key)); }

        const_iterator find(const key_type& key) const { return const_iterator(_tree.find(key)); }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) {
            return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const key_type& key) { return iterator(_tree.lower_bound(key)); }

        const_iterator lower_bound(const key_type& key) const { return const_iterator(_tree.lower_bound(key)); }

        iterator upper_bound(const key_type& key) { return iterator(_tree.upper_bound(key)); }

        const_iterator upper_bound(const key_type& key) const { return const_iterator(_tree.upper_bound(key)); }

        key_compare key_comp() const { return _key_compare; }

        value_compare value_comp() const { return value_compare(Compare()); }

		friend bool operator>(
				const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs
		) { return rhs<lhs; }

		friend bool operator<(
				const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs
		) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

        friend bool operator==(
                const map<Key, T, Compare, Allocator>& lhs,
                const map<Key, T, Compare, Allocator>& rhs
        ) {
            return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        friend bool operator!=(
                const map<Key, T, Compare, Allocator>& lhs,
                const map<Key, T, Compare, Allocator>& rhs
        ) { return !(lhs==rhs); }

		friend bool operator>=(
				const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs
		) { return !(lhs<rhs); }

        friend bool operator<=(
                const map<Key, T, Compare, Allocator>& lhs,
                const map<Key, T, Compare, Allocator>& rhs
        ) { return !(rhs<lhs); }
    };
}