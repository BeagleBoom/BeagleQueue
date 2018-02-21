//
// Created by Torben Hartmann on 03.05.17.
//
#include "../include/Event.h"
Event::Event(EventType event) : eventType(event) {
    this->parsed = true;
    this->data = new Array;
}

void Event::parse() {
    if (this->parsed)return;
    Parser loParser;
    Poco::Dynamic::Var loParsedJson = loParser.parse(this->content);
    Poco::Dynamic::Var loParsedJsonResult = loParser.result();
    this->data = loParsedJsonResult.extract<Array::Ptr>();
    this->parsed = true;
}

Event::Event(net_event event) {
    this->content = std::string(event.data);
    this->eventType = static_cast<EventType>(event.id);
    this->event = event;
    this->generated = true;
}

void Event::addInt(int data) {
    this->data->add(data);
    this->generated = true;
}

int Event::getInt(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addFloat(float data) {
    this->data->add(data);
    this->generated = true;
}

float Event::getFloat(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addBool(bool data) {
    this->data->add(data);
    this->generated = true;
}

bool Event::getBool(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addString(std::string data) {
    this->data->add(data);
    this->generated = true;
}

std::string Event::getString(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

net_event Event::generatePackage() {
    if(!generated){
        std::ostringstream oss;
        Poco::JSON::Stringifier::stringify(this->data, oss);
        std::string data = oss.str();
        net_event event;

        event.id = static_cast<unsigned int>(this->eventType);
        event.recipient = 1;
        strncpy(event.data, data.c_str(), sizeof(event.data));
        this->event=event;
        this->generated=true;
    }
    return this->event;
}

EventType Event::getType() {
    return this->eventType;
}

size_t Event::getPayloadCount() {
    return this->data->size();
}

bool Event::isInt(unsigned int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isInteger();
}

bool Event::isFloat(unsigned int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isNumeric()
           && !this->data->get(position).isInteger();
}

bool Event::isString(unsigned int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isString();
}

bool Event::isBool(unsigned int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isBoolean();
}
