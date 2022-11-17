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
#include <list>
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
void readFromFileAutomated_list(std::list<Studentas>& studentai, int studentuSkaicius, std::ifstream& input);
void inputStudent(std::vector<Studentas>& studentai);
void askForGeneration();
void generateFile(int numberOfStudents, std::ofstream& output);
void generateDirectories(std::string directory);
double findMedian(std::vector<int> grades, int n);
void writeToFile(std::vector<Studentas>& studentai, std::ostream& out);
void writeToFile_list(std::list<Studentas>& studentai, std::ostream& out);
void writeToConsoleMed(std::vector<Studentas>& studentai, std::ostream& out);
void checkInput(int& skaicius, bool limited);
void checkInput(char& ivestis);
std::list<Studentas> avgAndMed_list(std::list<Studentas> studentai_list);
std::vector<Studentas> avgAndMed(std::vector<Studentas> studentai);
void sort_vector(std::vector<Studentas> &studentai, std::vector<Studentas> &kietiakai, std::vector<Studentas> &vargsiukai);
void sort_list(std::list<Studentas> &studentai_list, std::list<Studentas> &kietiakai_list, std::list<Studentas> &vargsiukai_list);
bool compareTwoStudents(Studentas a, Studentas b);


#endif

