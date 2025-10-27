/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <cassert>
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

static std::vector<Person::ID_t> collect_ids(RosterLList& l) {
    std::vector<Person::ID_t> v;
    for (auto it = l.begin(); it != l.end(); ++it) {
        v.push_back((*it).getID());
    }
    return v;
}

void RosterLList::extraTestRoster() {
    // Test 1: Check empty roster list
    {
        RosterLList empty;
        auto b = empty.begin();
        auto e = empty.end();
        assert(!(b != e));

        // Should not iterate
        for (auto it = empty.begin(); it != empty.end(); ++it) {
            assert(false && "Empty list should not iterate");
        }
    }

    // Test 2: One insert and iteration count
    {
        RosterLList l_list;
        Person a(10, "A", "B");

        assert(l_list.insert(a));

        int count = 0;
        for (auto it = l_list.begin(); it != l_list.end(); ++it)
            ++count;

        assert(count == 1);

        // Deref and iterate
        for (auto it = l_list.begin(); it != l_list.end(); ++it) {
            assert((*it).getFname() == "A");
            assert((*it).getLname() == "B");
        }
    }

    // Test 3: Current insert behavior = append, so verify insertion order based on appends
    {
        RosterLList l_list;
        Person a(20, "A", "B");
        Person b(10, "C", "D");
        Person c(30, "E", "F");

        assert(l_list.insert(a));
        assert(l_list.insert(b));
        assert(l_list.insert(c));

        auto ids = collect_ids(l_list);

        assert(ids.size() == 3);
        // Ensure append order
        assert(ids[0] == 20 && ids[1] == 10 && ids[2] == 30);
    }

    // Test 3: Erase -> head, middle, tail, and missing
    {
        RosterLList l_list;
        Person a(1, "A", "x");
        Person b(2, "B", "x");
        Person c(3, "C", "x");
        Person d(4, "D", "x");

        assert(l_list.insert(a) && l_list.insert(b) && l_list.insert(c) && l_list.insert(d));
        // List should now be 1, 2, 3, 4

        l_list.erase(1); // Remove head

        auto v1 = collect_ids(l_list); // expect 2, 3, 4
        assert(v1.size() == 3 && v1[0] == 2 && v1[1] == 3 && v1[2] == 4);

        l_list.erase(3); // Remove middle
        auto v2 = collect_ids(l_list); // expect 2, 4
        assert(v2.size() == 2 && v2[0] == 2 && v2[1] == 4);

        l_list.erase(4); // Remove tail
        auto v3 = collect_ids(l_list); // expect 2
        assert(v3.size() == 1 && v3[0] == 2);

        l_list.erase(1000); // No operation
        auto v4 = collect_ids(l_list); // still 2
        assert(v4.size() == 1 && v4[0] == 2);
    }

    // Test 4: Iterating from last, then to it == end()
    {
        RosterLList l_list;

        for (int i = 0; i < 5; ++i) {
            Person p(i, "x", "x");
            assert(l_list.insert(p));
        }
        auto it = l_list.begin();
        int steps = 0;
        // loop terminates only if ++ hits end() (nullptr)
        while (it != l_list.end()) {
            ++it;
            ++steps;
        }
        assert(steps == 5);
    }

    std::cout << "ALL TESTS HAVE PASSED.\n";
}

}   // namespace
