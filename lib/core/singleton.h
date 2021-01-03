#ifndef SINGLETON_H
#define SINGLETON_H


template <typename T>
class Singleton {
public:
    static T& Get() {
        static T instance {};
        return instance;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) noexcept = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) noexcept = delete;
};

#endif // SINGLETON_H
