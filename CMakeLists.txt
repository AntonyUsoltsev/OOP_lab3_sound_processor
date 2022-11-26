cmake_minimum_required(VERSION 3.20)
project(lab3_sound_processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3_sound_processor main.cpp Config/Config.cpp Config/Config.h Converter/Converter.cpp Converter/Converter.h WAV/WAV.cpp WAV/WAV.h Mixer/Mixer.cpp Mixer/Mixer.h Muter/Muter.cpp Muter/Muter.h)

set(Boost_INCLUDE_DIR C:/MinGW/include)
set(Boost_LIBRARY_DIR C:/MinGW/lib)
find_package(Boost COMPONENTS program_options REQUIRED)
target_include_directories(lab3_sound_processor PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(lab3_sound_processor ${Boost_LIBRARIES})