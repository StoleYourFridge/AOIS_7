#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool summary(bool first, bool second)
{
	if (first && second) return true;
	else return (first + second);
}
pair<bool, bool> recursion_compare(vector<bool> &term_one, vector<bool>& term_two, int position)
{
	pair<bool, bool> result;
	if (position == term_one.size()) {
		result.first = false;
		result.second = false;
		return result;
	}
	else {
		pair<bool, bool> previous_result = recursion_compare(term_one, term_two, position + 1);
		result.first = summary(previous_result.first, !term_one[position] * term_two[position] * !previous_result.second);
		result.second = summary(previous_result.second, term_one[position] * !term_two[position] * !previous_result.first);
		return result;
	}
}

int main()
{
	vector<bool> t1{ 1,0}, t2{ 1,1};
	pair<bool, bool> test = recursion_compare(t1, t2, 0);
	cout << test.first << "  " << test.second;
}
