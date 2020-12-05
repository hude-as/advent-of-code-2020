#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int count_tree_on_slope(vector<string>& topological_lines, int inc_count_right, int inc_count_bottom) {
	int tree_count = 0;
	int step_count_right = 0;
	int virtual_width = (int)topological_lines.front().length();

	for (int i = 0; i < topological_lines.size(); i += inc_count_bottom) {
		if (topological_lines[i][step_count_right % virtual_width] == '#') {
			tree_count += 1;
		}
		step_count_right += inc_count_right;
	}
	return tree_count;
}

int count_tree_on_slope_part_1(vector<string>& topological_lines) {
	return count_tree_on_slope(topological_lines, 3, 1);
}

long multiply_tree_on_all_slope_part_2(vector<string>& topological_lines) {
	int inc_count_rights[] = {1, 3, 5, 7, 1};
	int inc_count_bottoms[] = {1, 1, 1, 1, 2};
	long result = 1;
	for (int i = 0; i < 5; ++i) {
		result *= count_tree_on_slope(topological_lines, inc_count_rights[i], inc_count_bottoms[i]);
	}
	return result;
}

int main(int argc, char* argv[]) {
	string			input;
	vector<string>	topological_lines;
	int				result_part_1;
	long				result_part_2;

	while (getline(cin, input)) {
		topological_lines.emplace_back(input);
	}

	result_part_1 = count_tree_on_slope_part_1(topological_lines);
	cout << result_part_1 << endl;
	
	result_part_2 = multiply_tree_on_all_slope_part_2(topological_lines);
	cout << result_part_2 << endl;
	
	return 0;
} 
