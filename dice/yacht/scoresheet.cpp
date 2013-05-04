#include "engine.h"

namespace arg3
{

    namespace yacht
    {


        ScoreSheet::ScoreSheet()
        {
            lowerValues_.fill(0);
            upperValues_.fill(0);
        }

        ScoreSheet::ScoreSheet(const ScoreSheet &other) : upperValues_(other.upperValues_), lowerValues_(other.lowerValues_)
        {

        }

        ScoreSheet::ScoreSheet(ScoreSheet &&other) : upperValues_(std::move(other.upperValues_)), lowerValues_(std::move(other.lowerValues_))
        {

        }

        ScoreSheet::~ScoreSheet()
        {

        }

        ScoreSheet &ScoreSheet::operator=(const ScoreSheet &other)
        {
            if (this != &other)
            {
                upperValues_ = other.upperValues_;
                lowerValues_ = other.lowerValues_;
            }
            return *this;
        }

        ScoreSheet &ScoreSheet::operator=(ScoreSheet &&other)
        {
            if (this != &other)
            {
                upperValues_ = std::move(other.upperValues_);
                lowerValues_ = std::move(other.lowerValues_);
            }
            return *this;
        }

        void ScoreSheet::reset()
        {
            lowerValues_.fill(0);
            upperValues_.fill(0);
        }

        void ScoreSheet::lowerScore(Type index, ScoreSheet::value_type value)
        {
            lowerValues_[index] = value;
        }

        void ScoreSheet::upperScore(Die::value_type index, ScoreSheet::value_type value)
        {
            upperValues_[index] = value;
        }

        ScoreSheet::value_type ScoreSheet::lowerScore(Type index) const
        {
            return lowerValues_[index];
        }

        ScoreSheet::value_type ScoreSheet::upperScore(Die::value_type index) const
        {
            return upperValues_[index];
        }

    }

}
