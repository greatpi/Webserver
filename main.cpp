#include "config.h"
#include "webserver.h"

int main(int argc, char* argv[])
{
    std::string user = "root";
    std::string passwd = "root";
    std::string database = "yourdb";

    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    server.init(config.PORT, user, passwd, database, config.LOGWrite,
                config.OPT_LINGER, config.TRIGMode, config.sql_num, config.thread_num,
                config.close_log, config.actor_model);
    

    server.log_write();

    server.sql_pool();

    server.thread_pool();

    server.trig_mode();

    server.eventListen();
    std::cout << "Server is running" << std::endl;
    server.eventLoop();

    return 0;
}