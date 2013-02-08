/*!
     @header Yacht Engine
     The Yacht Engine provides a functional interface to a game of Yacht.
     Use the functions declared here to handle gameplay.
     @copyright arg3 software
     @updated 2012-09-09
 */
#ifndef ARG3_YACHT_H
#define ARG3_YACHT_H

#include "player.h"

namespace arg3
{

    namespace yacht
    {


        /*!
         * @class Engine
         * A class that represents a game of Yacht
         */
        class Engine
        {
        public:

            /*!
             * Gets the instance of the yacht engine
             */
            static Engine *instance();

            /*! iterator type for players */
            typedef typename vector<Player>::iterator iterator;
            /*! const iterator type for players */
            typedef typename vector<Player>::const_iterator const_iterator;

            /*!
             * Adds a player with given name to the game
             * @param name
             * the name to give the added player
             */
            void addPlayer(const string &name);

            /*!
             * Removes a player from the game
             * @param index
             * which player to remove
             */
            void removePlayer(size_t index);

            /*!
             * @result the player whose turn it is
             */
            Player *currentPlayer();

            /*!
             * Advances to the next player in the game
             * @result the next player in the game
             */
            Player *nextPlayer();

            /*!
             * @result the number of players in the game
             */
            size_t numberOfPlayers() const;

            // iterator methods
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;

            // const iterator methods
            const const_iterator cbegin() const;
            const const_iterator cend() const;

            // index operators
            Player *operator[] ( size_t );
            const Player *operator[] ( size_t ) const;

            /*!
             * Sets the random engine to use when adding players
             * @param engine
             * The engine to use
             */
            void setRandomEngine(Die::Engine *engine);

        private:
            vector<Player> m_players;

            Die::Engine *m_engine;

            // private singleton constructors
            Engine(Die::Engine * = Die::default_engine);
            Engine(const Engine &);
            Engine &operator=(const Engine &);

            size_t m_currentPlayer;
        };

    }

}
#endif

