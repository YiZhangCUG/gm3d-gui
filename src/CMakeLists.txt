aux_source_directory(. DIR_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
# 生成windows和mac的应用程序文件
add_executable(gm3d_gui WIN32 MACOSX_BUNDLE ${DIR_SRC})

include_directories(/usr/local/include)

find_library(HINTS /usr/local/lib)
#find_library(FLTK_LIBRARY fltk HINTS /usr/local/lib)


target_link_libraries(gm3d_gui PUBLIC ${FLTK_LIBRARY})