CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

PROJECT(myserver) #项目名称

AUX_SOURCE_DIRECTORY(src SRC_LIST)
add_subdirectory(src/base)
add_subdirectory(src/net)

add_compile_options(-std=c++11 -Wall -Wno-unused-but-set-variable -g ) 


include_directories (include)
include_directories (include/libmevent/base)
include_directories (include/libmevent/net)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(TESTFUNC_LIB pthread HINTS /usr/lib)

add_executable (cli ${SRC_LIST})

target_link_libraries (cli PRIVATE  "/usr/lib/x86_64-linux-gnu/libcurl.so" "/usr/lib/x86_64-linux-gnu/libmysqlclient.so" 
${TESTFUNC_LIB} libmevent_base libmevent_net )




