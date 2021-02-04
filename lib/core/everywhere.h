#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "app_exceptions.h"

#include "icanbeeverywhere.h"
#include "singleton.h"

#include "deltatime.h"
#include "window.h"

#include "graphics.h"
#include "opengl.h"

#include "input.h"

#include "camera.h"
#include "freecamera.h"
#include "targetcamera.h"

#include "materialstorage.h"
#include "space.h"
#include "projection.h"
#include "orthographic.h"
#include "perspective.h"

#include <string>
#include <unordered_map>
#include <typeinfo>


class Everywhere final : public Singleton<Everywhere> {
private:
    template <typename T>
    static std::string ClassName() {
        static const std::string CLASS_NAME { typeid(T).name() };
        return CLASS_NAME;
    }

private:
    std::unordered_map<std::string, ICanBeEverywhere*> m_units;

public:
    Everywhere();
    virtual ~Everywhere();

    template <typename U>
    U& Get() {
        return *dynamic_cast<U*>(m_units.at(ClassName<U>()));
    }

    template <typename U>
    const U& Get() const {
        return *dynamic_cast<U*>(m_units.at(ClassName<U>()));
    }

    template <typename U>
    void Init(U* unit) {
        if (!dynamic_cast<ICanBeEverywhere*>(unit)) {
            throw EverywhereException { "Some unit cannot Init to Everywhere" };
        }

        if (m_units.count(ClassName<U>())) {
            throw EverywhereException { "Unit \"" + ClassName<U>() + "\" already exists" };
        }

        m_units[ClassName<U>()] = unit;
    }

    template <typename U>
    void Free() {
        if (m_units.count(ClassName<U>())) {
            delete m_units[ClassName<U>()];
            m_units[ClassName<U>()] = nullptr;
        }
    }

};

#endif // EVERYWHERE_H
