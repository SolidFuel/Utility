set (BaseTargetName "${SF_PROJECT}")

add_compile_definitions("$<$<CONFIG:Release>:SF_DEBUG=0>")

include(GetGitRevisionDescription)

get_git_head_revision(GIT_REF GIT_HASH)

string(SUBSTRING "${GIT_HASH}" 0 7 GIT_SHORT_HASH )

message("GIT_HASH = " ${GIT_HASH})
message("GIT_SHORT_HASH = " ${GIT_SHORT_HASH})
message("GIT_REF = " ${GIT_REF})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

string(TOUPPER "${CMAKE_BUILD_TYPE}" upper_build_type)
if(${upper_build_type} STREQUAL "RELEASE")
        set(PLUGIN_PRODUCT_NAME "${SF_PROJECT}")
        set(PLUGIN_PRODUCT_CODE "Sfut" )
else()
        set(PLUGIN_PRODUCT_NAME "${SF_PROJECT}Dev")
        set(PLUGIN_PRODUCT_CODE "SfuD")
endif()

string(TOUPPER "${PLUGIN_PRODUCT_NAME}" PLUGIN_NAME_UPPER)

configure_file(version.hpp.in version.hpp @ONLY)

set(VST3_manifest TRUE)

juce_add_plugin("${BaseTargetName}"
        COMPANY_NAME "SolidFuel"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_MANUFACTURER_CODE "Sdfl"
        PLUGIN_CODE ${PLUGIN_PRODUCT_CODE}
        FORMATS VST3
        VST3_AUTO_MANIFEST ${VST3_manifest}
        PRODUCT_NAME ${PLUGIN_PRODUCT_NAME})

target_sources(${BaseTargetName} PRIVATE
        Debug.hpp
        Glider.hpp
        PluginProcessor.hpp
        Processor/setup.cpp Processor/processing.cpp
        ProcessorParameters.hpp ProcessorParameters.cpp
        PluginEditor.hpp PluginEditor.cpp
        EditorComponent/StereoModeComponent.hpp
        EditorComponent/StereoModeComponent.cpp
        EditorComponent/MuteModeComponent.hpp
        EditorComponent/MuteModeComponent.cpp
        EditorComponent/MainComponent.hpp
        EditorComponent/MainComponent.cpp
        EditorComponent/HeaderComponent.hpp
        EditorComponent/HeaderComponent.cpp
        )


target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PRIVATE
        solidfuel
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)
