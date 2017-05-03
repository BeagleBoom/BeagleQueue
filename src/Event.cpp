//
// Created by Torben Hartmann on 03.05.17.
//
#include "Event.h"


Event::Event(int event) : eventType(event) {
    this->parsed = true;
    this->data = new Array;
}

void Event::parse() {
    if (this->parsed)return;
    Parser loParser;
    Poco::Dynamic::Var loParsedJson = loParser.parse("[" + this->content + "]");
    Poco::Dynamic::Var loParsedJsonResult = loParser.result();
    this->data = loParsedJsonResult.extract<Array::Ptr>();
    this->parsed = true;
}

Event::Event(net_event event) {
    this->content = event.data;
    this->eventType = event.id;
}

void Event::addInt(int data) {
    this->data->add(data);
}

int Event::getInt(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addFloat(float data) {
    this->data->add(data);
}

float Event::getFloat(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addBool(bool data) {
    this->data->add(data);
}

bool Event::getBool(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

void Event::addString(std::string data) {
    this->data->add(data);
}

std::string Event::getString(unsigned int position) {
    this->parse();
    return this->data->get(position);
}

net_event Event::generatePackage() {
    std::ostringstream oss;
    Poco::JSON::Stringifier::stringify(this->data, oss);
    std::string data = oss.str();
    net_event event{
            1,
            this->eventType,
            data.substr(1, data.size() - 2)
    };
    return event;
}

unsigned int Event::getType() {
    return this->eventType;
}

size_t Event::getPayloadCount() {
    return this->data->size();
}

bool Event::isInt(int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isInteger();
}

bool Event::isFloat(int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isNumeric()
           && !this->data->get(position).isInteger();
}

bool Event::isString(int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isString();
}

bool Event::isBool(int position) {
    return this->getPayloadCount() < position
           && this->data->get(position).isBoolean();
}