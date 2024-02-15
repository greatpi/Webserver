cmake_minimum_required(VERSION 3.10)

project(WebServer)

set(SRC 
    main.cpp
    config.cpp
    webserver.cpp
    ./CGImysql/sql_connection_pool.cpp
    ./http/http_conn.cpp
    ./log/log.cpp
    ./timer/lst_timer.cpp
    )

add_executable(target ${SRC})

target_link_libraries(target -lmysqlclient)