#ifndef COLLECTIONOF_H
#define COLLECTIONOF_H

#include <cstddef>
#include <iterator>
#include <vector>
#include <memory>
#include <utility>


template <typename T>
class CollectionOf {
public:
    template <typename U>
    using TypeSPtr = std::shared_ptr<U>;

    template <typename U>
    using Collection = std::vector<U>;

    using size_type = size_t;

private:
    Collection<TypeSPtr<T>> m_objects;

public:
    template<typename U>
    friend void swap(CollectionOf<U>&, CollectionOf<U>&);

public:
    CollectionOf() : m_objects {} {}
    CollectionOf(const CollectionOf& other) : m_objects { other } {}
    CollectionOf(CollectionOf&& other) noexcept : m_objects { other } {}

    CollectionOf& operator=(const CollectionOf& other) {
        if (this != &other) {
            Clear();
            m_objects = other;
        }

        return *this;
    }

    CollectionOf& operator=(CollectionOf&& other) noexcept {
        if (this != &other) {
            Clear();
            m_objects = std::move(other);
        }

        return *this;
    }

    ~CollectionOf() { Clear(); }

public:
    TypeSPtr<T>& operator[](size_type idx) { return m_objects[idx]; }
    const TypeSPtr<T>& operator[](size_type idx) const { return m_objects[idx]; }

    TypeSPtr<T>& At(size_type idx) { return m_objects.at(idx); }
    const TypeSPtr<T>& At(size_type idx) const { return m_objects.at(idx); }

    size_type Size() const { return m_objects.size(); }

    bool IsEmpty() const { return m_objects.empty(); }

    TypeSPtr<T>& Front() { return m_objects.front(); }
    const TypeSPtr<T>& Front() const { return m_objects.front(); }

    TypeSPtr<T>& Back() { return m_objects.back(); }
    const TypeSPtr<T>& Back() const { return m_objects.back(); }

    void Add(const TypeSPtr<T>& object) {
        m_objects.push_back(object);
    }

    void Delete(size_type idx) {
        if (idx >= Size()) return;

        At(idx).reset();
        m_objects.erase(std::next(m_objects.begin(), idx));
    }

    void Clear() {
        for (auto& obj : m_objects) {
            obj.reset();
        }

        m_objects.clear();
    }

    Collection<TypeSPtr<T>>& Get() { return m_objects; }
    const Collection<TypeSPtr<T>>& Get() const { return m_objects; }
};

template<typename U>
void swap(CollectionOf<U>& rhs, CollectionOf<U>& lhs) {
    if (&rhs == &lhs) return;

    using std::swap;
    swap(rhs.Get(), lhs.Get());
}

#endif // COLLECTIONOF_H
