#include "application.h"

#ifdef DEBUG
#include <iostream>
#endif

#include <core/appexceptions.h>


Application::Application(const std::string& title) :
    m_title { title } {}

Application::Application(const char* title) :
    Application { std::string { title } } {}

void Application::Run() {
    std::cout << "[Title] " << m_title << std::endl;
}
