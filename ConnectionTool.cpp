#include "ConnectionTool.hpp"

pqxx::connection ConnectionTool::connect(
        "user=postgres password=123 host=127.0.0.1 port=5432 dbname=postgres target_session_attrs=read-write");

pqxx::connection &ConnectionTool::GetConnect() {
    return connect;
}