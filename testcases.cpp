#include "DLL.h"
#include <assert.h>

void test_add_back() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	cout << "My result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("two", 2) << '\n';
}

void test_add_front() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.add_front("zero", 0);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("zero", 0) << ", " << Node("one", 1) << ", " << Node("two", 2) << '\n';
}

void test_add_after() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.add_after("one", "middle", 0);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("middle", 0) << ", " << Node("two", 2) << '\n';
}

void test_remove_front() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.remove_front();
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("two", 2) << '\n';
}

void test_remove_back() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.remove_back();
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << '\n';
}

void test_remove_key() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	list.remove_key("two");
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("three", 3) << '\n';
}

void test_search() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	auto result = list.search("two");
	cout << "\nMy result: " << result << '\n';
	cout << "Expected:  " << Node("two", 2) << '\n';
}

void test_update_value() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	list.update_value("two", 22);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("two", 22) << ", " << Node("three", 3) << '\n';
}

int main() {
	// test_add_back();
	// test_add_front();
	// test_add_after();
	// test_remove_front();
	// test_remove_back();
	//test_remove_key();
	// test_search();
	// test_update_value();
	vector<Node> vec = { Node("one", 1), Node("two", 2) };
  auto list = DLL(vec);
  list.add_after("two","end", 50);
  assert(list.get_tail()->value == 50);
  assert(list.get_tail()->key == "end");
  auto ret = list.add_after("not_in_list", "test", 12);
  assert(ret == Node("", 0));
  assert(list.get_size() == 3);
  ret = list.add_after("one", "middle", 10);
  assert(list.get_size() == 4);
  assert(*(list.get_head()) == Node("one", 1));
  assert(*(list.get_head()->next) == Node("middle", 10));
  assert(*(list.get_head()->next->next) == Node("two", 2));
  assert(*(list.get_head()->next->next->next) == Node("end", 50));
  assert(*(list.get_head()->next->next->next) == *list.get_tail());
  assert(*(list.get_tail()->prev) == Node("two", 2));
  assert(*(list.get_tail()->prev->prev) == Node("middle", 10));
  assert(*(list.get_tail()->prev->prev->prev) == Node("one", 1));
	
	return 0;
}