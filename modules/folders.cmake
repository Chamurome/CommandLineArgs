function(basic_project)

    if(NOT ARGV0) 
        set(NAME ${PROJECT_NAME})    
    else()
        set(NAME ${ARGV0})
    endif()

    set(SRC_DIR             ${PROJECT_SOURCE_DIR}/src)
    set(INC_DIR             ${SRC_DIR}/include)
    set(LIB_DIR             ${SRC_DIR}/lib)

    file(GLOB SRC_FILES     ${SRC_DIR}/*.cpp)
    file(GLOB LIB_FILES     ${LIB_DIR}/*.cpp)

    set(SRC_DIR             ${SRC_DIR}                  PARENT_SCOPE)
    set(LIB_DIR             ${LIB_DIR}                  PARENT_SCOPE)
    set(INC_DIR             ${INC_DIR}                  PARENT_SCOPE)
    set(SRC_FILES           ${SRC_FILES}                PARENT_SCOPE)
    set(LIB_FILES           ${LIB_FILES}                PARENT_SCOPE)

    set(${NAME}_SRC_DIR     ${SRC_DIR} CACHE PATH "Directorio fuentes para ${NAME}")
    set(${NAME}_LIB_DIR     ${LIB_DIR} CACHE PATH "Directorio fuentes para ${NAME}")
    set(${NAME}_INC_DIR     ${INC_DIR} CACHE PATH "Directorio fuentes para ${NAME}")
    set(${NAME}_SRC_FILES   ${SRC_FILES} CACHE PATH "Directorio fuentes para ${NAME}")
    set(${NAME}_LIB_FILES   ${LIB_FILES} CACHE PATH "Directorio fuentes para ${NAME}")


endfunction(basic_project)

