#include <cstdlib>
#include <iostream>
#include <string>

#include <core/appexceptions.h>
#include <core/application.h>


int main() {
    try {
        Application{"Seductive Dream Engine"}.Run();
    } catch (const ApplicationException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "[Exception] Unknown error" << std::endl;
    }

    return EXIT_SUCCESS;
}
