#include "everywhere.h"


void Everywhere::InitWindow(Window* window) { m_window = window; }
Window& Everywhere::GetWindow() { return *m_window; }
void Everywhere::FreeWindow() { delete m_window; }
