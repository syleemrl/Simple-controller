PROJECT(ANIMATION_HW4)

#set(MATHCLASS_INCLUDE_DIR ../libs/mathclass/include/)
#set(MATHCLASS_LIBRARIES_DIR ../libs/mathclass/build/)
set(MATHCLASS_LIBRARIES mathclass)
set(PMQM_LIBRARIES PmQm)

INCLUDE_DIRECTORIES(../libs/mathclass/include/)
LINK_DIRECTORIES(../libs/mathclass/build/)

INCLUDE_DIRECTORIES(../libs/PmQm/include/)
LINK_DIRECTORIES(../libs/PmQm/)

add_compile_options(-std=gnu++11)

ADD_EXECUTABLE(a.out Controller.cpp)
TARGET_LINK_LIBRARIES(a.out ${PMQM_LIBRARIES})
TARGET_LINK_LIBRARIES(a.out ${MATHCLASS_LIBRARIES})
