#include <chrono>
#include <iostream>

// AoS
struct Particle {
        float x;
        float y;
        float z;
        float mass;
        float padding[4];
};

// SoA
struct Particles {
        std::vector<float> x, y, z;
        std::vector<float> mass;
        std::vector<float> padding[4];
};

void aos_benchmark() {
        std::vector<Particle> particles(1000000);
        auto start = std::chrono::high_resolution_clock::now();
        for(auto& p : particles) {
                p.x += 1.0f;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << duration.count() << "\n";
}

void soa_benchmark() {
        Particles particles;
        particles.x.resize(1000000);
        particles.y.resize(1000000);
        particles.z.resize(1000000);
        particles.mass.resize(1000000);
        auto start = std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < 1000000; ++i) {
                particles.x[i] += 1.0f;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << duration.count() << "\n";
}

int main() {
        aos_benchmark();
        soa_benchmark();
}
