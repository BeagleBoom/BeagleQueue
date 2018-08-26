# ![alt text](docs/beagleQueue_logo.png "BeagleQueue")
BeagleQueue is a wrapper of POSIX MessageQueues used by the BeagleBoom System. The POSIX standard needs each message to have a type in form of a long value. The receive command allows to specify a type, to only get messages of the desired type. Our system uses this value to distinguish the recipient for the events. The payload of an event is the event id, followed by an arbitrary number of additional `paramaters`, encoded as an JSON-Array.
# Usage
## Events
For each event-type, an entry has to be added to the enum found at [include/EventType.h].
An event has to be created with the desired event-type. The event can later be retrieved with the method `getType`. After instantiation, multiple values can be added to the event via the methods `addInt`, `addBool`, `addFloat` and `addString`. Likewise the methods `getInt`, `getBool`, `getFloat` and `getString` can read a value at a specified zero based array position. In order to check the datatype of a paramater the methods `isInt`, `isBool`, `isFloat` and `isString` can be used.

```c++
Event e=Event(EventType::BUTTON_UP); //create an event of type "BUTTON_UP"
e.addInt(5); //add an integer parameter with the value "5"
e.addString("Hi!");
e.isString(1); //=>true
e.isBool(1); //=>false
e.getInt(0); //=>5
e.getType(); //=> BUTTON_UP
```
## Queue
To send and receive the beforementioned events, the MessageQueue class can be used. The Queue has to be initilaized with the desired id on which the queue should listen. Additionally the default recipient of events can be changed (defaults to 1, which is the Menu in the BeagleBoom system).

```c++
MessageQueue queue1 = MessageQueue(5); //Listen as recipient 5 and send events to recipient 1
MessageQueue queue2 = MessageQueue(8, 2); //Listen as recipient 8 and send events to recipient 2
```
To send an event, it can be passed to the `send` method. If the recipient shuld differ to the default one, it can be specified in the second parameter.

```c++
MessageQueue queue = MessageQueue(3);
Event event = Event(EventType::BUTTON_UP); 
queue.send(event); // send to recipient 1
queue.send(event, 5); // send to recipient 5
```

An event can be recieved in a blocking (`receive`) or non-blocking (`receiveNoWait`) way. Both methods return an event. As `receiveNoWait` directly returns without waiting, it is not guaranteed that there was an actual event to return. In this cases, the returned event will have the type `EventType::NONE` to indicate that it is not an actual event.

```c++
MessageQueue queue = MessageQueue(3);
Event e1 = queue.receive(); // Wait until an event is present in the queue

Event e2 = queue.receiveNoWait(); //Return event if one is present
if(e2.getType()==EventType::NONE){
  //There was no event :-(
}else{
  //Event found!
}
```

# Installation
- You need an installed version of PocoLib which includes the JSON namespace.
- Cmake

These commands shall install the BeagleQueue:

```
cmake .
make && make install
```

# License
The content and source code of this project itself is licensed under the [Creative Commons Attribution 4.0 International license](https://creativecommons.org/licenses/by/4.0/).

# About this repository
This repository is part of the [BeagleBoom](https://github.com/beagleboom)-Sampler project developed by the academic working group "[Creative Technologies AG](http://www.creative-technologies.de/)" (ctag) at the [University of Applied Sciences Kiel](https://www.fh-kiel.de/).
