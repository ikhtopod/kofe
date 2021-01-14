#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "app_exceptions.h"

#include "icanbeeverywhere.h"
#include "singleton.h"
#include "window.h"
#include "opengl.h"
#include "input.h"
#include "space.h"

#include <string>
#include <unordered_map>


class Everywhere final : public Singleton<Everywhere> {
private:
    std::unordered_map<std::string, ICanBeEverywhere*> m_units;

public:
    Everywhere();
    virtual ~Everywhere();

    template <typename U>
    U& Get() {
        return *dynamic_cast<U*>(m_units.at(U::ToString()));
    }

    template <typename U>
    const U& Get() const {
        return *dynamic_cast<U*>(m_units.at(U::ToString()));
    }

    template <typename U>
    void Init(U* unit) {
        if (!dynamic_cast<ICanBeEverywhere*>(unit)) {
            throw EverywhereException { "Some unit cannot Init to Everywhere" };
        }

        if (m_units.count(U::ToString())) {
            throw EverywhereException { "Unit \"" + U::ToString() + "\" already exists" };
        }

        m_units[U::ToString()] = unit;
    }

    template <typename U>
    void Free() {
        if (!m_units.count(U::ToString())) {
            throw EverywhereException { "Unit \"" + U::ToString() + "\" not exists" };
        }

        delete m_units[U::ToString()];
        m_units[U::ToString()] = nullptr;
    }

};

#endif // EVERYWHERE_H
