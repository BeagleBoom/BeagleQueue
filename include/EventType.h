//
// Created by Torben Hartmann on 30.08.17.
//

#ifndef EVENTQUEUE_ECENTTYPE_H
#define EVENTQUEUE_ECENTTYPE_H

enum class EventType {
    NONE,
    BUTTON_DOWN,
    BUTTON_UP,
    ROTARY_LEFT,
    ROTARY_RIGHT,
    ADC_VALUES
};
#endif //EVENTQUEUE_ECENTTYPE_H