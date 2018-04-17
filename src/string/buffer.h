#ifndef CODA_STRING_BUFFERED_IO_H_
#define CODA_STRING_BUFFERED_IO_H_

#include <sstream>
#include <string>
#include <vector>

namespace coda
{
    typedef std::vector<unsigned char> buffered_data;

    static const buffered_data NEWLINE = {'\r', '\n'};

    class buffer
    {
       private:
        std::ostringstream buf_;

       public:
        buffer();
        template <typename T>
        buffer(const T &value)
        {
            buf_ << value;
        }
        buffer(const buffer &other);
        buffer(buffer &&other) = delete;
        buffer &operator=(const buffer &other);
        buffer &operator=(buffer &&other) = delete;

        buffer &writeln();

        template <typename T>
        buffer &writeln(const T &value)
        {
            buf_ << value << std::endl;
            return *this;
        }

        template <typename T>
        buffer &write(const T &value)
        {
            buf_ << value;
            return *this;
        }

        template <typename T>
        buffer &operator<<(const T &value)
        {
            buf_ << value;
            return *this;
        }

        operator std::string() const;

        std::string to_string() const;

        bool empty() const;

        buffer &remove(size_t start, size_t end = std::string::npos);

        size_t length() const;
    };

    class buffered_reader
    {
       public:
        /*!
         * Reads a line from the read buffer
         */
        std::string readln();

        /*!
         * @returns the read buffer
         */
        const buffered_data &input() const;

        buffered_data &input();

        /*!
         * @returns true if the read buffer contains data
         */
        bool has_input() const;

        /*!
         * Reads data into the read buffer
         * @returns true if no errors occured
         */
        virtual bool read_to_buffer() = 0;

       private:
        buffered_data buffer_;
    };

    class buffered_writer
    {
       public:
        /*!
         * Appends some data to the write buffer with a new line.
         */
        buffered_writer &writeln(const std::string &value);

        buffered_writer &writeln(const buffered_data &value);

        /*!
        * Appends a new line to the write buffer
        */
        buffered_writer &writeln();

        /*!
         * Appends some data to the write buffer.
         */
        buffered_writer &write(const std::string &value);

        buffered_writer &write(const buffered_data &value);

        /*!
         * @returns the write buffer
        */
        const buffered_data &output() const;

        buffered_data &output();

        /*!
         * @returns true if the write buffer contains data
         */
        bool has_output() const;

        /*!
         * Will write the buffer
         * @returns true if no errors occured
         */
        virtual bool write_from_buffer() = 0;

       private:
        buffered_data buffer_;
    };
}

#endif
