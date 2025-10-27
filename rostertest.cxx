/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "person.h"
#include "roster.h"
#include "rosterllist.h"

namespace csen79 {

void RosterLList::testRoster() {
    Person t;
	std::string cmd;

	// Read cmd first, then branch accordingly
    while (std::cin >> cmd) {
        switch (cmd[0]) {
        case Command::Add:
            // Insert a record
            std::cin >> t;
            try {
                this->insert(t); // insert returns if successful
            } catch (std::out_of_range &e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case Command::Erase: {
            // remove a record, given the ID
            Person::ID_t id;
            std::cin >> id;
            this->erase(id);
            std::cout << "Erase " << id << std::endl;
            }
            break;
        case Command::Print:
            // listing the entire roster with a rudimentary iterator
            std::cout << "---- Current Roster ----"  << std::endl;
            int i = 1;
            for (auto st = this->begin(); st != this->end(); ++st, i++)
                std::cout << i << ": " << *st << std::endl;
            break;
        }
    }
}

}   // namespace
