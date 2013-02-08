#include "engine.h"
#include <algorithm>
#include <cassert>

namespace arg3
{

    namespace yacht
    {

        Engine::Engine(Die::Engine *engine) : m_players(), m_engine(engine), m_currentPlayer(0)
        {
        }

        Engine::Engine(const Engine &other) : m_players(other.m_players), m_currentPlayer(other.m_currentPlayer)
        {

        }

        Engine &Engine::operator=(const Engine &other)
        {

            if (this != &other)
            {
                m_players = other.m_players;
                m_currentPlayer = other.m_currentPlayer;
            }
            return *this;
        }

        void Engine::addPlayer(const string &name)
        {
            m_players.push_back(Player(name, m_engine));
        }

        void Engine::removePlayer(size_t index)
        {

            iterator pos = m_players.begin() + index;

            if (pos >= m_players.end())
            {
                return;
            }

            m_players.erase(pos);

            if (index >= m_currentPlayer)
                m_currentPlayer--;
        }

        Engine *Engine::instance()
        {
            static Engine instance;
            return &instance;
        }


        Player *Engine::currentPlayer()
        {
            if (m_currentPlayer >= m_players.size())
                return 0;

            return &(m_players.at(m_currentPlayer));
        }

        size_t Engine::numberOfPlayers() const
        {
            return m_players.size();
        }

        Player *Engine::nextPlayer()
        {
            if (m_players.size() == 0)
                return 0;

            m_currentPlayer++;

            if (m_currentPlayer >= m_players.size())
            {
                m_currentPlayer = 0;
            }

            return &(m_players.at(m_currentPlayer));
        }

        // iterator methods
        Engine::iterator Engine::begin()
        {
            return m_players.begin();
        }

        Engine::const_iterator Engine::begin() const
        {
            return m_players.begin();
        }

        // const iterator methods
        const Engine::const_iterator Engine::cbegin() const
        {
            return m_players.cbegin();
        }

        Engine::iterator Engine::end()
        {
            return m_players.end();
        }

        Engine::const_iterator Engine::end() const
        {
            return m_players.end();
        }

        const Engine::const_iterator Engine::cend() const
        {
            return m_players.cend();
        }

        Player *Engine::operator[] ( size_t index )
        {
            return &(m_players.at(index));
        }

        const Player *Engine::operator[] ( size_t index ) const
        {
            return &(m_players[index]);
        }

        void Engine::setRandomEngine(Die::Engine *value)
        {
            m_engine = value;
        }

    }

}

