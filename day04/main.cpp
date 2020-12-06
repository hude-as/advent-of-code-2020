#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool is_password_correct_policy_1(vector<string> inputs) {
	map<string, bool> next_passport_policy;
	next_passport_policy["byr"] = false;
	next_passport_policy["iyr"] = false;
	next_passport_policy["eyr"] = false;
	next_passport_policy["hgt"] = false;
	next_passport_policy["hcl"] = false;
	next_passport_policy["ecl"] = false;
	next_passport_policy["pid"] = false;
	next_passport_policy["cid"] = false;

	for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
	    istringstream iss(*it);
		vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

		for (vector<string>::iterator word = tokens.begin(); word != tokens.end(); ++word) {
			string key = word->substr(0, 3);
			next_passport_policy[key] = true;
		}
	}
	if (next_passport_policy["byr"]
		&& next_passport_policy["iyr"]
		&& next_passport_policy["eyr"]
		&& next_passport_policy["hgt"] 
		&& next_passport_policy["hcl"] 
		&& next_passport_policy["ecl"]
		&& next_passport_policy["pid"]) {
			return true;
	}
	return false;
}

// byr (Birth Year) - four digits; at least 1920 and at most 2002.
bool policy_byr(string field) {
	int birth_year = stoi(field);
	return birth_year >= 1920 && birth_year <= 2002 && field.length() == 4;
}

// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
bool policy_iyr(string field) {
	int issue_year = stoi(field);
	return issue_year >= 2010 && issue_year <= 2020 && field.length() == 4;
}

// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
bool policy_eyr(string field) {
	int exp_year = stoi(field);
	return exp_year >= 2020 && exp_year <= 2030 && field.length() == 4;
}

// hgt (Height) - a number followed by either cm or in:
//		If cm, the number must be at least 150 and at most 193.
//		If in, the number must be at least 59 and at most 76.
bool policy_hgt(string field) {
	if (field.length() < 3)
		return false;
	int size = stoi(field);
	string end = field.substr(field.length() - 2);
	if (size >= 150 && size <= 193 && end == "cm" && field.length() == 5)
		return true;
	else if (size >= 59 && size <= 76 && end == "in" && field.length() == 4) {
		return true;
	}
	return false;
}

// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
bool policy_hcl(string field) {
	return (field[0] == '#'
    	&& field.length() == 7
    	&& field.find_first_not_of("0123456789abcdef", 1) == string::npos);
}

// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
bool policy_ecl(string field) {
	vector<string> valid_color = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	return (find(valid_color.begin(), valid_color.end(), field) != valid_color.end());
}

// pid (Passport ID) - a nine-digit number, including leading zeroes.
bool policy_pid(string field) {
	return (field.length() == 9 && field.find_first_not_of("0123456789") == string::npos);
}

bool policy_cid(string field) {
	return true;
}

bool is_password_correct_policy_2(vector<string> inputs) {
	map<string, bool> next_passport_policy;
	map<string, bool (*)(string)> field_policy;
	next_passport_policy["byr"] = false;
	next_passport_policy["iyr"] = false;
	next_passport_policy["eyr"] = false;
	next_passport_policy["hgt"] = false;
	next_passport_policy["hcl"] = false;
	next_passport_policy["ecl"] = false;
	next_passport_policy["pid"] = false;
	next_passport_policy["cid"] = false;

	field_policy["byr"] = &policy_byr;
	field_policy["iyr"] = &policy_iyr;
	field_policy["eyr"] = &policy_eyr;
	field_policy["hgt"] = &policy_hgt;
	field_policy["hcl"] = &policy_hcl;
	field_policy["ecl"] = &policy_ecl;
	field_policy["pid"] = &policy_pid;
	field_policy["cid"] = &policy_cid;

	for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
	    istringstream iss(*it);
		vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

		for (vector<string>::iterator word = tokens.begin(); word != tokens.end(); ++word) {
			string key = word->substr(0, 3);
			next_passport_policy[key] = field_policy[key](word->substr(4));
		}
	}
	if (next_passport_policy["byr"]
		&& next_passport_policy["iyr"]
		&& next_passport_policy["eyr"]
		&& next_passport_policy["hgt"] 
		&& next_passport_policy["hcl"] 
		&& next_passport_policy["ecl"]
		&& next_passport_policy["pid"]) {
		// for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
		// 	cout << *it << endl;
		// }
		// cout << endl;
			return true;
	}
	return false;
}

int count_valid_password_policy(vector<string> inputs, bool policy(vector<string>)) {
	int valid_password_count = 0;
	vector<string> password_inputs;

	for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
		if (*it == "") {
			valid_password_count += (int)policy(password_inputs);
			password_inputs.clear();
		} else {
			password_inputs.emplace_back(*it);
		}
	}
	valid_password_count += (int)policy(password_inputs);
	return valid_password_count;
}

int main(int argc, char* argv[]) {
	string			input;
	vector<string>	inputs;
	int				result_part_1;
	int				result_part_2;

	while (getline(cin, input)) {
		inputs.emplace_back(input);
	}

	result_part_1 = count_valid_password_policy(inputs, is_password_correct_policy_1);
	cout << result_part_1 << endl;
	
	result_part_2 = count_valid_password_policy(inputs, is_password_correct_policy_2);
	cout << result_part_2 << endl;
	
	return 0;
} 
