#include "engine.h"
#include <algorithm>
#include <cassert>

namespace arg3
{

    namespace yacht
    {

        Engine::Engine(Die::Engine *engine) : players_(), engine_(engine), currentPlayer_(0)
        {
        }

        Engine::Engine(const Engine &other) : players_(other.players_), engine_(other.engine_), currentPlayer_(other.currentPlayer_)
        {

        }

        Engine::Engine(Engine &&other) : players_(std::move(other.players_)), engine_(std::move(other.engine_)), currentPlayer_(other.currentPlayer_)
        {

        }

        Engine &Engine::operator=(const Engine &other)
        {

            if (this != &other)
            {
                players_ = other.players_;
                engine_ = other.engine_;
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }


        Engine &Engine::operator=(Engine &&other)
        {

            if (this != &other)
            {
                players_ = std::move(other.players_);
                engine_ = std::move(other.engine_);
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }

        void Engine::addPlayer(const string &name)
        {
            players_.push_back(Player(name, engine_));
        }

        void Engine::removePlayer(size_t index)
        {

            iterator pos = players_.begin() + index;

            if (pos >= players_.end())
            {
                return;
            }

            players_.erase(pos);

            if (index >= currentPlayer_)
                currentPlayer_--;
        }

        Engine *Engine::instance()
        {
            static Engine instance;
            return &instance;
        }


        Player *Engine::currentPlayer()
        {
            if (currentPlayer_ >= players_.size())
                return 0;

            return &(players_.at(currentPlayer_));
        }

        size_t Engine::numberOfPlayers() const
        {
            return players_.size();
        }

        Player *Engine::nextPlayer()
        {
            if (players_.size() == 0)
                return 0;

            currentPlayer_++;

            if (currentPlayer_ >= players_.size())
            {
                currentPlayer_ = 0;
            }

            return &(players_.at(currentPlayer_));
        }

        // iterator methods
        Engine::iterator Engine::begin()
        {
            return players_.begin();
        }

        Engine::const_iterator Engine::begin() const
        {
            return players_.begin();
        }

        // const iterator methods
        const Engine::const_iterator Engine::cbegin() const
        {
            return players_.cbegin();
        }

        Engine::iterator Engine::end()
        {
            return players_.end();
        }

        Engine::const_iterator Engine::end() const
        {
            return players_.end();
        }

        const Engine::const_iterator Engine::cend() const
        {
            return players_.cend();
        }

        Player *Engine::operator[] ( size_t index )
        {
            return &(players_.at(index));
        }

        const Player *Engine::operator[] ( size_t index ) const
        {
            return &(players_[index]);
        }

        void Engine::setRandomEngine(Die::Engine *value)
        {
            engine_ = value;
        }

    }

}

