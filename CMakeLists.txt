cmake_minimum_required(VERSION 3.10)
project(unimusic LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(unimusic unimusic.cpp song.cpp network.cpp commandhp.cpp spotifyinterface.cpp youtubeinterface.cpp exec.cpp)

if(WIN32)
  target_link_libraries(unimusic wsock32 ws2_32)
endif()