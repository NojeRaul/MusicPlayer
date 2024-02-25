#pragma once
#include <vector>
#include <random>

std::vector<int> getRandomInts(int min, int max, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a sequence from min to max
    std::vector<int> sequence(max - min + 1);
    for (int i = 0; i < sequence.size(); ++i) {
        sequence[i] = min + i;
    }

    // Shuffle the sequence
    std::shuffle(sequence.begin(), sequence.end(), gen);

    // Take the first n elements
    std::vector<int> randomInts(sequence.begin(), sequence.begin() + n);

    return randomInts;
}
