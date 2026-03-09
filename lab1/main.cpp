// Lab 1 — Weryfikacja środowiska
// Cel: sprawdzenie czy GLFW i GLAD są poprawnie podlinkowane.
// Jeśli ten program skompiluje się bez błędów — środowisko jest gotowe.

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "Lab 1: biblioteki GLFW i GLAD zaladowane poprawnie." << std::endl;
    return 0;
}
