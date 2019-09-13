aux_source_directory(. DIR_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
# 生成windows和mac的应用程序文件

include_directories(/usr/local/include)

#add_executable(gm3d_gui WIN32 MACOSX_BUNDLE ${DIR_SRC})
add_executable(gm3d_gui ${DIR_SRC})

find_library(FLTK_LIBRARY libfltk.a /usr/local/Cellar/fltk/1.3.5/lib)

target_link_libraries(gm3d_gui ${FLTK_LIBRARY})