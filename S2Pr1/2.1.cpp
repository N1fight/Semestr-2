#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Encryption {
private:
	string a[20];
	int c = 0;
public:

	void Encode() {
		string str;
		int b = 0;
		getline(cin, str);

		for (int i = 0; i < str.size(); i++) {
			string g = "";
			g = g + str[i];
			if ((g.compare(" ") == 0)) {
				string test = "";
				for (int j = b; j < i; j++) {
					test = test + str[j];
				}
				a[c] = test;
				c = c + 1;
				b = i + 1;
			}
		}
		string test = "";
		for (int j = b; j < str.size(); j++) {
			test = test + str[j];
		}
		a[c] = test;
		c = c + 1;

		//for (int i = 0; i < 20; i++) {
			//cout << a[i] << "|";
		//}

	};


	void Decode() {
		int fibonachi[20]{ 1, 2, 3, 5, 8, 13, 21, 43,
		55, 89, 144, 233, 377, 610, 987, 1597, 2584,
		4191, 6765, 10946 };

		int* password = new int[c];

		for (int i = 0; i < c; i++) {
			cin >> password[i];
		}

		//for (int i = 0; i < c; i++) {
			//cout << password[i] << endl;
		//}

		for (int i = 0; i < c; i++) {
			for (int j = 0; j < 20; j++) {
				if (password[i] == fibonachi[j]) {
					cout << a[j] << " ";
				}

			}
		}

		delete[] password;


	};
};

int main() {
	Encryption Encryption;
	Encryption.Encode();
	Encryption.Decode();
	// Hello, my name is Ivan




	return 0;
};