/*
 * CSEN 79 Lab3
 * Student Roster
 */
#ifndef ROSTER_H
#define ROSTER_H
using csen79pods::Person;

// Class declaration for roster
namespace csen79 {
	enum Command : char {Add='A', Erase='X', Print='L'};
	// class of a roster of students
	class Roster {
	public:
		using T = Person;
		static constexpr int CAPACITY=30;

		Roster(): idx(0), last(0), roster{} {}
		void insert(const T &);
		void erase(T::ID_t);

		T* begin(void);
		T* end(void);
		T* next(void);	// poor imitation of ++ operator
	private:
		T roster[CAPACITY];
		int idx;	// for the iterator
		int last;	// for insertion
	};
}
#endif // ROSTER_H
