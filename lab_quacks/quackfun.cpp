/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

// remove these when copying to the svn directory
// {
#include "stack.h" // renamed from `stack`
#include "queue.h" // renamed from `queue`
using cs225::queue;
using cs225::stack;
// }

#include <utility>

namespace QuackFun
{
    /**
     * Sums items in a stack.
     * @param s A stack holding values to sum.
     * @return The sum of all the elements in the stack, leaving the original
     *  stack in the same state (unchanged).
     *
     * @note You may modify the stack as long as you restore it to its original
     *  values.
     * @note You may use only two local variables of type T in your function.
     *  Note that this function is templatized on the stack's type, so stacks of
     *  objects overloading the + operator can be summed.
     * @note We are using the Standard Template Library (STL) stack in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint Think recursively!
     */
    template<typename T>
    T sum(stack<T> &s)
    {
        if (s.empty()) return T();

        auto last = s.top();
        s.pop();

        auto result = last + sum(s);

        s.push(last);

        return result;
    }

    /**
     * Reverses even sized blocks of items in the queue. Blocks start at size
     * one and increase for each subsequent block.
     * @param q A queue of items to be scrambled
     *
     * @note Any "leftover" numbers should be handled as if their block was
     *  complete.
     * @note We are using the Standard Template Library (STL) queue in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint You'll want to make a local stack variable.
     */
    template<typename T>
    void scramble(queue<T> &q)
    {
        if (q.empty()) return;

        stack<T> s{};
        queue<T> q2{};

        int block = 1;

        while (!q.empty())
        {
            // for each block
            if (block % 2 == 0) // even, reverse
            {
                for (int i = 0; i < block && !q.empty(); i++)
                {
                    s.push(q.front());
                    q.pop();
                }

                while (!s.empty())
                {
                    q2.push(s.top());
                    s.pop();
                }
            }
            else { // odd, keep
                for (int i = 0; i < block && !q.empty(); i++)
                {
                    q2.push(q.front());
                    q.pop();
                }
            }
            block++;
        }
        q = std::move(q2);
    }

    /**
     * @return true if the parameter stack and queue contain only elements of
     *  exactly the same values in exactly the same order; false, otherwise.
     *
     * @note You may assume the stack and queue contain the same number of items!
     * @note There are restrictions for writing this function.
     * - Your function may not use any loops
     * - In your function you may only declare ONE local boolean variable to use in
     *   your return statement, and you may only declare TWO local variables of
     *   parametrized type T to use however you wish.
     * - No other local variables can be used.
     * - After execution of verifySame, the stack and queue must be unchanged. Be
     *   sure to comment your code VERY well.
     */
    template<typename T>
    bool verifySame(stack<T> &s, queue<T> &q)
    {
        // 1. pop all but the last elements from the stack by recursing to the base case
        // 2. compare the last element with the front of the queue
        // 3. restore one element of the stack, move the front of the queue to the back
        // 4. repeat until the recursion ends

        // base case
        if (s.empty()) return true;

        // tear down the stack
        const T &temp = s.top();
        s.pop();

        // recurse
        bool retval = verifySame<T>(s, q);

        // compare the top with the front
        retval &= temp == q.front();

        // cycle the queue
        q.push(q.front());
        q.pop();
        // restore the stack
        s.push(temp);

        return retval;
    }
}
