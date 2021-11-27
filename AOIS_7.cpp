#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

const int recursion_border_index = -1;

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
string word_output(vector<bool>& word)
{
	string output;
	for (int i = 0; i < word.size(); i++)
	{
		if (!word[i]) output += '0';
		else if (word[i]) output += '1';
	}
	return output;
}
void book_output(vector<vector<bool>> &book)
{
	cout << "Amount of words : " << book.size() << endl;
	for (int i = 0; i < book.size(); i++)
	{
		cout << "book[" << i + 1 << "] = " << word_output(book[i]) << endl;
	}
}

vector<bool> unique_word_builder(map<vector<bool>, bool>& word, int& word_size)
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
	return result;
}
vector<vector<bool>> book_builder(int &word_size, int &lines_amount)
{
	vector<vector<bool>> words;
	map<vector<bool>, bool> unique_checker;
	for (int i = 0; i < lines_amount; i++)
	{
		words.push_back(unique_word_builder(unique_checker, word_size));
	}
	return words;
}

bool summary(bool first, bool second)
{
	if (first && second) return true;
	else return (first + second);
}
pair<bool, bool> recursion_compare(vector<bool> &term_one, vector<bool>& term_two, int position)
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
void compare_and_swap(vector<bool>& main_search_element, vector<bool>& near_current, vector<bool>& term, bool above, bool& overlap)
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

void find_near_above(vector<vector<bool>>& word_list, vector<bool>& compare_with)
{
	vector<bool> result(word_list[0].size(), 1);
	bool overlap = false;
	for (int i = 0; i < word_list.size(); i++)
	{
		compare_and_swap(compare_with, result, word_list[i], true, overlap);
	}
	if (!overlap) cout << "Nothing found compare with this above!" << endl;
	else cout << "Nearest word above found : " << word_output(result) << endl;
}
void find_near_below(vector<vector<bool>>& word_list, vector<bool>& compare_with)
{
	vector<bool> result(word_list[0].size(), 0);
	bool overlap = false;
	for (int i = 0; i < word_list.size(); i++)
	{
		compare_and_swap(compare_with, result, word_list[i], false, overlap);
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
	vector<vector<bool>> book = book_builder(word_size, lines_amount);
	book_output(book);
	find_near_above(book, search_word);
	find_near_below(book, search_word);
}

int main()
{
	task();
	return 0;
}
