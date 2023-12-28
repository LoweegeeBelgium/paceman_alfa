#ifndef PACMANV0_OBSERVER_H
#define PACMANV0_OBSERVER_H
#include "iostream"

class Observer {
public:
    virtual ~Observer() {};
    virtual void Update(const std::string &message_from_subject) = 0;
};


#endif //PACMANV0_OBSERVER_H
