cmake_minimum_required(VERSION 3.20)
project(lab3_sound_processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3_sound_processor main.cpp Config/Config.cpp Config/Config.h
        Converter/Converter.h WAV/WAV.cpp WAV/WAV.h
        Converter/Mixer/Mixer.cpp Converter/Mixer/Mixer.h Converter/Muter/Muter.cpp
        Converter/Muter/Muter.h Factory/Factory.h Sound_processor/Sound_processor.cpp
        Sound_processor/Sound_processor.h Exceptions/Exceptions.h
        Prog_args/Prog_args.cpp Prog_args/Prog_args.h Converter/Slow/Slow.h Manual/Manual.cpp
        Manual/Manual.h Converter/Slow/Slow.cpp)

set(Boost_INCLUDE_DIR C:/MinGW/include)
set(Boost_LIBRARY_DIR C:/MinGW/lib)
find_package(Boost COMPONENTS program_options REQUIRED)
target_include_directories(lab3_sound_processor PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(lab3_sound_processor ${Boost_LIBRARIES})