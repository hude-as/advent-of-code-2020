#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


// Start by considering the whole range, rows 0 through 127.
// F means to take the lower half, keeping rows 0 through 63.
// B means to take the upper half, keeping rows 32 through 63.
// F means to take the lower half, keeping rows 32 through 47.
// B means to take the upper half, keeping rows 40 through 47.
// B keeps rows 44 through 47.
// F keeps rows 44 through 45.
// The final F keeps the lower of the two, row 44.

// B means => 64 => 127
// 1, 2, 3, 4, 5, 6, 7, 8, .... 127
// BB means => 64 + 32 at least
// BBB means => 64 + 32 + 16
// BBBB means => 64 + 32 + 16 + 8
// BBBBB means => 64 + 32 + 16 + 8 + 4
// BBBBBB means => 64 + 32 + 16 + 8 + 4 + 2
// BBBBBBB means => 64 + 32 + 16 + 8 + 4 + 2 + 1 = 127

// in binary, its 1111111
// BBBBBBF means => 64 + 32 + 16 + 8 + 4 + 2 + 0 = 126
// BBBBBFB means => 64 + 32 + 16 + 8 + 4 + 0 + 1 = 125

// FFFFFFF means => 0
// FFFFFFB means => 1
// FFFFFBB means => 3
// FBFBBFF => 0101100 => 44


int get_seat_id(string seat) {
	string row_seat = seat.substr(0, 7);
	string col_seat = seat.substr(7);
	replace(row_seat.begin(), row_seat.end(), 'F', '0');
	replace(row_seat.begin(), row_seat.end(), 'B', '1');
	replace(col_seat.begin(), col_seat.end(), 'L', '0');
	replace(col_seat.begin(), col_seat.end(), 'R', '1');
	return stoi(row_seat, 0, 2) * 8 + stoi(col_seat, 0, 2);
}

int count_max_seat_id(vector<string> seats) {
	int max_seat_id = 0;

	for (vector<string>::iterator it = seats.begin(); it != seats.end(); ++it) {
		int seat_id = get_seat_id(*it);
		max_seat_id = max(max_seat_id, seat_id);
	}
	return max_seat_id;
}

int find_my_seat(vector<string> seats) {
	vector<int> plane;
	for (vector<string>::iterator it = seats.begin(); it != seats.end(); ++it) {
		int seat_id = get_seat_id(*it);
		plane.push_back(seat_id);
	}

	sort(plane.begin(), plane.end());
	// find first missing site with not empty seat around.
	for (vector<int>::iterator it = plane.begin(); it != plane.end() - 1; ++it) {
		if (*(it + 1) - *it == 2) {
			return *it + 1;
		}
	}
	return 0;
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
	
	result_part_2 = find_my_seat(seats);
	cout << result_part_2 << endl;
	
	return 0;
} 
