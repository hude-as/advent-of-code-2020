#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int count_max_seat_id(vector<string> seats) {
	int max_seat_id = 0;

	for (vector<string>::iterator it = seats.begin(); it != seats.end(); ++it) {
		int seat_id = 0;
		string seat = *it;

		for (int i = 0; i < 7; ++i) {
			if (seat[i] == 'F') {
				
			} else {

			}
		}

		max_seat_id = max(max_seat_id, seat_id);
	}
	return max_seat_id;
}

int main(int argc, char* argv[]) {
	string			input;
	vector<string>	seats;
	int				result_part_1;
	int				result_part_2;

	while (getline(cin, input)) {
		seats.emplace_back(input);
	}

	result_part_1 = count_max_seat_id(seats);
	cout << result_part_1 << endl;
	
	result_part_2 = count_max_seat_id(seats);
	cout << result_part_2 << endl;
	
	return 0;
} 
