#ifndef UNTITLED87_CONNECTIONTOOL_HPP
#define UNTITLED87_CONNECTIONTOOL_HPP

#include <pqxx/pqxx>
#include <fstream>
#include <unordered_map>

class ConnectionTool {
private:
    static pqxx::connection connect;
public:
    ConnectionTool() = default;

    static pqxx::connection &GetConnect();
};


#endif
