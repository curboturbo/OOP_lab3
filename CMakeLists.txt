cmake_minimum_required(VERSION 3.10)
project(DecimalTests)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем тестирование
enable_testing()

# Находим GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем директорию с исходниками
include_directories(${CMAKE_SOURCE_DIR}/src)

# Тестовый исполняемый файл
add_executable(test_lab3 tests/test_lab3.cpp src/fig.cpp)

# Линкуем GTest и pthreads
target_link_libraries(test_lab3 GTest::GTest GTest::Main Threads::Threads)

# Регистрируем тест
add_test(NAME FigureTest COMMAND test_lab3)
