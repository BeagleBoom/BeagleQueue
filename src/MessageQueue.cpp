//
// Created by Torben Hartmann on 03.05.17.
//

#include <Event.h>
#include "MessageQueue.h"

MessageQueue::MessageQueue(int identifier) : identifier(identifier) {
    this->queueId = msgget((key_t) 1337, 0666 | IPC_CREAT);
}


void MessageQueue::send(Event event, int recipient) {
    net_event pkg = event.generatePackage();
    pkg.recipient = recipient;
    msgsnd(this->queueId, (void *) &pkg, sizeof(pkg), IPC_NOWAIT);
}

void MessageQueue::send(Event event) {
    MessageQueue::send(event, 1);
}

std::pair<Event, bool> MessageQueue::receiveNoWait() {
    net_event data;
    if (msgrcv(this->queueId, (void *) &data, BUFSIZ,
               this->identifier, IPC_NOWAIT) == -1) {
        return std::pair<Event, bool>{Event(-1), false};
    } else {
        return std::pair<Event, bool>{Event(data), true};
    }
}

Event MessageQueue::receive() {
    net_event data;
    if (msgrcv(this->queueId, (void *) &data, BUFSIZ,
               this->identifier, 0) == -1) {
        perror("msgcrv failed with error");
        exit(EXIT_FAILURE);
    }
    return Event(data);
}


