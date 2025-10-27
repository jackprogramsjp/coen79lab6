/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "person.h"
#include "roster.h"


namespace csen79 {

	// insert into the roster
	void Roster::insert(const T &rec) {
		if (last >= CAPACITY)
			throw std::out_of_range("Roster iterator exceeded range: "+std::to_string(last));

		// if the array is not full, add to the end
		roster[last++] = rec;
	}

	// simply mark the slot empty
	void Roster::erase(Person::ID_t id) {
		for (auto i = 0; i < CAPACITY; i++)
			if (roster[i].getID() == id) {
				for (auto j = i; j < last-2; j++)
					roster[j] = roster[j+1];
				--last;
			}
		
	}

	// rudimentary iterator
	// in the future, this will return an object of iterator type
	Roster::T* Roster::begin(void) {
		idx = 0;
		return roster;
	}

	Roster::T* Roster::end(void) {
		return roster+last;
	}

	// The next element for interation
	// if already reached the end, throw exception
	Roster::T* Roster::next(void) {
		if (idx >= last || idx >= CAPACITY)
			throw std::out_of_range("Roster iterator exceeded range: "+std::to_string(idx));

		++idx;
		return roster+idx;
	}
}
