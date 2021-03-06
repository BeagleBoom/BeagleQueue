#ifndef EVENTQUEUE_EVENT_H
#define EVENTQUEUE_EVENT_H

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "EventType.h"

using namespace Poco::JSON;

/**
 * Struct for Event Serialization
 */
typedef struct {
    long int recipient;
    unsigned int id;
    char data[512];
} net_event;

class Event {
public:
    /**
     * Generates a new Event with a corresponding identifier
     * @param event
     */
    Event(EventType event);

    /**
     * Parses an incoming Event
     * @param event
     */
    Event(net_event event);

    /**
     * "serializes" the event for sending to the queue
     * @return
     */
    net_event generatePackage();

    /**
     * adds an Integer to the Payload
     * @param data
     */
    void addInt(int data);

    /**
     * returns an Integer at a specified position in the Payload
     * @param data
     */
    int getInt(unsigned int position);

    /**
     * adds a Float to the Payload
     * @param data
     */
    void addFloat(float data);

    /**
     * returns a Float at a specified position in the Payload
     * @param data
     */
    float getFloat(unsigned int position);

    /**
     * adds a Boolean to the Payload
     * @param data
     */
    void addBool(bool data);
    /**
     * returns a Boolean at a specified position in the Payload
     * @param data
     */
    bool getBool(unsigned int position);

    /**
     * adds a String to the Payload
     * @param data
     */
    void addString(std::string data);

    /**
     * returns a String at a specified position in the Payload
     * @param data
     */
    std::string getString(unsigned int position);

    /**
     * Returns the Number of Parameters present in the Event
     * @return
     */
    size_t getPayloadCount();

    /**
     * Returns true if the Payload has an Element at the given position which is of type Integer
     * @param position
     * @return
     */
    bool isInt(unsigned int position);

    /**
     * Returns true if the Payload has an Element at the given position which is of type Float
     * @param position
     * @return
     */
    bool isFloat(unsigned int position);

    /**
     * Returns true if the Payload has an Element at the given position which is of type String
     * @param position
     * @return
     */
    bool isString(unsigned int position);

    /**
     * Returns true if the Payload has an Element at the given position which is of type Boolean
     * @param position
     * @return
     */
    bool isBool(unsigned int position);

    /**
     * Returns the Event Identifier
     * @return
     */
    EventType getType();

    virtual ~Event();

private:
    void parse();

    EventType eventType;
    std::string content;
    bool parsed = false;
    Array::Ptr data;
    bool generated = false;
    net_event event;
};


#endif //EVENTQUEUE_EVENT_H
