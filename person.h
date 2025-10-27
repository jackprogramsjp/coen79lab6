/*
 * CSEN 79 POD Class
 * Plain Old Data Example
 * Person
 */
#ifndef PERSON_H
#define PERSON_H

// Class declaration for roster
namespace csen79pods {
class Person {
public:
	using ID_t = unsigned int;	// really should be a 7-digit unsigned int
	Person(): Person(0, "", "") {}	// default as nothing
	Person(ID_t n, std::string fn, std::string ln): id{n}, first{fn}, last{ln} {}
	const ID_t getID() const { return id; }
	const std::string getFname() const {return first;}
	const std::string getLname() const {return last;}
	const std::string getFullname() const {return first + " " + last;}

private:
	ID_t id;
	std::string first;
	std::string last;

	friend std::ostream& operator<<(std::ostream& os, const Person &t) {
		os << "ID: " << std::setfill('0') << std::setw(8) << t.id << ", Name: " << t.first +std::string(" ") + t.last;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Person &t) {
		is >> t.id >> t.first >> t.last;
		return is;
	}
};
}
#endif // PERSON_H
