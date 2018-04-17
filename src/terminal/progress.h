//
// Created by Ryan Jennings on 2018-03-26.
//

#ifndef CODA_PROGRESS_H
#define CODA_PROGRESS_H

#include <cstdlib>
#include <thread>
#include "output.h"

namespace coda
{
    namespace terminal
    {

        /**
         * RAII class to display a progress indicator, will disappear on scope loss
         */
        class Progress
        {
        public:
            Progress() noexcept;
            ~Progress();
            Progress(const Progress &) = delete;
            Progress(Progress &&) = delete;
            Progress &operator=(const Progress &) = delete;
            Progress &operator=(Progress &&) = delete;

        private:
            /**
             * a hash code for this object
             * @return a unique code for this object
             */
            std::size_t key() const;

            /**
             * updates the progress indicator
             */
            void update();

            /**
             * resets and removes the progress indicator
             */
            void reset();

            /**
             * runs the animation
             */
            void run();

            /**
             * initializes the progress state
             */
            void init();

            bool alive_;
            int row_;
            std::thread bg_;
            output::Mutex mutex_;
        };
    }
}
#endif
