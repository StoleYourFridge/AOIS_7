#include "AOIS_7.h"

bool first_input_control(string& numerical_string, bool is_it_word_size_input)
{
	int low_ASCII_border = 48, high_ASCII_border = 57, amount_of_words_border = 50, word_size_border = 10;
	if (numerical_string.size() == 0) return false;
	for (int i = 0; i < numerical_string.size(); i++)
	{
		if ((int)(numerical_string[i]) < low_ASCII_border || (int)(numerical_string[i]) > high_ASCII_border) return false;
	}
	int numerical_result = stoi(numerical_string);
	if (is_it_word_size_input) {
		if (numerical_result <= 0 || numerical_result > word_size_border) return false;
	}
	else {
		if (numerical_result <= 0 || numerical_result > amount_of_words_border) return false;
	}
	return true;
}
bool second_input_control(string& word, vector<bool>& word_we_build, int& expecting_size)
{
	word_we_build.clear();
	if (word.size() != expecting_size) return false;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] != '1' && word[i] != '0') {
			word_we_build.clear();
			return false;
		}
		else if (word[i] == '0') word_we_build.push_back(0);
		else word_we_build.push_back(1);
	}
	return true;
}
string word_output(const vector<bool>& word)
{
	string output;
	for (int i = 0; i < word.size(); i++)
	{
		if (!word[i]) output += '0';
		else if (word[i]) output += '1';
	}
	return output;
}
void book_output(map<vector<bool>, bool> &book)
{
	map<vector<bool>, bool> :: iterator it = book.begin();
	cout << "Amount of words : " << book.size() << endl;
	for (int i = 0; it != book.end(); it++, i++)
	{
		cout << "book[" << i << "] = " << word_output(it->first) << endl;
	}
}

void unique_word_builder(map<vector<bool>, bool>& word, int& word_size)
{
	srand(time(NULL));
	vector<bool> result;
	int counter = 0, counter_border = 100;
	do
	{
		result.clear();
		counter++;
		for (int i = 0; i < word_size; i++)
		{
			int positive_sign = rand() % 2;
			if (positive_sign == 1) {
				result.push_back(true);
			}
			else {
				result.push_back(false);
			}
		}
	} while (word[result] && counter < counter_border);
	word[result] = true;
}
map<vector<bool>, bool> book_builder(int &word_size, int &lines_amount)
{
	map<vector<bool>, bool> unique_checker;
	for (int i = 0; i < lines_amount; i++)
	{
		unique_word_builder(unique_checker, word_size);
	}
	return unique_checker;
}

bool summary(bool first, bool second)
{
	if (first && second) return true;
	else return (first + second);
}
pair<bool, bool> recursion_compare(vector<bool>& term_one, const vector<bool>& term_two, int position)
{
	pair<bool, bool> result;
	if (position == recursion_border_index) {
		result.first = false;
		result.second = false;
		return result;
	}
	else {
		pair<bool, bool> previous_result = recursion_compare(term_one, term_two, position - 1);
		result.first = summary(previous_result.first, !term_one[position] * term_two[position] * !previous_result.second);
		result.second = summary(previous_result.second, term_one[position] * !term_two[position] * !previous_result.first);
		return result;
	}
}
void compare_and_swap(vector<bool>& main_search_element, vector<bool>& near_current, const vector<bool>& term, bool above, bool& overlap)
{   
	pair<bool, bool> main_compare = recursion_compare(main_search_element, term, main_search_element.size() - 1);
	pair<bool, bool> current_near_compare = recursion_compare(near_current, term, near_current.size() - 1);
	if (above) {
		if (((main_compare.first && !main_compare.second) || (!main_compare.first && !main_compare.second)) && 
			((!current_near_compare.first && current_near_compare.second) || (!current_near_compare.first && !current_near_compare.second))) {
			near_current = term;
			overlap = true;
		}
	}
	else {
		if (((!main_compare.first && main_compare.second) || (!main_compare.first && !main_compare.second)) &&
			((current_near_compare.first && !current_near_compare.second) || (!current_near_compare.first && !current_near_compare.second))) {
			near_current = term;
			overlap = true;
		}
	}
}

void find_near_above(map<vector<bool>, bool>& word_list, vector<bool>& compare_with)
{
	map<vector<bool>, bool> ::iterator it = word_list.begin();
	vector<bool> result(it->first.size(), 1);
	bool overlap = false;
	for (it; it != word_list.end(); it++)
	{
		compare_and_swap(compare_with, result, it->first, true, overlap);
	}
	if (!overlap) cout << "Nothing found compare with this above!" << endl;
	else cout << "Nearest word above found : " << word_output(result) << endl;
}
void find_near_below(map<vector<bool>, bool>& word_list, vector<bool>& compare_with)
{
	map<vector<bool>, bool> ::iterator it = word_list.begin();
	vector<bool> result(it->first.size(), 0);
	bool overlap = false;
	for (it; it != word_list.end(); it++)
	{
		compare_and_swap(compare_with, result, it->first, false, overlap);
	}
	if (!overlap) cout << "Nothing found compare with this below!" << endl;
	else cout << "Nearest word below found : " << word_output(result) << endl;
}
void task()
{
	string str_word_size, str_lines_amount;
	cout << "Enter word size (10 max) : ";
	cin >> str_word_size;
	cout << "Enter book size (50 max) : ";
	cin >> str_lines_amount;
	if (!first_input_control(str_word_size, true)) {
		cout << "Enter something possible to work with!!" << endl;
		return;
	}
	if (!first_input_control(str_lines_amount, false)) {
		cout << "Enter something possible to work with!!" << endl;
		return;
	}
	int word_size = stoi(str_word_size), lines_amount = stoi(str_lines_amount);
	cout << "Enter word we are looking for ::: (" << word_size << ") elements : ";
	string input;
	vector<bool> search_word;
	cin.ignore();
	getline(cin, input);
	if (!second_input_control(input,search_word, word_size)) {
		cout << "Enter something possibble to work with!!" << endl;
		return;
	}
	map<vector<bool>, bool> book = book_builder(word_size, lines_amount);
	book_output(book);
	find_near_above(book, search_word);
	find_near_below(book, search_word);
}

bool Test1()
{
	vector<bool> A{ 0,0,0,0 }, S{ 0,0,0,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (compare_result.first && !compare_result.second) {
		cout << "Test1 correct!" << endl;
		return true;
	}
	else {
		cout << "Test1 incorrect!" << endl;
		return false;
	}
}
bool Test2()
{
	vector<bool> A{ 0,1,1,1 }, S{ 0,0,0,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && compare_result.second) {
		cout << "Test2 correct!" << endl;
		return true;
	}
	else {
		cout << "Test2 incorrect!" << endl;
		return false;
	}
}
bool Test3()
{
	vector<bool> A{ 0,0,0,1 }, S{ 0,0,0,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && !compare_result.second) {
		cout << "Test3 correct!" << endl;
		return true;
	}
	else {
		cout << "Test3 incorrect!" << endl;
		return false;
	}
}
bool Test4()
{
	vector<bool> A{ 1,1,1,1 }, S{ 0,1,1,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && compare_result.second) {
		cout << "Test4 correct!" << endl;
		return true;
	}
	else {
		cout << "Test4 incorrect!" << endl;
		return false;
	}
}
bool Test5()
{
	vector<bool> A{ 1,1,1,1 }, S{ 1,1,1,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && !compare_result.second) {
		cout << "Test5 correct!" << endl;
		return true;
	}
	else {
		cout << "Test5 incorrect!" << endl;
		return false;
	}
}
bool Test6()
{
	vector<bool> A{ 0,1,0,0,0,0 }, S{ 0,0,1,1,1,0 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && compare_result.second) {
		cout << "Test6 correct!" << endl;
		return true;
	}
	else {
		cout << "Test6 incorrect!" << endl;
		return false;
	}
}
bool Test7()
{
	vector<bool> A{ 1,1,0,0,0,0 }, S{ 1,1,0,0,0,0 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && !compare_result.second) {
		cout << "Test7 correct!" << endl;
		return true;
	}
	else {
		cout << "Test7 incorrect!" << endl;
		return false;
	}
}
bool Test8()
{
	vector<bool> A{ 0,1,1,1,1,1,1,1,1,1 }, S{ 1,0,0,0,0,0,0,0,0,0 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (compare_result.first && !compare_result.second) {
		cout << "Test8 correct!" << endl;
		return true;
	}
	else {
		cout << "Test8 incorrect!" << endl;
		return false;
	}
}
bool Test9()
{
	vector<bool> A{ 0,1,1,1,1,1,1,1,1,1 }, S{ 0,1,1,1,1,1,1,1,1,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (!compare_result.first && !compare_result.second) {
		cout << "Test9 correct!" << endl;
		return true;
	}
	else {
		cout << "Test9 incorrect!" << endl;
		return false;
	}
}
bool Test10()
{
	vector<bool> A{ 0,1,1,1,1,0,1,1,1,1 }, S{ 0,1,1,1,1,1,1,1,1,1 };
	pair<bool, bool> compare_result = recursion_compare(A, S, A.size() - 1);
	if (compare_result.first && !compare_result.second) {
		cout << "Test10 correct!" << endl;
		return true;
	}
	else {
		cout << "Test10 incorrect!" << endl;
		return false;
	}
}
void tests()
{
	int correct_counter = 0;
	correct_counter += Test1();
	correct_counter += Test2();
	correct_counter += Test3();
	correct_counter += Test4();
	correct_counter += Test5();
	correct_counter += Test6();
	correct_counter += Test7();
	correct_counter += Test8();
	correct_counter += Test9();
	correct_counter += Test10();
	if (correct_counter == 10) {
		cout << "All tests passed correctly!" << endl;
	}
}
void our_own_input()
{
	int choice;
	cout << "1)Tests :: 2)Task" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1: tests();
		break;
	case 2: task();
		break;
	default: cout << "Enter something possible to work with!" << endl;
		return;
	}
}