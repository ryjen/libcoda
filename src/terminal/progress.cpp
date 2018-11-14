//
// Created by Ryan Jennings on 2018-03-26.
//

#include "progress.h"
#include "color.h"
#include "cursor.h"
#include <functional>

namespace coda {
  namespace terminal {
    Progress::Progress() noexcept : alive_(false), row_(0), bg_() {
      init();
      // start updating
      bg_ = std::thread(std::bind(&Progress::run, this));
    }

    Progress::~Progress() {
      alive_ = false;

      if (bg_.joinable()) {
        bg_.join();
      }

      reset();
    }

    std::size_t Progress::key() const {
      return std::hash<const Progress *>()(this);
    }

    void Progress::reset() {
      // use a save point to reset the current cursor position
      cursor::Savepoint savepoint(cursor::get_mutex());

      // restore the cursor to this progress indicator
      cursor::set(row_, 2);

      // and erase the line
      print(cursor::ERASE_BACK) << std::flush;
    }

    void Progress::init() {
      int col = 0;

      std::lock_guard<cursor::Mutex> lock(cursor::get_mutex());

      // get the current row
      cursor::get(&row_, &col);
    }

    void Progress::run() {
      using namespace std::chrono_literals;

      alive_ = true;

      while (alive_) {
        update();
        std::this_thread::sleep_for(100ms);
      }
    }

    void Progress::update() {
      static unsigned frame = 0;
      constexpr static const char *FRAMES[] = {"◜", "◠", "◝", "◞", "◡", "◟"};
      constexpr static size_t FRAME_SIZE = (sizeof(FRAMES) / sizeof(FRAMES[0]));

      ++frame;
      frame %= FRAME_SIZE;

      // use a save point to reset the current cursor position
      cursor::Savepoint savepoint(cursor::get_mutex());

      // set the cursor to the saved position
      cursor::set(row_, 1);

      // send the frame and move the cursor back one character to print again
      print(color::colorize({color::attr::BOLD, color::fg::GREEN},
                            FRAMES[frame], true))
          << std::flush;
    }
  } // namespace terminal
} // namespace coda