#ifndef DECL_H
#define DECL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <functional>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <io.h>
#include <direct.h>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

static std::chrono::steady_clock::time_point clockStart;
extern double accumulatedTime;

struct Studentas
{
	std::string vardas, pavarde;
	std::vector<int> nd;
	int egzaminas = 0;
	double galutinisVid = 0;
	double galutinisMed = 0;
};

struct palyginimas
{
	inline bool operator() (const Studentas& struct1, const Studentas& struct2)
	{
		return (struct1.pavarde.compare(struct2.pavarde)) < 0;
	}
};

void readFromFile(std::vector<Studentas>& studentai);
void readFromFileAutomated(std::vector<Studentas>& studentai, int studentuSkaicius, std::ifstream& input);
void inputStudent(std::vector<Studentas>& studentai);
void askForGeneration();
void generateFile(int numberOfStudents, std::ofstream& output);
void generateDirectories(std::string directory);
double findMedian(std::vector<int> grades, int n);
void writeToConsoleAvg(std::vector<Studentas>& studentai, std::ostream& out);
void writeToConsoleMed(std::vector<Studentas>& studentai, std::ostream& out);
void checkInput(int& skaicius, bool limited);
void checkInput(char& ivestis);

#endif
