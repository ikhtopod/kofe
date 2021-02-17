#ifndef OBSERVER_H
#define OBSERVER_H

#include <cstdint>
#include <vector>
#include <mutex>


class IInputObserver {
public:
    virtual ~IInputObserver() = default;

public:
    virtual void UpdateInput() = 0;
};


class ObservableInput {
private:
    std::vector<IInputObserver*> m_observers;

    bool m_needClear;
    std::mutex mtx;

public:
    ObservableInput(const ObservableInput&) = delete;
    ObservableInput(ObservableInput&&) noexcept = delete;
    ObservableInput& operator=(const ObservableInput&) = delete;
    ObservableInput& operator=(ObservableInput&&) noexcept = delete;

public:
    ObservableInput();
    virtual ~ObservableInput();

private:
    bool NeedClear() const;
    void SetNeedClear(bool needClear);
    void ClearNonexistent();

public:
    void Attach(IInputObserver* observer);
    void Detach(IInputObserver* observer);
    void Notify();
};

#endif // OBSERVER_H
