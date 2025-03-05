#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// This is the struct for each album on our entry
struct Album {
	int position;
	string artist;
	string name;
	string label;
	int year;
};

// Declaring our functions
vector<Album> fileRead();
vector<string> dataSplit(string dataLine);
int dataQueryForAlbum(vector<Album> albums, string artistQuery);
vector<Album> dataSearchForAlbums(vector<Album> albums, string albumQuery);
vector<Album> dataSearchForArtist(vector<Album> ablums, string artistQuery);
vector<Album> dataSortByArtist(vector<Album> albums);
vector<Album> dataSearchForLabel(vector<Album> albums, string labelQuery);
vector<Album> dataSortByYear(vector<Album> albums);
int dataReturnAvrgYear(vector<Album> albums);
void userMainMenu();
void userSearchMenu();
void userSortMenu();
void userSearchArtist(vector<Album> albums);
void userSearchAlbum(vector<Album> albums);
void userQueryAlbum(vector<Album> albums);
void userSearchLabel(vector<Album> albums);
void displayTable(vector<Album> albums);
void displayTable(Album album);
bool compareByYearDesc(Album &a, Album &b);
bool compareByArtistDesc(Album &a, Album &b);

// This is the header from the CSV, we will use it later
vector<string> tableHeaders;
vector<Album> albums;

// Main function
int main() {
	fileRead(); // This always needs to run first for the data to be placed into "albums"
	userMainMenu();
	return 0;
}

// Make a function to read CSV and place data into a vector that uses the Album type
vector<Album> fileRead() {
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

// Search a vector of albums, find one matching the given name
int dataQueryForAlbum(vector<Album> albums, string albumQuery) {
	int artistPos = -1;

	for (int i = 0; i < albums.size(); i++) {
		if (albums[i].name == "'" + albumQuery + "'") {
			artistPos = i;
			break;
		}
	}

	return artistPos;
}

vector<Album> dataSearchForAlbums(vector<Album> albums, string albumQuery) {
	vector<Album> selectedAlbums;

	for (auto a = albums.begin(); a != albums.end(); ++a) {
		if (a -> name.find(albumQuery) != string::npos) {
			selectedAlbums.push_back(*a);
		}
	}

	return selectedAlbums;
}

// Search a vector of albums, find what ones are made by the given artist
vector<Album> dataSearchForArtist(vector<Album> albums, string artistQuery) {
	vector<Album> sortedAlbums;

	for (Album& album : albums) {
		if (album.artist == artistQuery) {
			sortedAlbums.push_back(album);
		}
	}

	return sortedAlbums;
}

// Sorting artist by their names
vector<Album> dataSortByArtist(vector<Album> albums) {
	vector<Album> sortedAlbums = albums;
	sort(sortedAlbums.begin(), sortedAlbums.end(), compareByArtistDesc);
	return sortedAlbums;
}

// Search a vector of albums, find what ones are done by the given label
vector<Album> dataSearchForLabel(vector<Album> albums, string labelQuery) {
	vector<Album> sortedAlbums;

	for (Album& album : albums) {
		if (album.label == labelQuery) {
			sortedAlbums.push_back(album);
		}
	}

	return sortedAlbums;
}

// Sorting the years from newest to oldest
vector<Album> dataSortByYear(vector<Album> albums) {
	vector<Album> sortedAlbums = albums;
	sort(sortedAlbums.begin(), sortedAlbums.end(), compareByYearDesc); 
	return sortedAlbums;
}

// Return the average of all albums and the oldest and newest albums
int dataReturnAvrgYear(vector<Album> albums) {
	Album oldestAlbum;
	Album newestAlbum;
	int yearTotal = 0;

	// Set min years
	oldestAlbum.year = 9999;
	newestAlbum.year = 0;

	// Go through the albums
	for (Album& album : albums) {
		if (album.year > newestAlbum.year) {
			newestAlbum = album;
		}

		if (album.year < oldestAlbum.year) {
			oldestAlbum = album;
		}

		yearTotal += album.year;
	}

	// Return the average and "return" the 2 albums
	vector<Album> selectedAlbums = {newestAlbum, oldestAlbum};
	displayTable(selectedAlbums);
	return yearTotal / 500;
}

// Main menu
void userMainMenu() {
	string input;

	while (true) {
		cout << "[1] Display Table\n[2] Search Table\n[3] Sort Table\n[4] Display Year Stats\n: ";
		cin >> input;

		if (input == "1") {
			displayTable(albums);
		} else if (input == "2") {
			cout << "\n";
			userSearchMenu();
		} else if (input == "3") {
			cout << "\n";
			userSortMenu();
		} else if (input == "4") {
			cout << "[+] Average year: " << dataReturnAvrgYear(albums) << "\n\n";
		} else {
			cout << "\n[!] Invalid Input. Please enter a numbe from 1 to 3.\n\n";
		}
	}
}

// Search menu
void userSearchMenu() {
	string input;

	while (true) {
		cout << "[1] Search for an Artist\n[2] Search for an Album\n[3] Query for an Album\n[4] Search for an Label\n[5] Back\n: ";
		cin >> input;

		if (input == "1") {
			cout << "\n";
			userSearchArtist(albums);
		} else if (input == "2") {
			cout << "\n";
			userSearchAlbum(albums);
		} else if (input == "3") {
			cout << "\n";
			userQueryAlbum(albums);
		} else if (input == "4") {
			cout << "\n";
			userSearchLabel(albums);
		} else if (input == "5") {
			cout << "\n";
			userMainMenu();
		} else {
			cout << "\n[!] Invalid Input. Please enter a numbe from 1 to 5.\n\n";
		}
	}
}

// Sort menu
void userSortMenu() {
	string input;

	while (true) {
		cout << "[1] Sort by Artist\n[2] Sort by Year\n[3] Back\n: ";
		cin >> input;

		if (input == "1") {
			displayTable(dataSortByArtist(albums));
		} else if (input == "2") {
			displayTable(dataSortByYear(albums));
		} else if (input == "3") {
			cout << "\n";
			userMainMenu();
		} else {
			cout << "\n[!] Invalid Input. Please enter a numbe from 1 to 3.\n\n";
		}
	}
}

// Input for entering artists
void userSearchArtist(vector<Album> albums) {
	string input;
	cout << "[?] Artist name (must be exact): ";
	cin >> input;

	if (input.empty() != true) {
		displayTable(dataSearchForArtist(albums, input));
		userSearchMenu();
	} else {
		cout << "[!] Invalid Input. Please enter an album name.\n";
		userSearchMenu();
	}
}

void userSearchAlbum(vector<Album> albums) {
	string input;
	cout << "[?] Album search: ";
	cin >> input;

	if (input.empty() != true) {
		displayTable(dataSearchForAlbums(albums, input));
		userSearchMenu();
	} else {
		cout << "[!] Invalid Input. Please enter an album name.\n";
		userSearchMenu();
	}
}

void userQueryAlbum(vector<Album> albums) {
	string input;
	cout << "[?] Album query (must be exact): ";
	cin >> input;

	if (input.empty() != true) {
		displayTable(albums[dataQueryForAlbum(albums, input)]);
		userSearchMenu();
	} else {
		cout << "[!] Invalid Input. Please enter an album name.\n";
		userSearchMenu();
	}
}

void userSearchLabel(vector<Album> albums) {
	string input;
	cout << "[?] Label query (must be exact): ";
	cin >> input;

	if (input.empty() != true) {
		displayTable(dataSearchForLabel(albums, input));
		userSearchMenu();
	} else {
		cout << "[!] Invalid Input. Please enter an label name.\n";
		userSearchMenu();
	}
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

 	cout << endl;
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

// Sorting function for artists
bool compareByArtistDesc(Album &a, Album &b) {
	return a.artist < b.artist;
}

// Sorting function for years
bool compareByYearDesc(Album &a, Album &b) {
	return a.year > b.year;
}