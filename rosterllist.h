/*
 * CSEN 79 Lab Sample Code
 */
#ifndef ROSTERLLIST_H
#define ROSTERLLIST_H

// Class declaration for roster
namespace csen79 {
	class RosterLList : public Roster {
	public:
		struct Node {
			T data;
			Node *next;

			Node();
			Node(T &t);
			~Node();
		};
		class iterator {
		public:
			iterator(Node *t);
			bool operator !=(const iterator &rhs);
			T &operator *();
			iterator &operator ++();
		private:
			Node* ptr;
		};

		RosterLList();
		~RosterLList();
		bool insert(T &);
		void erase(Person::ID_t);
		void testRoster();
		friend iterator;

		iterator begin();
		iterator end();
	private:
		Node *head;
	};
}
#endif // ROSTERLLIST_H
