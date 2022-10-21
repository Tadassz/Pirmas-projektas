#include "declarationss.h"

void readFromFile(vector<Studentas>& studentai)
{
	Studentas student;

	ifstream input;

	int pasirinkimas;

	cout << "Pasirinkite, kuri faila norite skaityti: "
		<< endl << "(1) studentai10000.txt"
		<< endl << "(2) studentai100000.txt"
		<< endl << "(3) studentai1000000.txt"
		<< endl << "(4) kursiokai.txt"
		<< endl;

	cout << "Jusu pasirinkimas: ";
	cin >> pasirinkimas;

	while (true)
	{
		switch (pasirinkimas)
		{
		case 1:
			input.open("studentai10000.txt");
			break;
		case 2:
			input.open("studentai100000.txt");
			break;
		case 3:
			input.open("studentai1000000.txt");
			break;
		case 4:
			input.open("kursiokai.txt");
			break;
		default:
			{
			cout << "Ivedete klaidinga reiksme! Pasirinkite skaiciu nuo 1 iki 4: ";
			cin >> pasirinkimas;
			continue;
			}
		}
		break;
	}


	input.ignore(256, '\n');

	while (!input.eof())
	{
		string line, vardas, pavarde;

		input >> vardas >> pavarde;
		getline(input, line);

		stringstream stream(line);
		vector<int> values;

		int n;
		while (stream >> n)
				values.push_back(n);

		values.pop_back();
		student.egzaminas = n;
		student.nd = values;
		student.vardas = vardas;
		student.pavarde = pavarde;
		studentai.push_back(student);
	}
	input.close();
}

void inputStudent(vector<Studentas>& studentai)
{
	Studentas stud;
	char pasirinkimas;
	int n;

	cout << "Iveskite studento varda: ";
	getline(cin, stud.vardas);

	cout << "Iveskite studento pavarde: ";
	getline(cin, stud.pavarde);

	cout << "Pradedami ivesti studento " << stud.vardas << " " << stud.pavarde << " duomenys."
		<< endl
			<< "Ar zinomas tikslus atliktu namu darbu skaicius? (T/N): ";

	cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{
		cout << "Iveskite studento atliktu namu darbu skaiciu: ";
		cin >> n;
		checkInput(n, false);

		cout << "Dabar yra suteikiama galimybe pasirinkti ivedima."
			<< " Duomenys vedami arba ranka, arba generuojami atsitiktinai."
				<< endl
					<< "Ar norite duomenis generuoti atsitiktinai? (T/N): ";

		cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			cout << "Pasirinkta duomenis generuoti atsitiktine tvarka.";

			for (int i = 0; i < n; i++)
				stud.nd.push_back(rand() % 10 + 1);

			stud.egzaminas = rand() % 10 + 1;

			cout << endl
				<< "Gauti pazymiai: ";
			for (int i = 0; i < stud.nd.size(); i++)
				cout << stud.nd[i] << " ";

			cout << endl
				<< "Gautas egzamino ivertinimas: "
					<< stud.egzaminas
						<< endl;
		}
		else if (tolower(pasirinkimas) == 'n')
		{
			cout << "Pasirinktas duomenu ivedimas ranka." <<
				endl;

			for (int i = 0; i < n; i++)
			{
				int ivestis;
				cout << "Iveskite " << i + 1 << "-aji pazymi: ";
				cin >> ivestis;
				checkInput(ivestis, true);
				stud.nd.push_back(ivestis);
			}
			cout << "Iveskite egzamino pazymi: ";
			cin >> stud.egzaminas;
			checkInput(stud.egzaminas, true);

			cout << "Baigtas duomenu ivedimas."
				<< endl;
		}
	}
	else if (tolower(pasirinkimas) == 'n')
	{
		cout << "Kadangi studento namu darbu skaicius nezinomas,"
			<< " atliekama ivestis rankiniu budu."
			<< endl;

		cout << "Noredami nutraukti pazymiu ivedima, pazymi suveskite 0."
			<< endl;

		while (true)
		{
			int ivestis;
			cout << "Iveskite " << stud.nd.size() + 1 << "-aji pazymi: ";
			cin >> ivestis;
			checkInput(ivestis, true);

			if (ivestis == 0 && stud.nd.size() > 0)
			{
				cout << "Iveskite egzamino pazymi: ";
				cin >> stud.egzaminas;
				checkInput(stud.egzaminas, true);
				break;
			}
			else if (ivestis == 0 && stud.nd.size() == 0)
				cout << "Studentas turi tureti bent viena pazymi!"
					<< endl;

			stud.nd.push_back(ivestis);
		}
	}
	studentai.push_back(stud);
}

void checkInput(int &skaicius, bool limited)
{
	while (cin.fail() || skaicius < 0 || skaicius > 10)
	{
		if(cin.fail())
			cout
				<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje skaiciaus ivedete raide?)"
					<< endl;

		else if (skaicius <= 0)
			cout
				<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti mazesne uz 0!)"
					<< endl;
		else if (skaicius > 10)
		{
			if (!limited) break;

			cout
				<< "Ivedete reiksme, netenkinancia salygos! (Skaicius negali buti didesnis uz 10!)"
					<< endl;
		}
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Pakartokite ivedima: ";
		cin >> skaicius;
	}
}

void checkInput(char& ivestis)
{
	while (cin.fail() || tolower(ivestis) != 't' && tolower(ivestis) != 'n')
	{
		if (cin.fail())
			cout
				<< "Ivedete reiksme, netenkinancia salygos! (Gal netycia vietoje raides ivedete skaiciu?)"
					<< endl;
		else if(tolower(ivestis) != 't' && tolower(ivestis) != 'n')
			cout
				<< "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)!"
				<< endl;

		cin.clear();
		cin.ignore(256, '\n');
		cout << "Pakartokite ivedima: ";
		cin >> ivestis;
	}
}
