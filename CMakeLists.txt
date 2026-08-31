cmake_minimum_required (VERSION 3.10)

project ("Snake" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source file directories...
set(SRC_FILES "${CMAKE_SOURCE_DIR}/Src")

# Gather Source and Header Files...
file(GLOB_RECURSE PROJ_HEADERS "${SRC_FILES}/*.h")
file(GLOB_RECURSE PROJ_SRC "${SRC_FILES}/*.cpp")

# Define the executable...
add_executable (Snake
	${PROJ_HEADERS}
	${PROJ_SRC}
)

# Set Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Snake)

# Filters...
source_group("Header Files" FILES ${PROJ_HEADERS})
source_group("Source Files" FILES ${PROJ_SRC})

# Third Party...
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/ThirdParty/SFML")

# Include Directories
target_include_directories(Snake PRIVATE "${SFML_ROOT}/include")

# Library Directories...
target_link_directories(Snake PRIVATE "${SFML_ROOT}/lib")

# Link Libraries...
target_link_libraries(Snake PRIVATE
	sfml-graphics-d.lib
	sfml-window-d.lib
	sfml-system-d.lib
	sfml-network-d.lib
	sfml-audio-d.lib
)

# Build
add_custom_command(TARGET Snake POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${SFML_ROOT}/bin"
	"$<TARGET_FILE_DIR:Snake>"
)