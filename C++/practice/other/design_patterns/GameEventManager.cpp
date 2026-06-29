#include <iostream>
#include <memory>
#include <vector>

class GameEventManager {
        public:
                static GameEventManager& getInstance() {
                        static GameEventManager instance;
                        return instance;
                }

                void log(const std::string& msg) {
                        std::cout << msg << "\n";
                }

                GameEventManager(const GameEventManager& other) = delete;
                GameEventManager& operator=(const GameEventManager& other) = delete;
                GameEventManager(GameEventManager&& other) = delete;
                GameEventManager& operator=(GameEventManager&& other) = delete;

        private:
                GameEventManager() {}
};

class Observer {
        public:
                virtual void onNotify(const std::string& event) = 0;
                virtual ~Observer() = default;
};

class Subject {
        public:
                void addObserver(Observer* observer) {
                        m_observers.push_back(observer);
                }

                void notify(const std::string& event) {
                        GameEventManager::getInstance().log(event);
                        for(auto* observer : m_observers) {
                                observer->onNotify(event);
                        }
                }

        private:
                std::vector<Observer*> m_observers;
};

class ScoreSystem : public Observer {
        public:
                void onNotify(const std::string& event) override {
                        std::cout << "Score updated with event: " + event << "\n";
                }
};

class SoundSystem : public Observer {
        public:
                void onNotify(const std::string& event) override {
                        std::cout << "Sound updated with event: " + event << "\n";
                }
};

class Enemy {
        public:
                virtual void attack() = 0;
                virtual ~Enemy() = default;
};

class Goblin : public Enemy {
        public:
                void attack() override {
                        std::cout << "Goblin attacks\n";
                }
};

class Dragon : public Enemy {
        public:
                void attack() override {
                        std::cout << "Dragon breathes fire\n";
                }
};

class EnemyFactory {
        public:
                static std::unique_ptr<Enemy> create(const std::string& type) {
                        if(type == "Goblin") return std::make_unique<Goblin>();
                        if(type == "Dragon") return std::make_unique<Dragon>();
                        throw std::invalid_argument("Unknown enemy type: " + type);
                }
};

class Player {
        public:
                void move(int dx, int dy) {
                        x += dx;
                        y += dy;
                }

        private:
                int x, y;
};

class Command {
        public:
                virtual void execute() = 0;
                virtual void undo() = 0;
                virtual ~Command() = default;
};

class MoveCommand : public Command {
        public:
                MoveCommand(Player& player, int dx, int dy)
                        : m_player(player)
                        , m_dx(dx)
                        , m_dy(dy)
                {}

                void execute() override {
                        m_player.move(m_dx, m_dy);
                }

                void undo() override {
                        m_player.move(-m_dx, -m_dy);
                }

        private:
                Player& m_player;
                int m_dx, m_dy;
};
