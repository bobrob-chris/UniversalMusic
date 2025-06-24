cmake_minimum_required(VERSION 3.10)
project(unimusic LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

enable_testing()

add_executable(unimusic unimusic.cpp player.cpp spotifyinterface.cpp youtubeinterface.cpp utils.cpp testing.cpp)

include_directories("C:/raylib/raylib/src") #TODO - I shouldn't have to include these to get the project to work (I don't thing if just installed cmake as a library)
link_directories("C:/raylib/raylib/src") # - so I should probably fix that at some point, but right now I'm tired of debugging this and I'm happy I can get the project to compile with my friend's additions.




if(WIN32)
  target_link_libraries(unimusic raylib gdi32 winmm wsock32 ws2_32) #things after wsock32 are mine

endif()