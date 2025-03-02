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
void displayTable(vector<Album> albums);
void displayTable(Album album);
int dataSearchForAlbum(vector<Album> albums, string queryArtist);
vector<Album> dataSearchForArtist(vector<Album> ablums, string queryArtist);
vector<Album> dataSearchForLabel(vector<Album> albums, string queryLabel);
void userInputArtist(vector<Album> albums);

// Main function
int main() {
	vector<Album> albums = fileRead();
	displayTable(albums[dataSearchForAlbum(albums, "Nevermind")]);
	cout << endl;
	displayTable(dataSearchForArtist(albums, "Nirvana"));
	cout << endl;
	displayTable(dataSearchForLabel(albums, "Geffen"));
	cout << endl;
	userInputArtist(albums);
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

int dataSearchForAlbum(vector<Album> albums, string queryName) {
	int artistPos = -1;

	for (int i = 0; i < albums.size(); i++) {
		if (albums[i].name == "'" + queryName + "'") {
			artistPos = i;
			break;
		}
	}

	return artistPos;
}

vector<Album> dataSearchForArtist(vector<Album> albums, string queryArtist) {
	vector<Album> sortedAlbums;

	for (Album& album : albums) {
		if (album.artist == queryArtist) {
			sortedAlbums.push_back(album);
		}
	}

	return sortedAlbums;
}

vector<Album> dataSearchForLabel(vector<Album> albums, string queryLabel) {
	vector<Album> sortedAlbums;

	for (Album& album : albums) {
		if (album.label == queryLabel) {
			sortedAlbums.push_back(album);
		}
	}

	return sortedAlbums;
}

// Method that creates the table based off a vector
void displayTable(vector<Album> albums) {
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

// Display a single album instead of many
void displayTable(Album album) {
	string outStr;
  string paddedPosition = to_string(album.position);
  string paddedArtist = album.artist;
  string paddedName = album.name;
  string paddedLabel = album.label;

	outStr += " | " + tableHeaders[0].substr(0, 3) + " | " + tableHeaders[1] + "                 | " + tableHeaders[2] + "                       | " + tableHeaders[3] + "           | " + tableHeaders[4] + " | \n";
	outStr += " ============================================================================================\n | ";

	// Position formatting
	if (album.position < 10) {
		paddedPosition += "  ";
	} else if (album.position < 100) {
		paddedPosition += " ";
	}

	outStr += paddedPosition += " | ";

	// Artist formatting
	if (album.artist.length() >= 22) {
		paddedArtist = album.artist.substr(0, 20) + "..";
	} else {
		while (paddedArtist.length() < 22) {
			paddedArtist += " ";
		}
	}

	outStr += paddedArtist + " | ";

	// Album Name formatting
	if (album.name.length() >= 32) {
		paddedName = album.name.substr(0, 30) + "..";
	} else {
		while (paddedName.length() < 32) {
			paddedName += " ";
		}
	}

	outStr += paddedName + " | ";

	// Label formatting
	if (album.label.length() >= 15) {
		paddedLabel = album.label.substr(0, 13) + "..";
	} else {
		while (paddedLabel.length() < 15) {
			paddedLabel += " ";
		}
	}

	outStr += paddedLabel + " | ";

	outStr += to_string(album.year) + " |";
	cout << outStr << endl;
}

void userInputArtist(vector<Album> albums) {
	string input;
	cout << "[?] Artist name: ";
	cin >> input;

	displayTable(dataSearchForArtist(albums, input));
}