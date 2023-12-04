# basic cmake file stuff
cmake_minimum_required(VERSION 3.16)
project(AwesomeChess LANGUAGES CXX)

# set output for the exe and turn off shared libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/executable)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# add libraries
add_subdirectory(src/rendering)

# include sfml packages
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# add exe
add_executable(AwesomeChess src/main.cpp)
# link packages from sfml library and other libraries (add extra here)
target_link_libraries(AwesomeChess PUBLIC rendering) # for our libraries
target_link_libraries(AwesomeChess PRIVATE sfml-graphics) # for sfml libraries
target_link_libraries(rendering PRIVATE sfml-graphics) # linking sfml to our libraries for use
# include directories for h files for libraries
target_include_directories(AwesomeChess PUBLIC
	"${PROJECT_BINARY_DIR}/src/rendering"
)
# set how to compile packages
target_compile_features(AwesomeChess PRIVATE cxx_std_17)

# little thing for windows that adds the sfml .dll file to the compiling process
if(WIN32)
    add_custom_command(
        TARGET AwesomeChess
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:AwesomeChess>
        VERBATIM)
endif()

# installs packages (Installs the binary files corresponding to targets built inside the project)
install(TARGETS AwesomeChess)
