//
// Created by Torben Hartmann on 30.08.17.
//

#ifndef EVENTQUEUE_ROUTER_H
#define EVENTQUEUE_ROUTER_H


#include "EventType.h"
#include "MessageQueue.h"
#include <memory>

class Router {
public:
    Router(int id);

    Router();

    void loop();

    void addRoute(EventType type, int target);

private:
    void init();

    std::multimap<EventType, int> map;
    int id;
    std::shared_ptr<MessageQueue> queue;
};


#endif //EVENTQUEUE_ROUTER_H
