#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

bool first_input_control(string& numerical_string, bool is_it_word_size_input)
{
	int low_ASCII_border = 60, high_ASCII_border = 71, amount_of_words_border = 50, word_size_border = 10;
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
bool second_input_control(string& word, int& expecting_size)
{
	if (word.size() != expecting_size) return false;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] != '1' && word[i] != '0') return false;
	}
	return true;
}
vector<bool> from_string_to_vector(vector<bool>& term)
{
	vector<bool>result;
	for (int i = 0; i < term.size(); i++)
	{
		if (term[i] == '0') result.push_back(0);
		else result.push_back(1);
	}
	return result;
}
string word_output(vector<bool>& word)
{
	string output;
	for (int i = 0; i < word.size(); i++)
	{
		output += word[i];
	}
	return output;
}
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
			result.push_back(rand() % 2);
		}
	} while (word[result] && counter < counter_border);
	word[result] = true;
	return result;
}
void compare_and_swap(vector<bool>& main_search_element, vector<bool>& nar_current, vector<bool>& term, bool above, bool& overlap)
{
	pair<bool, bool> main_compare = recursion_compare(main_search_element, term, 0);
	pair<bool, bool> current_near_compare = recursion_compare(near_current, term, 0);
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
	if (!overlap) cout << "Nothing found compare with this!" << endl;
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
	if (!overlap) cout << "Nothing found compare with this!" << endl;
	else cout << "Nearest word below found : " << word_output(result) << endl;
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
void task(int word_size, int lines_amount)
{
	cout << "Enter word we looking for (" << word_size << ") elements : ";
	string input;
	cin.ignore();
	getline(cin, input);
	if (!second_input_control(input, word_size)) {
		cout << "Enter something possibble to work with!!" << endl;
	}
	vector<bool>search_word = from_string_to_vector(input);


	

}

int main()
{
	vector<bool> t1{ 1,0}, t2{ 1,1};
	pair<bool, bool> test = recursion_compare(t1, t2, 0);
	cout << test.first << "  " << test.second;
}
