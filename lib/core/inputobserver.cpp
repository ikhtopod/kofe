#include "inputobserver.h"

#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <iostream>


ObservableInput::ObservableInput() :
    m_observers {},
    m_needClear { false },
    mtx {}
{
    auto pred = [] (ObservableInput* o) -> void {
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

ObservableInput::~ObservableInput() {
    m_observers.clear();
}

bool ObservableInput::NeedClear() const {
    return m_needClear;
}

void ObservableInput::SetNeedClear(bool needClear) {
    m_needClear = needClear;
}

void ObservableInput::ClearNonexistent() {
    std::lock_guard<std::mutex> lg { mtx };

    if (m_observers.empty()) return;

    auto lastIt =
            std::remove_if(m_observers.begin(), m_observers.end(),
                           [] (IInputObserver* observer) { return observer == nullptr; });

    m_observers.erase(lastIt, m_observers.end());
}

void ObservableInput::Attach(IInputObserver* observer) {
    if (observer == nullptr) return;

    std::lock_guard<std::mutex> lg { mtx };

    for (IInputObserver* o : m_observers) {
        if (observer == o) {
            return;
        } else if (o == nullptr && !m_needClear) {
            m_needClear = true;
        }
    }

    m_observers.push_back(observer);
}

void ObservableInput::Detach(IInputObserver* observer) {
    std::lock_guard<std::mutex> lg { mtx };

    if (observer == nullptr) {
        if (!m_needClear) {
            m_needClear = true;
        }
        return;
    }

    auto end = m_observers.end();
    for (auto it = m_observers.begin(); it != end; ++it) {
        if (observer == *it) {
            m_observers.erase(it);
            return;
        } else if (*it == nullptr && !m_needClear) {
            m_needClear = true;
        }
    }
}

void ObservableInput::Notify() {
    std::lock_guard<std::mutex> lg { mtx };

    for (IInputObserver* observer : m_observers) {
        if (observer != nullptr) {
            observer->UpdateInput();
        } else if (!m_needClear) {
            m_needClear = true;
        }
    }
}
