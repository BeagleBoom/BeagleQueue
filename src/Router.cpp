//
// Created by Torben Hartmann on 30.08.17.
//
#include "../include/Router.h"

Router::Router(int id) {
    this->id = id;
    this->init();
}

Router::Router() {
    this->id = 1;
    this->init();
}

void Router::init() {
    this->queue = std::make_shared<MessageQueue>(this->id);
}

void Router::loop() {
    auto event = queue->receive();
    std::pair<std::multimap<EventType, int>::iterator, std::multimap<EventType, int>::iterator> ret;
    ret = map.equal_range(event.getType());
    for (std::multimap<EventType, int>::iterator it = ret.first; it != ret.second; ++it) {
        queue->send(event, it->second);
    }
}

void Router::addRoute(EventType type, int target) {
    if (target == this->id)return;
    map.insert({type, target});
}


