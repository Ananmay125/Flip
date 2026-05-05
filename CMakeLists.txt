# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Flip")

list(APPEND CMAKE_PREFIX_PATH
    "${CMAKE_SOURCE_DIR}/libs/SDL3-devel-3.4.6-VC"
    "${CMAKE_SOURCE_DIR}/libs/SDL3-image-devel-vc"
    "${CMAKE_SOURCE_DIR}/libs/SDL3_mixer-devel-3.2.0-VC"
    "${CMAKE_SOURCE_DIR}/libs/SDL3_ttf-devel-3.2.0-VC" 
)

find_package(SDL3       REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_mixer REQUIRED CONFIG)

find_package(SDL3_ttf   REQUIRED CONFIG) 

add_executable(Flip "src/Flip.cpp"  "src/input.cpp"  "src/renderer.cpp" "src/renderer.h" "src/Interface.h" "src/Interface.cpp" "src/Secret.cpp" "src/audioPlayer.cpp" "src/audioPlayer.h" )

set_property(TARGET Flip PROPERTY CXX_STANDARD 20)

target_link_libraries(Flip PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)

# dont mind ts
add_custom_command(TARGET Flip POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:Flip>/resources"
)

install(TARGETS Flip DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION "resources")

if(WIN32)
    add_custom_command(TARGET Flip POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Flip>
            $<TARGET_FILE_DIR:Flip>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying SDL3 DLLs -> build dir"
    )
endif()