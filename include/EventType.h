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
    ADC_START,
    ADC_STOP,
    ADC_VALUES,
    MENU_ITEMS,
    ADSR
};
#endif //EVENTQUEUE_ECENTTYPE_H
