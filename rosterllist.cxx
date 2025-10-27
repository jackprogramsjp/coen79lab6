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

// bool RosterLList::insert(T &rec) {
//     Node *n = new(std::nothrow) Node(rec);
//     if (!n) return false;
//
//     if (!head) {                 // empty list → new head
//         head = n;
//         return true;
//     }
//
//     // walk to tail and append
//     Node *curr = head;
//     while (curr->next) curr = curr->next;
//     curr->next = n;
//     return true;
// }

// void RosterLList::erase(Person::ID_t id) {
// 	Node *prev = nullptr;
// 	Node *curr = head;
//
// 	while (curr && curr->data.getID() != id) {
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	if (!curr) return;               // not found
//
// 	if (!prev) head = curr->next;    // deleting head
// 	else       prev->next = curr->next;
//
// 	delete curr;
// }


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

	RosterLList::iterator RosterLList::begin() {
		return RosterLList::iterator(head);
	}

	RosterLList::iterator RosterLList::end() {
		return RosterLList::iterator(nullptr); // one past-the-end
	}

	// Insertion should keep list sorted by ID of perosn (ascending)
	// If ID is equal (existing), we update that node's data (replace) and succeed
	// Allocation failure returns false
	bool RosterLList::insert(T &rec) {
		Node *n = new(std::nothrow) Node(rec);

		if (!n) return false; // Allocation failed

		// Conditions:
		// if head is null
		// or
		// is the new record's ID smaller than the current first record's ID
		//
		// THIS KEEPS LIST SORTED BY ID NUMBERS IN ASCENDING ORDER
		// Basically, this checks whether the new node should be inserted at the front of the list.
		if (!head || rec.getID() < head->data.getID()) {
			n->next = head; // Set the new node's next pointer to the current head
			head = n; // Update head pointer so list starts with our new node
			return true;
		}

		// Keep iterating/walking all the way to insertion point
		Node *prev = nullptr;
		Node *curr = head;

		// This is to keep list sorted by ID numbers in ascending order,
		// basically, keep iterating until rec ID is no longer bigger
		while (curr && curr->data.getID() < rec.getID()) {
			prev = curr; // Current node becomes previous node
			curr = curr->next; // Go to next node
		}

		// Duplicate ID, then replace
		if (curr && curr->data.getID() == rec.getID()) {
			curr->data = rec; // Update node's data
			delete n; // We allocated one before, but we don't need it any more, so free it to prevent leak
			return true;
		}

		// Dummy/sentinel head node can obviously be added to remove special cases for the head.
		// But here, we know prev basically can never be null.
		//
		// Case 1: Empty list or new head (already returned)
		// Case 2: Traversing to insertion point (prev has been assigned at least once due to case 1)
		// Case 3: Duplicate ID (returned)
		//
		// Case 4: Insertion between prev and curr
		// prev should never be null,
		// it would only be null if the new node should go before the head,
		// but this was already handled in case 1
		assert(prev != nullptr);

		// Insert between prev and curr
		prev->next = n;
		n->next = curr;

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
