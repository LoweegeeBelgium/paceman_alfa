#ifndef PACMANV0_SUBJECT_H
#define PACMANV0_SUBJECT_H
#include "../Observer.h"

class Subject {
public:
    virtual ~Subject(){};
    virtual void Attach(std::shared_ptr<Observer> observer) = 0;
    virtual void Detach(std::shared_ptr<Observer> observer) = 0;
    virtual void Notify() = 0;
};


#endif //PACMANV0_SUBJECT_H
