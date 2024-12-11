#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"
#include "EventType.h"

class Subject {
public:
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify(EventType eventType, const void* data);

private:
    std::vector<Observer*> observers;
};

#endif 

