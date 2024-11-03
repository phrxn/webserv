#include "Menu.hpp"

#include <iostream>

#include "SimpleConnection.hpp"

void showMainMenu() {
	std::cout << "--------------- Main Menu ---------------" << std::endl;
	std::cout << "  Choose an option: " << std::endl;
	std::cout << "    \033[1;32mq\033[0m) to exit " << std::endl;
	std::cout << "    \033[1;32m1\033[0m) to simple connection:" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

void Menu::mainMenu() {
  std::string option;

  SimpleConnection sc;

  while (option != "q") {
	showMainMenu();
	std::cout << "The option: ";
    std::cin >> option;
	if (option == "q") continue;
    else if (option == "1") sc.startSimpleConnection();
	else std::cout << "\033[1;31mInvalid option!\033[0m" << std::endl;

  }
}
