//
// Created by Torben Hartmann on 03.05.17.
//

#ifndef EVENTQUEUE_MESSAGEQUEUE_H
#define EVENTQUEUE_MESSAGEQUEUE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Event.h"

class MessageQueue {
public:
    /**
     * Connects to the local Message Queue
     * @param identifier ID of the Handler(1 is Router)
     */
    MessageQueue(int identifier);

    /**
     * Sends an Event to a specified Handler
     * @param event
     * @param recipient Handler ID
     */
    void send(Event event, int recipient);

    /**
     * Sends an event to the Router
     * @param event
     */
    void send(Event event);


    /**
     * halts the current Thread until a Message for the Handler was received
     * @return
     */
    Event receive();

    /**
     * Looks for an Event and returns it, if one was present.
     * @return Pair, where the second member is true when a Message has been received
     */
    std::pair<Event, bool> receiveNoWait();

private:
    int identifier;
    int queueId;
};


#endif //EVENTQUEUE_MESSAGEQUEUE_H
