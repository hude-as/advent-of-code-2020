#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// part 1
// O(n.Log(n) + n / 2) ?
int multiply_matching_pair_that_sumup_into_2020(vector<int> account_lines) {
	sort(account_lines.begin(), account_lines.end());
	vector<int>::iterator	head = account_lines.begin();
	vector<int>::iterator	tail = account_lines.end() - 1;

	while (head != tail) {
		int result = *head + *tail;
		if (result > 2020) {
			--tail;
		} else if (result < 2020) {
			++head;
		} else {
			return *head * *tail;
		}
	}
	return 0;
}

// part 2
// on veut 25
// 0, 2, 3, 5, 6, 8, 9, 11, 12, 13, 15, 17
// 0 + 17 = 17. 17 + dichotomic search (]0, 17[)
// 0 + 17 + 9 > 25
// 0 + 17 + 3 < 25
// 0 + 17 + 6 < 25
// 0 + 17 + 7 < 25
// 0 + 17 + 8 => found.
// si on n'avait pas trouvé : (pas de 8) 
// 2 + 17 ou 0 + 15 ? => based on last comparaison ? why ? why not
int multiply_matching_triple_that_sumup_into_2020(vector<int> account_lines) {
	sort(account_lines.begin(), account_lines.end());
	vector<int>::iterator	head = account_lines.begin();
	vector<int>::iterator	tail = account_lines.end() - 1;

	while (head != tail) {
		int to_find = 2020 - *head - *tail;
		// binary search between 2 values
		vector<int>::iterator complement = lower_bound(head, tail, to_find);
		int result = *head + * tail + *complement;
		// if to_find not found, lower_bound return last element
		// in case that last element + head + tail > 2020, then we decrease tail and vice-versa when last element + head + tail < 2020
		if (result > 2020) {
			--tail;
		} else if (result < 2020) {
			++head;
		} else {
			return *head * *tail * *complement;
		}
	}
	return 0;

}

int main(int argc, char* argv[]) {
	string		input;
	vector<int>	account_lines;
	int			result_part_1;
	int			result_part_2;

	while (getline(cin, input)) {
		account_lines.emplace_back(stoi(input));
	}
	result_part_1 = multiply_matching_pair_that_sumup_into_2020(account_lines);
	cout << "Part 1 result : " << result_part_1 << endl;

	result_part_2 = multiply_matching_triple_that_sumup_into_2020(account_lines);
	cout  << "Part 2 result : " << result_part_2 << endl;
	return 0;
} 
