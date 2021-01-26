#ifndef OBSERVER_H
#define OBSERVER_H

#include <cstdint>
#include <vector>
#include <mutex>


class IObserver {
public:
    virtual ~IObserver() = default;

public:
    virtual void Update() = 0;
};


class Observable {
private:
    std::vector<IObserver*> m_observers;

    bool m_needClear;
    std::mutex mtx;

public:
    Observable(const Observable&) = delete;
    Observable(Observable&&) noexcept = delete;
    Observable& operator=(const Observable&) = delete;
    Observable& operator=(Observable&&) noexcept = delete;

public:
    Observable();
    virtual ~Observable();

private:
    bool NeedClear() const;
    void SetNeedClear(bool needClear);
    void ClearNonexistent();

public:
    void Attach(IObserver* observer);
    void Detach(IObserver* observer);
    void Notify();
};

#endif // OBSERVER_H
