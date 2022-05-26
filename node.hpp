#pragma once


#include "utils.hpp"
#include "pair.hpp"

namespace ft {
    enum node_type {
        red_node,
        nil_node,
        black_node,
    };

    template<class T1, class T2>
    struct node {
        typedef ft::pair<const T1, T2> value_type;
        node* right;
        node* left;
        value_type* data;
        node_type type;
        node* parent;

        node(T1 key, T2 value, node* nil = NULL, node_type type = black_node)
                : type(type), parent(nil), left(nil), right(nil), data(new value_type(key, value)) { }

        node(const node& other) { *this = other; }

        node& operator=(const node& other) {
            if (this == &other)
                return *this;
            type = other.type;
            parent = other.parent;
            left = other.left;
            right = other.right;
            data = new value_type(other.data->first, other.data->second);
            return *this;
        }

        ~node() {
            if (data) {
                delete data;
                data = NULL;
            }
        }
    };
}