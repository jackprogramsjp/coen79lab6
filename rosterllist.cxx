/*
 * CSEN 79 Lab
 * Jack Murrow
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <new>
#include "person.h"
#include "roster.h"
#include "rosterllist.h"

namespace csen79 {
	// STUDENT WORKS
	// IMPLEMENT ALL THESE FUNCTIONS
	// These are code only to make the program compile.  They do not work!

	// Node

	RosterLList::Node::Node() {
		data = T{}; // Brace initialization, a default-constructed object/value
		next = nullptr; // Set next to null
	}

	RosterLList::Node::Node(T &t) {
		data = t;
		next = nullptr; // Set nullptr
	}

	RosterLList::Node::~Node() {
		// Nothing much to do as no ownership
		// List's destructor/erase already handles this in a way
		next = nullptr;
	}

	// Iterator

	RosterLList::iterator::iterator(Node *t) {
		ptr = t;
	}

	bool RosterLList::iterator::operator !=(const iterator &rhs) {
		return ptr != rhs.ptr;
	}

	Roster::T &RosterLList::iterator::operator *() {
		return ptr->data;
	}

	RosterLList::iterator &RosterLList::iterator::operator++() {
		if (ptr)
			ptr = ptr->next;

		return *this;
	}

	RosterLList::iterator RosterLList::begin() {
		return RosterLList::iterator(head);
	}

	RosterLList::iterator RosterLList::end() {
		return RosterLList::iterator(nullptr); // one past-the-end
	}

	// RosterLList

	RosterLList::RosterLList() {
		head = nullptr;
	}

	RosterLList::~RosterLList() {
		Node *curr = head; // Set a mutable variable for the loop

		while (curr) {
			Node *to_delete = curr; // We know this is not null
			curr = curr->next; // Each node is separately allocated, allowing us to obtain next
			delete to_delete; // Free it, the next pointer should have its own memory
		}

		head = nullptr;
	}

	// Insertion at the end
	// Allocation failure returns false
	bool RosterLList::insert(T &rec) {
		Node *n = new(std::nothrow) Node(rec);

		if (!n) return false; // Allocation failed

		// If head is null, this is empty list so insert node at head.
		if (!head) {
			head = n; // Update head pointer so list starts with our new node
			return true;
		}

		// Get the current head node
		Node *curr = head;

		// Iterate through each next node while it is not null
		while (curr->next)
			curr = curr->next;

		// Assign next node to n
		curr->next = n;
		return true;
	}

	// Erase first node with matching ID.
	// If not found, do nothing.
	void RosterLList::erase(Person::ID_t id) {
		Node *prev = nullptr;
		Node *curr = head;

		// Keep iterating if it is not matching ID
		while (curr && curr->data.getID() != id) {
			prev = curr; // Current node becomes previous node
			curr = curr->next; // Go to next node
		}

		if (!curr) return; // No matching ID found

		if (!prev) {
			// Assuming head so deleting head
			head = curr->next;
		} else {
			// Delete node in between prev and curr
			prev->next = curr->next;
		}
		delete curr;
	}


}
