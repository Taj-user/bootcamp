#pragma once
#include "MatchingEngine.hpp"

class Server {
        public:
                Server(MatchingEngine& engine, int port);
                ~Server();
                void run();

        private:
                MatchingEngine& m_engine;
                SOCKET          m_socketfd;
};
