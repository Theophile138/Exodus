#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float constrainFloat(float x, float a, float b) {
    return std::max(a, std::min(b, x));
}

float simulatePression(int step) {
    return (std::sin(step / 10.0) + 1.0) / 2.0 * 4095.0;
}

int main() {
    for (int step = 0; step < 100; ++step) {
        float pression = simulatePression(step);
        float angle = mapFloat(pression, 0, 4095, 0, 180);
        angle = constrainFloat(angle, 0, 180);

        std::cout << "Pression = " << pression << " convertie donne Angle = " << angle << " Degres" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}