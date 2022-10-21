#ifndef DECLARATIONSS_H
#define DECLARATIONSS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <functional>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

using std::string;
using std::vector;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;
using std::sort;
using std::setprecision;
using std::setw;
using std::fixed;
using std::left;
using std::ifstream;
using std::stringstream;



struct Studentas {

	string vardas, pavarde;
	vector<int> nd;
	int egzaminas = 0;

};



struct palyginimas
{
	inline bool operator() (const Studentas& struct1, const Studentas& struct2)
	{
		return (struct1.pavarde.compare(struct2.pavarde)) < 0;
	}
};

void readFromFile(vector<Studentas>& studentai);
void inputStudent(vector<Studentas>& studentai);
void checkInput(int& skaicius, bool limited);
void checkInput(char& ivestis);

#endif
