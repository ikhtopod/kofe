#include <cstdlib>
#include <iostream>
#include <string>

#include <application.h>


int main() {
    try {
        Application { "Kofe" }.Run();
    } catch (const ApplicationException& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "[Exception] " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "[Error] Unknown error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
