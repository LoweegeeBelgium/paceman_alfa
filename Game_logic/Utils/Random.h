#ifndef PACMANV0_RANDOM_H
#define PACMANV0_RANDOM_H
#include <iostream>
#include <random>
#include <unordered_set>

class Random {
private:
    std::mt19937 m_mt;

    Random() : m_mt(std::random_device{}()) {}

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& instance() {
        static Random instance;
        return instance;
    }

    template <typename Distribution>
    auto get_random() -> decltype(Distribution()(m_mt)) {
        Distribution distribution;
        return distribution(m_mt);
    }

    // Generate a random number within the specified range [min, max]
    template <typename T>
    T get_random_in_range(T min, T max) {
        std::uniform_int_distribution<T> distribution(min, max);
        std::random_device rd;
        std::mt19937 gen(rd());
        return distribution(gen);
    }


    Direction get_random_direction(const std::vector<Direction>& allowedDirections) {
        if (allowedDirections.empty()) {
            return Direction::None;
        }

        //std::uniform_int_distribution<int> distribution(0, static_cast<int>(allowedDirections.size()) - 1);
        int max = allowedDirections.size() - 1;
        int directionIndex = get_random_in_range(0,max);

        // qua è l'errore non ritorna una posizione a caso ma un numero
        //allowedDirections = 3 --- directionIndex = 356400934
        return allowedDirections[directionIndex];
    }


};


#endif //PACMANV0_RANDOM_H
