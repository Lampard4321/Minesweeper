# src/CMakeLists.txt

SET(SOURCES
  main.cc
)

SET(MINESWEEPER_SOURCES
  field.cc
  minesweeper.cc
  utils.cc
)

add_library(Minesweeperlib STATIC ${MINESWEEPER_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Minesweeperlib)
add_dependencies(${PROJECT_NAME} Minesweeperlib)

install(TARGETS ${PROJECT_NAME} DESTINATION ./bin)
