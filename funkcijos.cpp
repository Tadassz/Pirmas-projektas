#include "decl.h"

auto nowForSeed = std::chrono::high_resolution_clock::now();
auto timeInMSForSeed = std::chrono::duration_cast<std::chrono::milliseconds>(nowForSeed.time_since_epoch()).count();

std::mt19937::result_type seed = timeInMSForSeed;
auto gradeGen = std::bind(std::uniform_int_distribution<int>(1, 10),
	std::mt19937(seed));

void readFromFile(std::vector<Studentas>& studentai)
{
	Studentas student;

	std::ifstream input;

	int pasirinkimas;

	std::cout << "Pasirinkite, kuri faila norite skaityti: "
		<< std::endl << "(1) studentai1000.txt"
		<< std::endl << "(2) studentai10000.txt"
		<< std::endl << "(3) studentai100000.txt"
		<< std::endl << "(4) studentai1000000.txt"
		<< std::endl << "(5) studentai10000000.txt"
		<< std::endl << "(6) kursiokai.txt"
		<< std::endl;

	std::cout << "Jusu pasirinkimas: ";
	std::cin >> pasirinkimas;

	try
	{
		while (true)
		{
			switch (pasirinkimas)
			{
			case 1:
				input.open("data/input/studentai1000.txt");
				break;
			case 2:
				input.open("data/input/studentai10000.txt");
				break;
			case 3:
				input.open("data/input/studentai100000.txt");
				break;
			case 4:
				input.open("data/input/studentai1000000.txt");
				break;
			case 5:
				input.open("data/input/studentai10000000.txt");
				break;
			case 6:
				input.open("data0/input/kursiokai.txt");
				break;
			default:
			{
				std::cout << "Ivedete klaidinga reiksme! Pasirinkite skaiciu nuo 1 iki 7: ";
				std::cin >> pasirinkimas;
				continue;
			}
			}
			break;
		}
		if (!input.good())
			throw 1;
	}
	catch (int err)
	{
		std::cout << "Pasirinktas failas nerastas! Programos veikla uzbaigiama.";
		exit(1);
	}

	clockStart = std::chrono::steady_clock::now();
	input.ignore(256, '\n');

	try
	{
		while (!input.eof())
		{

			std::string line, vardas, pavarde;

			input >> vardas >> pavarde;
			getline(input, line);

			std::stringstream stream(line);
			std::vector<int> values;

			int n;
			while (stream >> n)
			{
				values.push_back(n);
			}

			if (line.length() != 0)
			{
				values.pop_back();
				student.egzaminas = n;
				student.nd = values;
				student.vardas = vardas;
				student.pavarde = pavarde;
				studentai.push_back(student);
			}
		}
	}
	catch (std::bad_alloc& exception)
	{
		input.ignore(256, '\n');
		std::cout << "Programa aptiko klaidu faile! Tolimesnis sklandus veikimas negarantuojamas."
			<< std::endl;
	}

	input.close();

	std::cout << "Failo duomenys nuskaityti. "
		<< std::endl;
	std::cout << "Nuskaitymas uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
	accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
}

void readFromFileAutomated(std::vector<Studentas>& studentai, int studentuSkaicius, std::ifstream& input)
{
	Studentas student;

	std::string fileName = "studentai" + std::to_string(studentuSkaicius) + ".txt";
	input.open("data/input/" + fileName);
	input.ignore(256, '\n');

	try
	{
		while (!input.eof())
		{

			std::string line, vardas, pavarde;

			input >> vardas >> pavarde;
			getline(input, line);

			std::stringstream stream(line);
			std::vector<int> values;

			int n;
			while (stream >> n)
			{
				values.push_back(n);
			}

			if (line.length() != 0)
			{
				values.pop_back();
				student.egzaminas = n;
				student.nd = values;
				student.vardas = vardas;
				student.pavarde = pavarde;
				studentai.push_back(student);
			}
		}
	}
	catch (std::bad_alloc& exception)
	{
		input.ignore(256, '\n');
		std::cout << "Programa aptiko klaidu faile! Tolimesnis sklandus veikimas negarantuojamas."
			<< std::endl;
	}
	input.close();
}

void inputStudent(std::vector<Studentas>& studentai)
{
	Studentas stud;
	char pasirinkimas;
	int n;

	std::cout << "Iveskite studento varda: ";
	getline(std::cin, stud.vardas);

	std::cout << "Iveskite studento pavarde: ";
	getline(std::cin, stud.pavarde);

	std::cout << "Pradedami ivesti studento " << stud.vardas << " " << stud.pavarde << " duomenys."
		<< std::endl
		<< "Ar zinomas tikslus atliktu namu darbu skaicius? (T/N): ";

	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{
		std::cout << "Iveskite studento atliktu namu darbu skaiciu: ";
		std::cin >> n;
		checkInput(n, false);

		std::cout << "Dabar yra suteikiama galimybe pasirinkti ivedima."
			<< " Duomenys vedami arba ranka, arba generuojami atsitiktinai."
			<< std::endl
			<< "Ar norite duomenis generuoti atsitiktinai? (T/N): ";

		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			std::cout << "Pasirinkta duomenis generuoti atsitiktine tvarka.";

			for (int i = 0; i < n; i++)
				stud.nd.push_back(gradeGen());

			stud.egzaminas = gradeGen();

			std::cout << std::endl
				<< "Gauti pazymiai: ";
			for (int i = 0; i < stud.nd.size(); i++)
				std::cout << stud.nd[i] << " ";

			std::cout << std::endl
				<< "Gautas egzamino ivertinimas: "
				<< stud.egzaminas
				<< std::endl;
		}
		else if (tolower(pasirinkimas) == 'n')
		{
			std::cout << "Pasirinktas duomenu ivedimas ranka." <<
				std::endl;

			for (int i = 0; i < n; i++)
			{
				int ivestis;
				std::cout << "Iveskite " << i + 1 << "-aji pazymi: ";
				std::cin >> ivestis;
				checkInput(ivestis, true);
				stud.nd.push_back(ivestis);
			}
			std::cout << "Iveskite egzamino pazymi: ";
			std::cin >> stud.egzaminas;
			checkInput(stud.egzaminas, true);

			std::cout << "Baigtas duomenu ivedimas."
				<< std::endl;
		}
	}
	else if (tolower(pasirinkimas) == 'n')
	{
		std::cout << "Kadangi studento namu darbu skaicius nezinomas,"
			<< " atliekama ivestis rankiniu budu."
			<< std::endl;

		std::cout << "Noredami nutraukti pazymiu ivedima, pazymi suveskite 0."
			<< std::endl;

		while (true)
		{
			int ivestis;
			std::cout << "Iveskite " << stud.nd.size() + 1 << "-aji pazymi: ";
			std::cin >> ivestis;
			checkInput(ivestis, true);

			if (ivestis == 0 && stud.nd.size() > 0)
			{
				std::cout << "Iveskite egzamino pazymi: ";
				std::cin >> stud.egzaminas;
				checkInput(stud.egzaminas, true);
				break;
			}
			else if (ivestis == 0 && stud.nd.size() == 0)
				std::cout << "Studentas turi tureti bent viena pazymi!"
				<< std::endl;

			stud.nd.push_back(ivestis);
		}
	}
	studentai.push_back(stud);
}

void askForGeneration()
{
	char pasirinkimas;
	std::ofstream output;

	generateDirectories("data");
	generateDirectories("data/input");

	std::cout << "Ar norite generuoti 1 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(1000, output);
		std::cout << 1000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 10 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(10000, output);
		std::cout << 10000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 100 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(100000, output);
		std::cout << 100000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 1 000 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(1000000, output);
		std::cout << 1000000 << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
	}

	std::cout << "Ar norite generuoti 10 000 000 studentu faila? (T/N): ";
	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);
	if (tolower(pasirinkimas) == 't')
	{
		clockStart = std::chrono::steady_clock::now();
		generateFile(10000000, output);
	}
}

void generateDirectories(std::string directory)
{
	try
	{
		int dir = _mkdir(directory.c_str());

		if (dir == 0)
			std::cout << "Sukurta direktorija " + directory << "." << std::endl;
		else
			if (dir != 0 && errno == EEXIST)
			{
				std::cout << "Direktorija " + directory + " jau egzistuoja. Nieko nedaroma." << std::endl;
			}
		else throw(1);
	}
	catch (int err)
	{
		std::cout << "Ivyko klaida aplankalu kurimo metu! Programa nutraukia veikla.";
		exit(1);
	}
}

void generateFile(int numberOfStudents, std::ofstream& output)
{
	std::string fileName = "studentai" + std::to_string(numberOfStudents) + ".txt";
	output.open("data/input/" + fileName);
	output << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" ;

	int noOfHomework = 20;

	for (int i = 0; i < noOfHomework; i++)
	{
		output << std::setw(7) << "ND" + std::to_string(i + 1);
	}
	output << std::setw(7) << "Egz." << std::endl;

	for (int i = 0; i < numberOfStudents; i++)
	{
		int grades = gradeGen();
		output << std::setw(20) << "Vardas" + std::to_string(i + 1) << std::setw(20) << "Pavarde" + std::to_string(i + 1);

		for (int i = 0; i < noOfHomework; i++)
		{
			output << std::setw(7) << gradeGen();
		}
		output << std::setw(7) << gradeGen();
		if(i != numberOfStudents - 1) output << std::endl;
	}
	output.close();
}

double findMedian(std::vector<int> grades, int n)
{
	if (n % 2 == 0) {

		nth_element(grades.begin(), grades.begin() + n / 2, grades.end());

		nth_element(grades.begin(), grades.begin() + (n - 1) / 2, grades.end());

		return (double)(grades[(n - 1) / 2] + grades[n / 2]) / 2.0;
	}
	else {
		nth_element(grades.begin(), grades.begin() + n / 2, grades.end());
		return (double)grades[n / 2];
	}
}

void writeToConsoleAvg(std::vector<Studentas>& studentai, std::ostream& out)
{
	out << std::left
		<< std::setw(20) << "Pavarde"
		<< std::setw(15) << "Vardas"
		<< std::setw(10) << "Galutinis " << "(Vid.)" << "\n"
		<< std::string(65, '-')
		<< "\n";

	for (int i = 0; i < studentai.size(); i++)
	{
		out << std::left
			<< std::setw(20) << studentai[i].pavarde
			<< std::setw(15) << studentai[i].vardas
			<< std::setw(15) << std::fixed << std::setprecision(2) << studentai[i].galutinisVid
			<< "\n";
	}
}

void writeToConsoleMed(std::vector<Studentas>& studentai, std::ostream& out)
{
	out << std::left
		<< std::setw(20) << "Pavarde"
		<< std::setw(15) << "Vardas"
		<< std::setw(10) << "Galutinis " << "(Med.)" << "\n"
		<< std::string(65, '-')
		<< "\n";

	for (int i = 0; i < studentai.size(); i++)
	{
		out << std::left
			<< std::setw(20) << studentai[i].pavarde
			<< std::setw(15) << studentai[i].vardas
			<< std::setw(15) << std::fixed << std::setprecision(2) << studentai[i].galutinisMed
			<< "\n";
	}
}

void checkInput(int& skaicius, bool limited)
	{
		while (std::cin.fail() || skaicius < 0 || skaicius > 10)
		{
			if (std::cin.fail())
				std::cout
				<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje skaiciaus ivedete raide?)"
				<< std::endl;

			else if (skaicius <= 0)
				std::cout
				<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti mazesne uz 0!)"
				<< std::endl;
			else if (skaicius > 10)
			{
				if (!limited) break;

				std::cout
					<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti didesnis uz 10!)"
					<< std::endl;
			}
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Pakartokite ivedima: ";
			std::cin >> skaicius;
		}
	}

void checkInput(char& ivestis)
{
	while (std::cin.fail() || tolower(ivestis) != 't' && tolower(ivestis) != 'n')
	{
		if (std::cin.fail())
			std::cout
			<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje raides ivedete skaiciu?)"
			<< std::endl;
		else if (tolower(ivestis) != 't' && tolower(ivestis) != 'n')
			std::cout
			<< "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)!"
			<< std::endl;

		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Pakartokite ivedima: ";
		std::cin >> ivestis;
	}
}

