#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "app_exceptions.h"

#include "interface/icanbeeverywhere.h"
#include "misc/singleton.h"

#include "misc/deltatime.h"
#include "window/window.h"

#include "graphics/graphics.h"
#include "graphics/opengl.h"
#include "graphics/vulkan.h"

#include "input/input.h"

#include "camera/camera.h"
#include "camera/freecamera.h"
#include "camera/targetcamera.h"

#include "storage/texturestorage.h"
#include "storage/modelstorage.h"

#include "storage/lightstorage.h"
#include "light/light.h"
#include "light/pointlight.h"

#include "storage/materialstorage.h"
#include "space/space.h"
#include "projection/projection.h"
#include "projection/orthographic.h"
#include "projection/perspective.h"

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <type_traits>


class Everywhere final : public Singleton<Everywhere> {
private:
    template <typename T>
    static std::string ClassName() {
        static const std::string CLASS_NAME { typeid(T).name() };
        return CLASS_NAME;
    }

private:
    std::unordered_map<std::string, ICanBeEverywhere*> m_units;

    template <typename U>
    U& FindBase() {
        for (auto& unit : m_units) {
            using Base = typename std::remove_pointer<decltype(unit.second)>::type;
            using Derived = typename std::remove_pointer<U>::type;

            if (std::is_base_of<Base, Derived>::value) {
                return *dynamic_cast<U*>(unit.second);
            }
        }

        throw EverywhereException { "Unit \"" + ClassName<U>() + "\" is not exists" };
    }

public:
    Everywhere();
    virtual ~Everywhere();

    template <typename U>
    U& Get() {
        if (!m_units.count(ClassName<U>())) {
            throw EverywhereException { "Unit \"" + ClassName<U>() + "\" is not exists" };
        }

        return *dynamic_cast<U*>(m_units.at(ClassName<U>()));
    }

    template <typename U>
    const U& Get() const {
        if (!m_units.count(ClassName<U>())) {
            throw EverywhereException { "Unit \"" + ClassName<U>() + "\" is not exists" };
        }

        return *dynamic_cast<U*>(m_units.at(ClassName<U>()));
    }

    template <typename U>
    U& FindSimilarClass() {
        if (!m_units.count(ClassName<U>())) {
            return FindBase<U>();
        }

        return *dynamic_cast<U*>(m_units.at(ClassName<U>()));
    }

    template <typename U>
    const U& FindSimilarClass() const {
        if (!m_units.count(ClassName<U>())) {
            return FindBase<U>();
        }

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
