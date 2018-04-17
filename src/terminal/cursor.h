//
// Created by Ryan Jennings on 2018-03-26.
//

#ifndef CODA_CURSOR_H
#define CODA_CURSOR_H

#include <mutex>

namespace coda
{
    namespace terminal
    {

        // cursor related
        namespace cursor
        {
            using Mutex = std::recursive_mutex;

            /**
             * saves a cursor position and attributes
             */
            constexpr static const char *const SAVE = "\0337";
            /**
             * restores a saved cursor position and attributes
             */
            constexpr static const char *const RESTORE = "\0338";

            /**
             * erases from cursor to the start of the line
             */
            constexpr static const char *const ERASE_BACK = "\033[1K";

            /**
             * asks the terminal to report the cursor position for reading
             */
            constexpr static const char *const REPORT = "\033[6n";

            /**
             * cursor methods have their own mutex
             * @return the single instance mutex
             */
            Mutex &get_mutex();

            /**
             * sets the cursor position
             * @param rows
             * @param cols
             * @return PREP_SUCCESS or PREP_FAILURE
             */
            bool set(int rows, int cols);

            /**
             * gets the cursor position
             * NOTE: may be blocking
             * @param rows
             * @param cols
             * @return PREP_SUCCESS or PREP_FAILURE
             */
            bool get(int *rows, int *cols);

            /**
             * RAII class to save and restore a cursor position
             */
            class Savepoint
            {
            public:
                /**
                 * @param mutex the mutex to lock
                 */
                explicit Savepoint(Mutex &mutex) noexcept;
                ~Savepoint() = default;
                Savepoint(const Savepoint &) = delete;
                Savepoint(Savepoint &&) = delete;
                Savepoint &operator=(const Savepoint &) = delete;
                Savepoint &operator=(Savepoint &&) = delete;

            private:
                class Restore
                {
                public:
                    Restore() = default;
                    ~Restore();
                    Restore(const Restore &) = delete;
                    Restore(Restore &&) = delete;
                    Restore &operator=(const Restore &) = delete;
                    Restore &operator=(Restore &&) = delete;
                };
                // deconstruct restore first
                Restore restore_;
                std::lock_guard<Mutex> guard_;
            };
        }

    }
}
#endif
