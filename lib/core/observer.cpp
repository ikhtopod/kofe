#include "observer.h"

#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <iostream>


Observable::Observable() :
    m_observers {},
    m_needClear { false },
    mtx {}
{
    auto pred = [] (Observable* o) -> void {
        while (o != nullptr) {
            if (o->NeedClear()) {
                o->ClearNonexistent();
                o->SetNeedClear(false);
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    };

    std::thread t = std::thread(pred, this);
    t.detach();
}

Observable::~Observable() {
    m_observers.clear();
}

bool Observable::NeedClear() const {
    return m_needClear;
}

void Observable::SetNeedClear(bool needClear) {
    m_needClear = needClear;
}

void Observable::ClearNonexistent() {
    std::lock_guard<std::mutex> lg { mtx };

    if (m_observers.empty()) return;

    auto lastIt =
            std::remove_if(m_observers.begin(), m_observers.end(),
                           [] (IObserver* observer) { return observer == nullptr; });

    m_observers.erase(lastIt, m_observers.end());
}

void Observable::Attach(IObserver* observer) {
    std::lock_guard<std::mutex> lg { mtx };

    for (IObserver* o : m_observers) {
        if (observer == o) {
            return;
        }
    }

    m_observers.push_back(observer);
}

void Observable::Detach(IObserver* observer) {
    std::lock_guard<std::mutex> lg { mtx };

    auto end = m_observers.end();
    for (auto it = m_observers.begin(); it != end; ++it) {
        if (observer == *it) {
            m_observers.erase(it);
            return;
        }
    }
}

void Observable::Notify() {
    std::lock_guard<std::mutex> lg { mtx };

    for (IObserver* observer : m_observers) {
        if (observer != nullptr) {
            observer->Update();
        } else if (!m_needClear) {
            m_needClear = true;
        }
    }
}
