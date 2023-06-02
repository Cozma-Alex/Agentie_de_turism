#pragma once
#include "vector"
#include "algorithm"

using std::vector;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Wishlist_obs {
    std::vector<Observer *> observers;
public:
    void register_observer(Observer *observer) {
        this->observers.push_back(observer);
    }

    void unregister_observer(Observer *observer) {
        this->observers.erase(
                std::find(this->observers.begin(),
                          this->observers.end(),
                          observer));
    }

    void notify() {
        for (auto &obs: this->observers) {
            obs->update();
        }
    }

    virtual ~Wishlist_obs()=default;
};