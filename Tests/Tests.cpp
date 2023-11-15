/****
 * Chantool - Versatile VST3 Channel Utility for Digital Audio Workstations 
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <juce_core/juce_core.h>

template <typename T>
bool checkMin(T first, T second)
{
    return juce::exactlyEqual(juce::jmin(first, second), std::min(first, second));
}

template <typename T>
bool checkMax(T first, T second)
{
    return juce::exactlyEqual(juce::jmax(first, second), std::max(first, second));
}

TEST_CASE("Test that juce::jmin works")
{
    REQUIRE(checkMin(5, 7));
    REQUIRE(checkMin(12, 3));
    REQUIRE(checkMin(5.31, 5.42));
}

TEST_CASE("Test that juce::jmax works")
{
    REQUIRE(checkMax(5, 7));
    REQUIRE(checkMax(12, 3));
    REQUIRE(checkMax(5.31, 5.42));
}