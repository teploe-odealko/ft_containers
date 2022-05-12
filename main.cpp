#include "Tester.hpp"
#include "vector"
#include "stack"
#include "stack.hpp"

//ft::stack<int> st;
//Tester< ft::vector<int>, int > tester("vector", st);
#ifdef FT
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

class Person{
public:
	int passport_id;
	Person(int passport_id=rand()): passport_id(passport_id){};
	friend std::ostream &operator<<( std::ostream  &out, Person &p ) {
		out << "Persons's passport id is " << p.passport_id;
		return out;
	}
};

int main() {

	NAMESPACE::stack<int> st;
	Tester< NAMESPACE::stack<int>, int > stack_simple_type_tester("stack", st);
	stack_simple_type_tester.run_test();

	NAMESPACE::stack<Person> per;
	Tester< NAMESPACE::stack<Person>, Person > stack_custom_type_tester("stack", per);
	stack_custom_type_tester.run_test();


	return (0);
}