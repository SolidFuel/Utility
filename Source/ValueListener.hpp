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

#include <juce_gui_basics/juce_gui_basics.h>

#include "functional"

#include "Debug.hpp"

class ValueListener : public juce::Value::Listener {
    void valueChanged(juce::Value &v) { 
        //DBGLOG("ValueListener cb triggered")
        if (onChange) {
            //DBGLOG("ValueListener calling onChange")
            onChange(v);
        } 
    }

public :
    std::function<void(juce::Value &)> onChange;
};
