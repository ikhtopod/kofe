#ifndef COLLECTIONOF_H
#define COLLECTIONOF_H

#include <cstddef>
#include <iterator>
#include <vector>
#include <memory>
#include <utility>
#include <type_traits>


template <typename T, bool IsShared = true>
class CollectionOf {
public:
    using ClearT =
        std::remove_pointer_t<
            std::remove_reference_t<
                std::remove_cv_t<T>>>;

    template <typename U>
    using TypePtr = std::conditional_t<IsShared, std::shared_ptr<U>, U*>;

    template <typename U>
    using Collection = std::vector<U>;

    using size_type = size_t;

private:
    Collection<TypePtr<ClearT>> m_objects;

public:
    template <typename U>
    friend void swap(CollectionOf<U>&, CollectionOf<U>&);

public:
    CollectionOf() :
        m_objects {} {}

    CollectionOf(const CollectionOf& other) :
        m_objects { other } {}

    CollectionOf(CollectionOf&& other) noexcept :
        m_objects { other } {}

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

    ~CollectionOf() {
        Clear();
    }

public:
    TypePtr<ClearT> operator[](size_type idx) {
        return m_objects[idx];
    }

    const TypePtr<ClearT> operator[](size_type idx) const {
        return m_objects[idx];
    }

    TypePtr<ClearT> At(size_type idx) {
        return m_objects.at(idx);
    }

    const TypePtr<ClearT> At(size_type idx) const {
        return m_objects.at(idx);
    }

    size_type Size() const {
        return m_objects.size();
    }

    bool IsEmpty() const {
        return m_objects.empty();
    }

    TypePtr<ClearT> Front() {
        return m_objects.front();
    }

    const TypePtr<ClearT> Front() const {
        return m_objects.front();
    }

    TypePtr<ClearT> Back() {
        return m_objects.back();
    }

    const TypePtr<ClearT> Back() const {
        return m_objects.back();
    }

    void Add(TypePtr<ClearT> object) {
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

    Collection<TypePtr<ClearT>>& Get() {
        return m_objects;
    }

    const Collection<TypePtr<ClearT>>& Get() const {
        return m_objects;
    }
};


template <typename U>
void swap(CollectionOf<U>& rhs, CollectionOf<U>& lhs) {
    if (&rhs == &lhs) return;

    using std::swap;

    swap(rhs.Get(), lhs.Get());
}


#endif // COLLECTIONOF_H
