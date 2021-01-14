#include "everywhere.h"


Everywhere::Everywhere() :
    Singleton<Everywhere> {},
    m_units {} {}

Everywhere::~Everywhere() {
    m_units.clear();
}
