#include <cstdlib>
#include <iostream>
#include <string>

#include <core/app_exceptions.h>
#include <core/application.h>


int main() {
    try {
        Application{"Seductive Dream"}.Run();
    } catch (const ApplicationException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Exception] " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "[Error] Unknown error" << std::endl;
    }

    return EXIT_SUCCESS;
}
