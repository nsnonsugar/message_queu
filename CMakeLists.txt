cmake_minimum_required(VERSION 2.8)

project( sample_queue )

if(WIN32)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")
elseif(UNIX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif(WIN32)

#ディレクトリ設定
set( include_dir ${CMAKE_CURRENT_SOURCE_DIR}/inc )
set( source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src )

#インクルードパス設定
include_directories(
    ${include_dir}
)

set( headers
    ${include_dir}/Message.h
    ${include_dir}/MessageQueue.h
    ${include_dir}/Mutex.h
    ${include_dir}/threads.h
)

set( sources
    ${source_dir}/main.cpp
    ${source_dir}/Message.cpp
    ${source_dir}/MessageQueue.cpp
    ${source_dir}/Mutex.cpp
    ${source_dir}/threads.cpp
)

add_executable( sample_queue
    ${headers}
    ${sources}
)

if(NOT WIN32)
target_link_libraries( sample_queue
    pthread
)
endif(NOT WIN32)

