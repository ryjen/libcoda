#include "engine.h"
#include <algorithm>
#include <cassert>

namespace arg3
{

    namespace yacht
    {

        Engine::Engine(Die::Engine *engine) : mPlayers(), mEngine(engine), mCurrentPlayer(0)
        {
        }

        Engine::Engine(const Engine &other) : mPlayers(other.mPlayers), mCurrentPlayer(other.mCurrentPlayer)
        {

        }

        Engine &Engine::operator=(const Engine &other)
        {

            if (this != &other)
            {
                mPlayers = other.mPlayers;
                mCurrentPlayer = other.mCurrentPlayer;
            }
            return *this;
        }

        void Engine::addPlayer(const string &name)
        {
            mPlayers.push_back(Player(name, mEngine));
        }

        void Engine::removePlayer(size_t index)
        {

            iterator pos = mPlayers.begin() + index;

            if (pos >= mPlayers.end())
            {
                return;
            }

            mPlayers.erase(pos);

            if (index >= mCurrentPlayer)
                mCurrentPlayer--;
        }

        Engine *Engine::instance()
        {
            static Engine instance;
            return &instance;
        }


        Player *Engine::currentPlayer()
        {
            if (mCurrentPlayer >= mPlayers.size())
                return 0;

            return &(mPlayers.at(mCurrentPlayer));
        }

        size_t Engine::numberOfPlayers() const
        {
            return mPlayers.size();
        }

        Player *Engine::nextPlayer()
        {
            if (mPlayers.size() == 0)
                return 0;

            mCurrentPlayer++;

            if (mCurrentPlayer >= mPlayers.size())
            {
                mCurrentPlayer = 0;
            }

            return &(mPlayers.at(mCurrentPlayer));
        }

        // iterator methods
        Engine::iterator Engine::begin()
        {
            return mPlayers.begin();
        }

        Engine::const_iterator Engine::begin() const
        {
            return mPlayers.begin();
        }

        // const iterator methods
        const Engine::const_iterator Engine::cbegin() const
        {
            return mPlayers.cbegin();
        }

        Engine::iterator Engine::end()
        {
            return mPlayers.end();
        }

        Engine::const_iterator Engine::end() const
        {
            return mPlayers.end();
        }

        const Engine::const_iterator Engine::cend() const
        {
            return mPlayers.cend();
        }

        Player *Engine::operator[] ( size_t index )
        {
            return &(mPlayers.at(index));
        }

        const Player *Engine::operator[] ( size_t index ) const
        {
            return &(mPlayers[index]);
        }

        void Engine::setRandomEngine(Die::Engine *value)
        {
            mEngine = value;
        }

    }

}

