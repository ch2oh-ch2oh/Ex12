// Copyright 2021 ch2oh-ch2oh

#include <TimedDoor.h>
#include <thread>  // NOLINT [build/c++11]

bool TimedDoor::isDoorOpened() {
    return opened;
}

void TimedDoor::unlock() {
    opened = true;
    Timer t{};
    t.tregister(iTimeout, adapter);
}

void TimedDoor::lock() {
    opened = false;
}

void TimedDoor::DoorTimeOut() {
    if (opened) {
        throw std::string("close the door!");
    }
}

void TimedDoor::throwState() {
    if (opened) {
        throw std::string("the door is opened!");
    } else {
        throw std::string("the door is closed!");
    }
}

TimedDoor::TimedDoor(int iTimeout) {
    adapter = new DoorTimerAdapter(*this);
    this->iTimeout = iTimeout;
    opened = false;
}

void Timer::sleep(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay * 1000));
    client->Timeout();
}

void Timer::tregister(int delay, TimerClient *timer) {
    client = timer;
    sleep(delay);
}

DoorTimerAdapter::DoorTimerAdapter(TimedDoor &timedDoor) : door(timedDoor) {}

void DoorTimerAdapter::Timeout() {
    door.DoorTimeOut();
}
