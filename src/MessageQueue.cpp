//
// Created by Torben Hartmann on 03.05.17.
//

#include "../include/MessageQueue.h"
#include <iostream>
#include <errno.h>
#include <Event.h>

MessageQueue::MessageQueue(int identifier) : identifier(identifier) {
    this->queueId = msgget((key_t) 1337, 0666 | IPC_CREAT);
    struct msqid_ds ds = {0};
    msgctl(this->queueId, IPC_STAT, &ds);
    ds.msg_qbytes = 1024 * 1024;
    msgctl(this->queueId, IPC_SET, &ds);
}


void MessageQueue::send(Event event, int recipient) {
    net_event pkg = event.generatePackage();
    pkg.recipient = recipient;
    std::cout << msgsnd(this->queueId, (void *) &pkg, sizeof(pkg.id) + sizeof(pkg.data), IPC_NOWAIT) << std::endl;
    std::cout << strerror(errno) << std::endl;
}

void MessageQueue::send(Event event) {
    MessageQueue::send(event, 1);
}

Event MessageQueue::receiveNoWait() {
    net_event data;
    if (msgrcv(this->queueId, (void *) &data, BUFSIZ,
               this->identifier, IPC_NOWAIT) == -1) {
        return Event(EventType::NONE);
    } else {
        return Event(data);
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


