#include "engine.h"

namespace arg3
{

    namespace yacht
    {


        ScoreSheet::ScoreSheet()
        {
            mLowerValues.fill(0);
            mUpperValues.fill(0);
        }

        ScoreSheet::ScoreSheet(const ScoreSheet &other) : mUpperValues(other.mUpperValues), mLowerValues(other.mLowerValues)
        {

        }

        ScoreSheet::~ScoreSheet()
        {

        }

        ScoreSheet &ScoreSheet::operator=(const ScoreSheet &other)
        {

            if (this != &other)
            {
                mUpperValues = other.mUpperValues;
                mLowerValues = other.mLowerValues;
            }
            return *this;
        }

        void ScoreSheet::reset()
        {
            mLowerValues.fill(0);
            mUpperValues.fill(0);
        }

        void ScoreSheet::lowerScore(Type index, ScoreSheet::value_type value)
        {
            mLowerValues[index] = value;
        }

        void ScoreSheet::upperScore(Die::value_type index, ScoreSheet::value_type value)
        {
            mUpperValues[index] = value;
        }

        ScoreSheet::value_type ScoreSheet::lowerScore(Type index) const
        {
            return mLowerValues[index];
        }

        ScoreSheet::value_type ScoreSheet::upperScore(Die::value_type index) const
        {
            return mUpperValues[index];
        }

    }

}
