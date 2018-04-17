//
// Created by Ryan Jennings on 2018-03-26.
//

#ifndef CODA_OUTPUT_H
#define CODA_OUTPUT_H

#include <mutex>
#include <iostream>

namespace coda
{
    namespace terminal
    {

        // output related functions
        namespace output
        {
            // define a mutex type
            using Mutex = std::recursive_mutex;

            /**
             * utility method for variadic print
             * @param os the output stream
             * @return the output stream
             */
            std::ostream &print(std::ostream &os);

            /**
             * variadic print
             * @tparam A0 the type of argument
             * @tparam Args the remaining arguments
             * @param os the output stream
             * @param a0 the argument
             * @param args the remaining arguments
             * @return
             */
            template <class A0, class... Args>
            std::ostream &print(std::ostream &os, const A0 &a0, const Args &... args)
            {
                // print the argument
                os << a0;
                // print the remaining arguments
                return print(os, args...);
            }

            /**
             * variadic print
             * @tparam Args the arguments
             * @param os the output stream
             * @param args the arguments
             * @return the output stream
             */
            template <class... Args>
            std::ostream &print(std::ostream &os, const Args &... args)
            {
                // pass the first argument to the printer
                return print(os, args...);
            }

            /**
             * output methods have their own mutex
             * @return a single instance mutex
             */
            Mutex &get_mutex();
        }

        /**
         * variadic print
         * @tparam Args the type of arguments
         * @param args the arguments
         * @return the output stream
         */
        template <class... Args>
        std::ostream &print(const Args &... args)
        {
            std::lock_guard<output::Mutex> _(output::get_mutex());
            return output::print(std::cout, args...);
        }

    }
}
#endif
