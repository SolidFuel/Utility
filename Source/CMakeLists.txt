
set (BaseTargetName ChanTool)

add_compile_definitions("$<$<CONFIG:Release>:STARP_DEBUG=0>")

include(GetGitRevisionDescription)

get_git_head_revision(GIT_REF GIT_HASH)

string(SUBSTRING "${GIT_HASH}" 0 7 GIT_SHORT_HASH )

message("GIT_HASH = " ${GIT_HASH})
message("GIT_SHORT_HASH = " ${GIT_SHORT_HASH})
message("GIT_REF = " ${GIT_REF})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

configure_file(version.hpp.in version.hpp @ONLY)

string(TOUPPER "${CMAKE_BUILD_TYPE}" chantool_build_type)
if(${chantool_build_type} STREQUAL "RELEASE")
        set(ChanTool_PRODUCT_NAME "ChanTool")
        set(ChanTool_PLUGIN_CODE "Chnt" )
else()
        set(ChanTool_PRODUCT_NAME "ChanToolDev")
        set(ChanTool_PLUGIN_CODE "ChnD")
endif()


juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "SolidFuel"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_MANUFACTURER_CODE "Sdfl"
        PLUGIN_CODE ${ChanTool_PLUGIN_CODE}
        FORMATS VST3
        PRODUCT_NAME ${ChanTool_PRODUCT_NAME})

target_sources(${BaseTargetName} PRIVATE
        ChanTool.hpp
        Glider.hpp
        ChanToolProcessor.hpp
        Processor/setup.cpp Processor/processing.cpp
        ProcessorParameters.hpp ProcessorParameters.cpp
        ChanToolEditor.hpp ChanToolEditor.cpp
        MainComponent.hpp MainComponent.cpp
        )


target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PRIVATE
        shared_plugin_helpers
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)
