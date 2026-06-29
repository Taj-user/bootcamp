#include "GameEventManager.cpp"

int main(void) {
        GameEventManager& gem = GameEventManager::getInstance();
        gem.log("GameEventManager created\n");

        Subject sub;
        ScoreSystem score;
        SoundSystem sound;
        sub.addObserver(&score);
        sub.addObserver(&sound);
        sub.notify("bread");
        std::unique_ptr<Enemy> dragon = EnemyFactory::create("Dragon");
        dragon->attack();
        Player player;
        MoveCommand command(player, 2, 4);
        command.execute();
        command.undo();
}
