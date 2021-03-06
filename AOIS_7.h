#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

const int recursion_border_index = -1;

bool first_input_control(string& numerical_string, bool is_it_word_size_input);
bool second_input_control(string& word, vector<bool>& word_we_build, int& expecting_size);
string word_output(const vector<bool>& word);
void book_output(vector<vector<bool>>& book);

void unique_word_builder(map<vector<bool>, bool>& word, int& word_size);
map<vector<bool>, bool> book_builder(int& word_size, int& lines_amount);

bool summary(bool first, bool second);
pair<bool, bool> recursion_compare(vector<bool>& term_one, const vector<bool>& term_two, int position);
void compare_and_swap(vector<bool>& main_search_element, vector<bool>& near_current, const vector<bool>& term, bool above, bool& overlap);

void find_near_above(map<vector<bool>, bool>& word_list, vector<bool>& compare_with);
void find_near_below(map<vector<bool>, bool>& word_list, vector<bool>& compare_with);
void task();

bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
void tests();
void our_own_input();