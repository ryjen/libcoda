//
// Created by Ryan Jennings on 2018-03-26.
//

#include "cursor.h"
#include "output.h"
#include <cstdio>
#include <set>
#include <string>
#include <termios.h>
#include <unistd.h>

namespace coda {
  namespace terminal {
    namespace internal {

      // reads a cursor report response from the terminal
      static ssize_t read_cursor(int fd, std::string &buf) {
        static const std::set<char> Valids = {'\033', '[', ';', 'R'};
        ssize_t numRead; /* # of bytes fetched by last read() */
        size_t totRead;  /* Total bytes read so far */
        char ch;

        totRead = 0;

        buf.clear();

        for (;;) {
          numRead = read(fd, &ch, 1);

          if (numRead == -1) {
            if (errno == EINTR) /* Interrupted --> restart read() */
              continue;
            else
              return -1; /* Some other error */

          } else if (numRead == 0) { /* EOF */
            if (totRead == 0)        /* No bytes read; return 0 */
              return 0;
            else /* Some bytes read; add '\0' */
              break;

          } else { /* 'numRead' must be 1 if we get here */
            totRead++;

            if (ch != '\n' && ch != '\r' &&
                (Valids.find(ch) != Valids.end() || std::isdigit(ch))) {
              buf += ch;
            }

            if (ch == 'R')
              break;
          }
        }

        return totRead;
      }

      /**
       * RAII class to temporarily disable echo mode so we can read a response
       * from the terminal
       */
      class TTYRead {
        public:
        TTYRead() : state_(), saved_() {
          // get state
          tcgetattr(STDIN_FILENO, &state_);
          // copy state
          saved_ = state_;

          // turn off canonical mode and echo
          state_.c_lflag &= ~(ICANON | ECHO);
          // minimum of number input read.
          state_.c_cc[VMIN] = 1;
          // timeout
          state_.c_cc[VTIME] = 2;

          // set the new terminal attributes.
          tcsetattr(STDIN_FILENO, TCSANOW, &state_);
        }

        ~TTYRead() {
          // reset state
          tcsetattr(STDIN_FILENO, TCSANOW, &saved_);
        }

        /**
         * @param row the cursor row to find
         * @param col the cursor col to find
         */
        bool read_cursor(int *row, int *col) const {
          std::string line;

          // request the cursor position
          print(cursor::REPORT) << std::flush;

          // read the response
          if (internal::read_cursor(STDIN_FILENO, line) < 0) {
            return false;
          }

          // parse the response
          if (sscanf(line.c_str(), "\033[%d;%dR", row, col) != 2) {
            return false;
          }

          return true;
        }

        private:
        struct termios state_, saved_;
      };
    } // namespace internal
    namespace cursor {
      Mutex &get_mutex() {
        static Mutex m;
        return m;
      }

      bool set(int rows, int cols) {
        if (rows > 0 && cols > 0) {
          print("\033[", rows, ";", cols, "H") << std::flush;
          return true;
        }
        return false;
      }

      bool get(int *row, int *col) {
        // assert we can read
        internal::TTYRead ttyRead;

        return ttyRead.read_cursor(row, col);
      }

      Savepoint::Savepoint(Mutex &mutex) noexcept : restore_(), guard_(mutex) {
        // save the cursor position
        print(SAVE) << std::flush;
      }

      Savepoint::Restore::~Restore() {
        // restore the cursor position
        print(RESTORE) << std::flush;
      }
    } // namespace cursor
  }   // namespace terminal
} // namespace coda