#include "everywhere.h"


Everywhere::Everywhere() :
    Singleton<Everywhere> {},
    m_units {} {}

Everywhere::~Everywhere() {
    for (auto& [key, value] : m_units) {
        if (value) {
            delete value;
            value = nullptr;
        }
    }

    m_units.clear();
}
