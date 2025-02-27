#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// This is the struct for each album on our entry
struct albumEntry {
	int position;
	string artist;
	string name;
	string label;
	int year;
};

vector<albumEntry> fileRead();

// Main function
int main() {
	//fileRead();
	dataSplit("6,Nirvana,'Nevermind',Geffen,1991")
	return 0;
};

// Make a function to read CSV and place data into a vector that uses the albumEntry type
vector<albumEntry> fileRead() {
	vector<albumEntry> albums;
	ifstream fin("albums.csv");

	if(fin) {
		string dataLine;
		while(getline(fin, dataLine)) {
			albumEntry albumData;

			for (int i = 0; i < curData.size(); i++) {
				cout << curData[i] << endl;
			}
		};
		fin.close();
	} else {
		cout << "Error opening file";
	};

	return albums;
};

// Method to split a string byt a comma
vector<string> dataSplit(string dataLine) {

}