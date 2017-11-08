cmake_minimum_required(VERSION 3.10)

PROJECT(ANIMATION_HW4)

#set(MATHCLASS_INCLUDE_DIR ../libs/mathclass/include/)
#set(MATHCLASS_LIBRARIES_DIR ../libs/mathclass/build/)
set(MATHCLASS_LIBRARIES mathclass)
set(PMQM_LIBRARIES PmQm)
FIND_PACKAGE(Boost COMPONENTS filesystem REQUIRED)

INCLUDE_DIRECTORIES(../libs/mathclass/include/)
LINK_DIRECTORIES(../libs/mathclass/build/)

INCLUDE_DIRECTORIES(../libs/PmQm/include/)
LINK_DIRECTORIES(../libs/PmQm/)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_compile_options(-std=gnu++11)

ADD_EXECUTABLE(a.out Controller.cpp RawDatabase.cpp RawDatabase.h)
TARGET_LINK_LIBRARIES(a.out ${PMQM_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
TARGET_LINK_LIBRARIES(a.out ${MATHCLASS_LIBRARIES})
