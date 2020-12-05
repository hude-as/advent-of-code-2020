#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// part1
int count_password_policy1(vector<string> policy_password) {
	int result = 0;
	for (vector<string>::iterator it = policy_password.begin(); it != policy_password.end(); ++it) {
		stringstream ss(*it);
		string password;
		int min_occ, max_occ;
		char sep1, mandatory_letter, sep2;
		ss >> min_occ >> sep1 >> max_occ >> mandatory_letter >> sep2 >> password;

		size_t n = count(password.begin(), password.end(), mandatory_letter);
		if (n >= min_occ && n <= max_occ) {
			result += 1;
		}
	}
	return result;
}

// part2
int count_password_policy2(vector<string> policy_password) {
	int result = 0;
	for (vector<string>::iterator it = policy_password.begin(); it != policy_password.end(); ++it) {
		stringstream ss(*it);
		string password;
		int first_pos, second_pos;
		char sep1, mandatory_letter, sep2;
		ss >> first_pos >> sep1 >> second_pos >> mandatory_letter >> sep2 >> password;

		if ((password[first_pos - 1] == mandatory_letter && password[second_pos - 1] != mandatory_letter) \
				|| (password[first_pos - 1] != mandatory_letter && password[second_pos - 1] == mandatory_letter)) {
			result += 1;
		}
	}
	return result;
}

int main(int argc, char* argv[]) {
	string			input;
	vector<string>	policy_passwords;
	int				result_part_1;
	int				result_part_2;

	while (getline(cin, input)) {
		policy_passwords.emplace_back(input);
	}

	result_part_1 = count_password_policy1(policy_passwords);
	cout << result_part_1 << endl;
	
	result_part_2 = count_password_policy2(policy_passwords);
	cout << result_part_2 << endl;
	
	return 0;
} 

