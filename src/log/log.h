#ifndef CODA_LOG_H
#define CODA_LOG_H

#include <ostream>

namespace coda {

    namespace log {

        namespace level {
            typedef enum {
                /*! logging is disabled */
                        None = 0,
                /*! only error messages will be logged */
                        Error = 1,
                /*! warnings and errors will be logged */
                        Warn = 2,
                /*! info, warning, and error messages will be logged */
                        Info = 3,
                /*! debug, info, warning and error messages will be logged */
                        Debug = 4,
                /*! trace, debug, info, warning and error messages will be logged */
                        Trace = 5
            } Type;

            void set(const std::string &name);

            void set(Type type);

            bool valid(Type value);

            std::string format(level::Type value);
        }

        namespace output {

            void enable_color(bool value);

            extern std::ostream &stream;

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
            template<class A0, class... Args>
            std::ostream &print(std::ostream &os, const A0 &a0, const Args &... args) {
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
            template<class... Args>
            std::ostream &print(std::ostream &os, const Args &... args) {
                // pass the first argument to the printer
                return print(os, args...);
            }
        }

        using namespace level;
        using namespace output;

        template<class... Args>
        void info(const Args &... args) {
            if (!valid(Info)) {
                return;
            }
            print(stream, format(Info), args..., "\n") << std::flush;
        }

        template<class... Args>
        void debug(const Args &... args) {
            if (!valid(Debug)) {
                return;
            }
            print(stream, format(Debug), args..., "\n") << std::flush;
        }

        template<class... Args>
        void error(const Args &... args) {
            if (!valid(Error)) {
                return;
            }
            print(stream, format(Error), args..., "\n") << std::flush;
        }

        template<class... Args>
        void warn(const Args &... args) {
            if (!valid(Warn)) {
                return;
            }
            print(stream, format(Warn), args..., "\n") << std::flush;
        }

        template<class... Args>
        void trace(const Args &... args) {
            if (!valid(Trace)) {
                return;
            }
            print(stream, format(Trace), args..., "\n") << std::flush;
        }

        template<class... Args>
        void perror(const Args &... args) {
            error(std::to_string(errno), ": ", strerror(errno), " - ", args...);
        }
    }
}

#endif
