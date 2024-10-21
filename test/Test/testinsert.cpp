#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

int	main(void) {
	string value="Helelo woerld";
	string::iterator it = find(value.begin(), value.end(), 'e');

	while (it != value.end()) {
		if (isspace(*(it - 1)) == false) {
			value.insert(it, ' ');
			it++;
		}
		if (isspace(*(it + 1)) == false)
			value.insert(it + 1, ' ');
		it = find(it + 1, value.end(), 'e');
	}
	cout << value << endl;
	return (0);
}
