#include "ConnectionTool.hpp"

pqxx::connection ConnectionTool::connect(
        "user=postgres password=123 host=89.204.138.144 port=3389 dbname=postgres target_session_attrs=read-write");

pqxx::connection &ConnectionTool::GetConnect() {
    return connect;
}