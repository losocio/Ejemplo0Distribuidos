 
cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(client LANGUAGES CXX)
add_executable(client utils.h utils.cpp client.cpp)
target_link_libraries(client pthread)

project(server LANGUAGES CXX)
add_executable(server utils.h utils.cpp server.cpp)
target_link_libraries(server pthread)

project(clienteObjetos LANGUAGES CXX)
add_executable(clienteObjetos utils.h utils.cpp clienteObjetos.cpp persona_stub.h operaciones.h)
target_link_libraries(clienteObjetos pthread)

project(serverObjetos LANGUAGES CXX)
add_executable(serverObjetos utils.h utils.cpp serverObjetos.cpp persona.h persona_imp.h operaciones.h)
target_link_libraries(serverObjetos pthread)
