#include <string>
#include <iostream>
#include <time.h> 
#include <fstream>
#include <vector>

using namespace std;

int punkty_1; // gracz1
int punkty_2; // gracz2 
char odpowiedz; // a, b lub c
string pytania[21];

ifstream plik("pytania.txt");

// tu sa pytania

char odpowiedz_pytanie[21];

ifstream plik_1("odpowiedzi.txt");

// tu odpowiedzi

int miejsce; // wylosowany indeks pytania
int miejsce1;
int miejsce2;
int miejsce3;
// tu analogicznie az do ostatniego pytania(4 pytania)


vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

int main()
{
	for (int i = 0; i < 21; i++) {

		//plik >> pytania[i];
		getline(plik, pytania[i]);
	}
	for (int k = 0; k < 21; k++) {

		plik_1 >> odpowiedz_pytanie[k];
		//getline(plik_1, odpowiedz_pytanie[k]);
	}
	// quiz
	cout << "Wybrales Quiz, gracze odpowiadaja na 4 pytania, kto zgadnie wiecej ten zdobywa punkt, gracz 1 odpowiada jako pierwszy!\n";
	srand(time(NULL));

	miejsce = rand() % 22;
	cout << pytania[miejsce] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce]) {
		punkty_1++;
	}
	miejsce1 = rand() % 22;

	while (miejsce1 == miejsce) {
		miejsce1 = rand() % 22;
	}// zeby pytania sie nie powtarzaly

	cout << pytania[miejsce1] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce1]) {
		punkty_1++;
	}
	miejsce2 = rand() % 22;

	while (miejsce2 == miejsce1) {
		miejsce2 = rand() % 22;
	}

	cout << pytania[miejsce2] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce2]) {
		punkty_1++;
	}
	miejsce3 = rand() % 22;

	while (miejsce3 == miejsce2) {
		miejsce3 = rand() % 22;
	}

	cout << pytania[miejsce3] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce3]) {
		punkty_1++;
	}

	cout << "Gracz 1 zdobyl" << ' ' << punkty_1 << "punktow." << endl << "Teraz czas na pytania dla Gracza 2." << endl;

	// to samo tylko zmienione indeksy(Gracz2)

	srand(time(NULL));
	miejsce = rand() % 22;
	cout << pytania[miejsce] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce]) {
		punkty_2++;
	}
	miejsce1 = rand() % 22;

	while (miejsce1 == miejsce) {
		miejsce1 = rand() % 22;
	}// zeby pytania sie nie powtarzaly

	cout << pytania[miejsce1] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce1]) {
		punkty_2++;
	}
	miejsce2 = rand() % 22;

	while (miejsce2 == miejsce1) {
		miejsce2 = rand() % 22;
	}

	cout << pytania[miejsce2] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce2]) {
		punkty_2++;
	}
	miejsce3 = rand() % 22;

	while (miejsce3 == miejsce2) {
		miejsce3 = rand() % 22;
	}

	cout << pytania[miejsce3] << endl;
	cin >> odpowiedz;

	if (odpowiedz == odpowiedz_pytanie[miejsce3]) {
		punkty_2++;
	}


	ifstream savedPoints("data.txt");
	
	string saved;

	getline(savedPoints, saved);
	savedPoints.close();
	int pointsX = 0;
	int pointsO = 0;

	vector<string> v = split(saved, "=");

	pointsX = stoi(v.front());
	pointsO = stoi(v.back());
	

	cout << "Gracz 2 zdobyl" << ' ' << punkty_2 << "punktow." << endl << "Czas przekonac sie, kto wygral." << endl;

	if (punkty_1 > punkty_2) {
		pointsX++;
		cout << "Wygral Gracz 1!" << endl;
	}

	else {
		pointsO++;
		cout << "Wygral Gracz 2!" << endl;
	}

	string to_save = to_string(pointsX) + "=" + to_string(pointsO);

	ofstream saveFile;
	saveFile.open("data.txt");
	saveFile << to_save;
	saveFile.close();

	return 0;
}