aux_source_directory(. DIR_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(/usr/local/include)

# NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
# the property added to Info.plist
#     <key>CFBundleIconFile</key>
#     <string>logo</string>
set(MACOSX_BUNDLE_ICON_FILE Logo_ZY)

# And this part tells CMake where to find and install the file itself
set(myApp_ICON ${PROJECT_SOURCE_DIR}/assert/logo/Logo_ZY.icns)
# set_source_files_properties would create Resources folder to store icns
# The folder is at same path where Info.plist located
set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

#add_executable(gm3d_gui WIN32 MACOSX_BUNDLE ${DIR_SRC})
add_executable(gm3d MACOSX_BUNDLE ${DIR_SRC} ${myApp_ICON})

# 添加openmp的编译命令 设置编译选项
find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
	message(STATUS "OpenMP Found.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_SHARED_LINKER_FLAGS}")
	#target_link_libraries(gm3d PUBLIC OpenMP::OpenMP_CXX)
endif()

find_library(FLTK_LIBRARY libfltk.a /usr/local/Cellar/fltk/1.3.5/lib)
target_link_libraries(gm3d ${FLTK_LIBRARY} OpenMP::OpenMP_CXX)