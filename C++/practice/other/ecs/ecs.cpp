#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

// Entity
using Entity = size_t;

// Component
struct Position { float x, y; };
struct Health { int current, max; };
struct Sprite { std::string texture; };
struct Velocity { int dx, dy; };

class World {
        public:
                Entity create_entity() {
                        return m_next_entity++;
                }

                void add_position(Entity e, Position p) {
                        positions.emplace(e, p);
                }

                void add_health(Entity e, Health h) {
                        healths.emplace(e, h);
                }

                void add_sprite(Entity e, Sprite s) {
                        sprites.emplace(e, s);
                }

                void add_velocity(Entity e, Velocity v) {
                        velocities.emplace(e, v);
                }

                std::unordered_map<Entity, Position>& get_positions() {
                        return positions;
                }

                std::unordered_map<Entity, Health>& get_healths() {
                        return healths;
                }

                std::unordered_map<Entity, Sprite>& get_sprites() {
                        return sprites;
                }

                std::unordered_map<Entity, Velocity>& get_velocities() {
                        return velocities;
                }

                const std::unordered_map<Entity, Position>& get_positions() const {
                        return positions;
                }

                const std::unordered_map<Entity, Health>& get_healths() const {
                        return healths;
                }

                const std::unordered_map<Entity, Sprite>& get_sprites() const {
                        return sprites;
                }

                const std::unordered_map<Entity, Velocity>& get_velocities() const {
                        return velocities;
                }

        private:
                std::unordered_map<Entity, Position> positions;
                std::unordered_map<Entity, Health> healths;
                std::unordered_map<Entity, Sprite> sprites;
                std::unordered_map<Entity, Velocity> velocities;
                size_t m_next_entity = 0;
};

// System
class PhysicsSystem {
        public:
                void update(World& world) {
                        for(auto& [entity, position] : world.get_positions()) {
                                if(world.get_velocities().count(entity) == 1) {
                                        position.x += world.get_velocities().at(entity).dx;
                                        position.y += world.get_velocities().at(entity).dy;
                                }
                        }
                }
};

class HealthSystem {
        public:
                void update(World& world) {
                        for(auto& [entity, health] : world.get_healths()) {
                                if(health.current <= 0) std::cout << "Entity " << entity << " died\n";
                        }
                }
};

int main(void) {
        World world;
        Position p(2, 4);
        Position pt(1, 1);
        Health h(20, 100);
        Health ht(0, 200);
        Velocity v(8, 3);

        Entity player = world.create_entity();
        Entity target = world.create_entity();

        world.add_position(player, p);
        world.add_health(player, h);
        world.add_velocity(player, v);
        world.add_position(target, pt);
        world.add_health(target, ht);

        std::unordered_map<Entity, Position> p_before = world.get_positions();
        for(const auto& [entity, position] : p_before) {
                std::cout << position.x << " " << position.y << "\n";
        }

        PhysicsSystem ps;
        HealthSystem hs;
        ps.update(world);
        hs.update(world);

        std::unordered_map<Entity, Position> p_after= world.get_positions();
        for(const auto& [entity, position] : p_after) {
                std::cout << position.x << " " << position.y << "\n";
        }
        return 0;
}
