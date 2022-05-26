#include "Tester/Tester.hpp"
#include "vector"
#include "stack"
#include "stack.hpp"
#include "Tester/StackTester.hpp"
#include "Tester/VectorTester.hpp"
#include "Tester/MapTester.hpp"
#include "utils.hpp"
#include "pair.hpp"
#include "map.hpp"
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
	StackTester< NAMESPACE::stack<int>, int > simple_type_stack_tester(st);
	simple_type_stack_tester.run_test();

	NAMESPACE::stack<Person> per;
	StackTester< NAMESPACE::stack<Person>, Person > custom_type_stack_tester(per);
	custom_type_stack_tester.run_test();

	NAMESPACE::vector<int> simple_vec;
	VectorTester< NAMESPACE::vector<int>, int > simple_type_vec_tester(simple_vec);
	simple_type_vec_tester.run_test();


    NAMESPACE::map<int, int> simple_map;
    MapTester< NAMESPACE::map<int, int>, NAMESPACE::pair<int, int> > simple_type_map_tester(simple_map);
    simple_type_map_tester.run_test();

	return (0);
}