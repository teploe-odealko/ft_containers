#pragma once
#include "utils.hpp"


namespace ft {
    template<class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;

        pair() : first(), second() {}

        template<class U1, class U2>
        pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        pair(const first_type &k, const second_type &v) : first(k), second(v) {};

        pair &operator=(const pair &other) {
            if (this == &other)
                return *this;
            first = other.first;
            second = other.second;
            return *this;
        }

        void swap(pair &p) {
            ft::swap(first, p.first);
            ft::swap(second, p.second);
        }
    };

    template<class T1, class T2>
    inline bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) {
        return x.first == y.first && x.second == y.second;
    }

    template<class T1, class T2>
    inline bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
        return !(x == y);
    }

    template<class T1, class T2>
    inline bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y) {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }

    template<class T1, class T2>
    inline bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y) { return y < x; }

    template<class T1, class T2>
    inline bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y) { return !(x < y); }

    template<class T1, class T2>
    inline bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y) { return !(y < x); }

    template<class T1, class T2>
    inline pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }
}