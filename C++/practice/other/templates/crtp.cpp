#include <algorithm>
#include <cctype>
#include <iostream>

template<typename Derived, typename OutputPolicy>
class Printable {
        OutputPolicy policy;
        public:
                void print() {
                        policy.output(static_cast<Derived*>(this)->toString());
                }
};

class ConsoleOutput {
        public:
                void output(const std::string& msg) {
                        std::cout << msg << "\n";
                }
};

class UpperCaseOutput {
        public:
                void output(std::string msg) {
                        std::transform(msg.begin(), msg.end(), msg.begin(), [](unsigned char c) { return std::toupper(c); });
                        std::cout << msg << "\n";
                }
};

class Dog : public Printable<Dog, UpperCaseOutput> {
        public:
                std::string toString() {
                        return "I am a Dog\n";
                }
};

class Cat : public Printable<Cat, ConsoleOutput> {
        public:
                std::string toString() {
                        return "I am a Cat\n";
                }
};

int main(void) {
        Dog dog;
        dog.print();

        Cat cat;
        cat.print();

        return 0;
}
