cmake_minimum_required(VERSION 3.21)
project(MultiMaid VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set JUCE_DIR or add JUCE as submodule before configuring.
# Example:
#   cmake -B build -DJUCE_DIR=/path/to/JUCE

if(NOT DEFINED JUCE_DIR)
    message(FATAL_ERROR "JUCE_DIR not set. Point it at your JUCE directory.")
endif()

add_subdirectory(${JUCE_DIR} JUCE)

juce_add_plugin(MultiMaid
    COMPANY_NAME "TizWildin Entertainment"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE TwEn
    PLUGIN_CODE MuMd
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "MultiMaid")

juce_generate_juce_header(MultiMaid)

target_sources(MultiMaid PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/Core/Parameters.cpp
)

target_include_directories(MultiMaid PRIVATE
    Source
)

target_compile_definitions(MultiMaid PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(MultiMaid PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra)
