#include "ConnectionTool.hpp"

pqxx::connection ConnectionTool::connect(
        "user=postgres password=123 host=0.0.0.0 port=5432 dbname=postgres target_session_attrs=read-write");

pqxx::connection &ConnectionTool::GetConnect() {
    return connect;
}

