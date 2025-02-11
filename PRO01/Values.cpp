//
// Created by Jeremi on 30.05.2022.
//

#include "Values.h"

Values::Values(int maxValue) : maxValue(maxValue), currentValue(maxValue) {}

int Values::getMaxValue() const {
    return maxValue;
}

void Values::setMaxValue(int maxValue) {
    Values::maxValue = maxValue;
}

int Values::getCurrentValue() const {
    return currentValue;
}

void Values::setCurrentValue(int currentValue) {
    Values::currentValue = currentValue;
}

void Values::resetValue() {
    currentValue = maxValue;
}

bool Values::isZero() const {
    return currentValue <= 0;
}

void Values::plusCurrent(int val) {
    currentValue += val;
}

Values::Values() {}
