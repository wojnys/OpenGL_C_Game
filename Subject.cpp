#include "Subject.h"

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(EventType eventType, const void* data) {
    for (Observer* observer : observers) {
        observer->update(eventType, data);
    }
}
