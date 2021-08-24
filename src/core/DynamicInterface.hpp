#pragma once

#include <string>
#include <map>

/**
 * 实现动态接口，就是对于一个对象来说，可以动态的添加这个对象实现的接口。
 */

/**

 */
class Interface {
public:
    Interface() {
    }
    virtual ~Interface() {
    }
};

class DynamicInterface;

class Interfaces {
public:
    typedef std::map<std::string, Interface *> MapInterface;

    Interfaces(DynamicInterface *dynamic) {
        _dynamic = dynamic;
    }

    bool has_impl(std::string id) {
        if (_map_interfaces.find(id) != _map_interfaces.end()) {
            return true;
        } else {
            return false;
        }
    }

    bool add_impl(std::string id, Interface *interface) {
        _map_interfaces[id] = interface;
        return true;
    }

    Interface *get_impl(std::string id) {
        return _map_interfaces[id];
    }

protected:
    MapInterface _map_interfaces;

    DynamicInterface *_dynamic;

private:
};

class DynamicInterface {
public:
    DynamicInterface() {
        _interfaces = new Interfaces(this);
    }
    virtual ~DynamicInterface() {
    }

    Interfaces *interfaces() {
        return this->_interfaces;
    }

protected:
    Interfaces *_interfaces;

private:
};
