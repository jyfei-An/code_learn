project(copy_construct_func)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

#必须在add_executable之后，否则cmake出错
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES FOLDER "CPlusPlusBase")

