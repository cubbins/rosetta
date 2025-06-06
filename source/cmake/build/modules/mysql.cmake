OPTION(MYSQL "Build support for MySQL" OFF)

IF (MYSQL)
    # Include the system MySQL library
    ADD_DEFINITIONS(-DUSEMYSQL)
    FIND_PACKAGE(MySQL REQUIRED)
    INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})
    SET(LINK_EXTERNAL_LIBS ${LINK_EXTERNAL_LIBS} ${MYSQL_LIBRARIES})

    # Configure cppdb to use MySQL
    ADD_LIBRARY(cppdb_mysql SHARED ../../external/dbio/cppdb/mysql_backend.cpp)
    TARGET_LINK_LIBRARIES(cppdb_mysql ${MYSQL_LIBRARIES})
    SET_TARGET_PROPERTIES(cppdb_mysql PROPERTIES COMPILE_DEFINITIONS CPPDB_DRIVER_EXPORTS)
    TARGET_LINK_LIBRARIES(cppdb_mysql cppdb)
    SET(LINK_EXTERNAL_LIBS ${LINK_EXTERNAL_LIBS} cppdb_mysql)
ENDIF ()
