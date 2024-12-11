#pragma once
#include <random>
#include <vector>
#include <iostream>

class GenerateRandomPosition
{
public:
    float static generateRandomFloatNumber(float bottomBoundary, float upBoundary) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(bottomBoundary, upBoundary);

        return dis(gen);
    }
};

