# CMakeList.txt: проект CMake для RTSPClient; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (RTSPClient "src/RTSPClient.cpp" "src/include/TCPConnection.h" "src/TCPConnection.cpp" "src/include/SDP.h" "src/SDP.cpp" "src/include/UDPConnection.h" "src/UDPConnection.cpp" "src/include/Connection.h" "src/Connection.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RTSPClient PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
