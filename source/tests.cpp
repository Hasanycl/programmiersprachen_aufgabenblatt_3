#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"


//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test case for deleting
#include "sub_tests/clear.test"

//test case for copy constructor
#include "sub_tests/copy_constructor.test"

//test case for unifying assignment operator
#include "sub_tests/assignment_operator.test"

//test cases for reversing the list
#include "sub_tests/reverse.test"

//test cases for equality & inequality
#include "sub_tests/equality_inequality.test"

//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"


//test case for move constructor
#include "sub_tests/move_constructor.test"

#include "sub_tests/initializer_list_plus_operator.test"


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}




