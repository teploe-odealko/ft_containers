#include "Tester.hpp"
#include "vector"
#include "stack"
#include "Stack.hpp"


int main(int argc, char** argv) {

	std::string sf[] = {"value_type", "container_type", "size_type"};
	std::vector<std::string> stack_fields(std::begin(sf), std::end(sf));

	Tester< ft::Stack<int> > tester(stack_fields, stack_fields);
	ft::Stack<int> st;

	tester.print_state(st);
	return (0);
}