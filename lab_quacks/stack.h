#ifndef MY_STACK_H
#define MY_STACK_H

// this file is renamed from `stack` to `stack.h` to avoid conflict with the standard library's stack
 
#include <deque>
#include <stack>

namespace cs225 {
    template <class T, class Container = std::deque<T> >
    class stack : public std::stack<T, Container> {
    public:
        static size_t _ctor_count;

        // these are pretty much copied from libc++'s stack header file
        stack() : std::stack<T, Container>() { _ctor_count ++; };
        stack(const stack& q) : std::stack<T, Container>(q) { _ctor_count ++; };
        stack(stack&& q) : std::stack<T, Container>(q) { _ctor_count ++; };

        explicit stack(const Container& c) : std::stack<T, Container>(c) { _ctor_count ++; };
        explicit stack(Container&& c) : std::stack<T, Container>(c) { _ctor_count ++; };

        template <class Alloc> explicit stack(const Alloc& a) : std::stack<T, Container>(a) { _ctor_count ++; }
        template <class Alloc> stack(const Container& c, const Alloc& a) : std::stack<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> stack(Container&& c, const Alloc& a) : std::stack<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> stack(const stack& c, const Alloc& a) : std::stack<T, Container>(c, a) { _ctor_count ++; }
        template <class Alloc> stack(stack&& c, const Alloc& a) : std::stack<T, Container>(c, a) { _ctor_count ++; }

        stack& operator=(const stack& other) = default;
    };

    template <class T, class Container>
    size_t stack<T, Container>::_ctor_count = 0;
};

#undef libcpp_queue
 
#endif
 
/* vim: set ft=cpp: */