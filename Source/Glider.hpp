/****
 * solidUtility - Versatile VST3 Channel Utility for Digital Audio Workstations 
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/

#pragma once

/**
 * Glider
 * Simple linear ramping class that returns a sequence of numbers that
 * start at @startValue and end at @targetValue.
 * Once @targetValue has been reached, it will continue
 * to give that value.
 * 
*/
template <class FT> class Glider {
public :
    /**
     * Default Constructor
     * 
     * restart() will need to called before using the object.
    */
    Glider() : samples_(0) {}

    /**
     * @param startValue
     * @param targetValue
     * @param samples - how long should it take to move to targetValue
    */
    Glider(FT startValue, FT targetValue, long samples ) {
        restart(startValue, targetValue, samples);

    }

    void restart(FT startValue, FT targetValue, long samples) {
        samples_ = samples;
        delta_ = (targetValue - startValue) / samples;
        latestValue_ = startValue;
    }

    bool in_progress() const {
        return samples_.get() > 0;
    }

    FT nextValue() { 
        latestValue_ = latestValue_.get() + delta_.get() * in_progress();
        samples_ -= in_progress();
        return latestValue_.get();
    }

    /**
     * Stop the sequence. The Glider will continue to return
     * the same value until reset() is called.
    */
    void stop() { samples_ = 0; }

    /**
     * Stop the sequence and set the Glider's value.
     * This will be the value that is given by both nextValue()
     * and currentValue() until reset() is called.
    */
    void forceValue(FT value) {
        stop();
        latestValue_ = value;
    }

    FT currentValue() const { return latestValue_.get(); }

private :
    juce::Atomic<long> samples_;
    juce::Atomic<FT> delta_;
    juce::Atomic<FT> latestValue_;
};


template <class FT> class BooleanGlider {
public:
    BooleanGlider() {
        glider_.forceValue(falseValue_);
    }

    BooleanGlider(FT falseValue, FT trueValue, long samples ) :
            falseValue_{falseValue},
            trueValue_{trueValue},
            steps_{samples}
    {
        glider_.forceValue(falseValue_);
    }

    void forceValue(bool v) {
        currentBoolValue_ = v;
        stop();
    }

    void stop() { 
        glider_.forceValue(currentBoolValue_.get() ? trueValue_ : falseValue_ );
    }

    void go(bool value) {
        if (currentBoolValue_.compareAndSetBool(value, !value)) {
            glider_.restart(glider_.currentValue(),  value ? trueValue_ : falseValue_, steps_.get());
            currentBoolValue_ = value;
        }
    }

    FT nextValue() { return glider_.nextValue(); }
    FT currentValue() const { return glider_.currentValue(); }

    bool in_process() const { return glider_.in_progress(); }


private:
    Glider<FT> glider_;
    FT falseValue_ { 0 };
    FT trueValue_ { 1 };
    juce::Atomic<bool> currentBoolValue_ = false;
    juce::Atomic<long> steps_;


};