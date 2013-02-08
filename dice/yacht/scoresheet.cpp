#include "engine.h"

namespace arg3
{

    namespace yacht
    {


        ScoreSheet::ScoreSheet()
        {
            m_lowerValues.fill(0);
            m_upperValues.fill(0);
        }

        ScoreSheet::ScoreSheet(const ScoreSheet &other) : m_upperValues(other.m_upperValues), m_lowerValues(other.m_lowerValues)
        {

        }

        ScoreSheet::~ScoreSheet()
        {

        }

        ScoreSheet &ScoreSheet::operator=(const ScoreSheet &other)
        {

            if (this != &other)
            {
                m_upperValues = other.m_upperValues;
                m_lowerValues = other.m_lowerValues;
            }
            return *this;
        }

        void ScoreSheet::reset()
        {
            m_lowerValues.fill(0);
            m_upperValues.fill(0);
        }

        void ScoreSheet::lowerScore(Type index, ScoreSheet::value_type value)
        {
            m_lowerValues[index] = value;
        }

        void ScoreSheet::upperScore(Die::value_type index, ScoreSheet::value_type value)
        {
            m_upperValues[index] = value;
        }

        ScoreSheet::value_type ScoreSheet::lowerScore(Type index) const
        {
            return m_lowerValues[index];
        }

        ScoreSheet::value_type ScoreSheet::upperScore(Die::value_type index) const
        {
            return m_upperValues[index];
        }

    }

}
