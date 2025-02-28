#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// This is the struct for each album on our entry
struct Album {
	int position;
	string artist;
	string name;
	string label;
	int year;
};

vector<string> tableHeaders;

vector<Album> fileRead();
vector<string> dataSplit(string dataLine);
void dataDisplayTable(vector<Album> albums);

// Main function
int main() {
	vector<Album> albums = fileRead();
	dataDisplayTable(albums);
	return 0;
}

// Make a function to read CSV and place data into a vector that uses the Album type
vector<Album> fileRead() {
	vector<Album> albums;
	ifstream fin("albums.csv");

	if(fin) {
		string dataLine;

		// Storing the header line for use displaying later
		if(getline(fin, dataLine)) {
			tableHeaders = dataSplit(dataLine);
		}

		while(getline(fin, dataLine)) {
			Album albumData;
			vector<string> dataElements = dataSplit(dataLine);

			albumData.position = stoi(dataElements[0]);
			albumData.artist = dataElements[1];
			albumData.name = dataElements[2];
			albumData.label = dataElements[3];
			albumData.year = stoi(dataElements[4]);

			albums.push_back(albumData);
		}
		fin.close();
	} else {
		cout << "Error opening file";
	}

	return albums;
}

// Method to split a string byt a comma
vector<string> dataSplit(string dataLine) {
	vector<string> dataVec;

	while(dataLine.find(",") != string::npos) {
		string dataElement = dataLine.substr(0, dataLine.find(','));
		dataVec.push_back(dataElement);
		dataLine = dataLine.substr(dataLine.find(',') + 1);
	}

	dataVec.push_back(dataLine);
	return dataVec;
}

// Method that creates the table to be displayed to the user in the CLI
void dataDisplayTable(vector<Album> albums) {
	cout << " | " << tableHeaders[0].substr(0, 3) << " | " << tableHeaders[1] << "                 | " << tableHeaders[2] << "                       | " << tableHeaders[3] << "           | " << tableHeaders[4] << " | " << endl;
	cout << " ============================================================================================" << endl;

	for (int i = 0; i < albums.size(); i++) {
  	string outStr = " | ";
  	string paddedPosition = to_string(albums[i].position);
  	string paddedArtist = albums[i].artist;
  	string paddedName = albums[i].name;
  	string paddedLabel = albums[i].label;

  	// Position formatting
  	if (albums[i].position < 10) {
  		paddedPosition += "  ";
  	} else if (albums[i].position < 100) {
  		paddedPosition += " ";
  	}

  	outStr += paddedPosition += " | ";

  	// Artist formatting
  	if (albums[i].artist.length() >= 22) {
  		paddedArtist = albums[i].artist.substr(0, 20) + "..";
  	} else {
  		while (paddedArtist.length() < 22) {
  			paddedArtist += " ";
  		}
  	}

  	outStr += paddedArtist + " | ";

  	// Album Name formatting
  	if (albums[i].name.length() >= 32) {
  		paddedName = albums[i].name.substr(0, 30) + "..";
  	} else {
  		while (paddedName.length() < 32) {
  			paddedName += " ";
  		}
  	}

  	outStr += paddedName + " | ";

  	// Label formatting
  	if (albums[i].label.length() >= 15) {
  		paddedLabel = albums[i].label.substr(0, 13) + "..";
  	} else {
  		while (paddedLabel.length() < 15) {
  			paddedLabel += " ";
  		}
  	}

  	outStr += paddedLabel + " | ";

  	outStr += to_string(albums[i].year) + " |";
  	cout << outStr << endl;
 	}
}