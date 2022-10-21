#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#define WINPAUSE system("pause")
#endif

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::left;
using std::setprecision;
using std::sort;




struct Studentas {

	string vardas, pavarde;
	int n = 0;
	int* nd = 0;
	int egzaminas = 0;

};

void inputStudent(Studentas& studentai);
void checkInput(int& skaicius, bool limited);
void checkInput(char& ivestis);

int main()
{
	srand(time(NULL));

	cout << "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)."
		<< endl;

	int studentu = 0;
	Studentas* studentai = new Studentas[studentu + 1];

	char pasirinkimas;

	while (true)
	{
		inputStudent(studentai[studentu]);

		studentu++;

		cout << "Ar norite prideti dar viena studenta? (T/N): ";
		cin >> pasirinkimas;
		cin.ignore();

		if (tolower(pasirinkimas) == 'n')
			break;
		else
		{
			Studentas* studentai_didesnis = new Studentas[studentu + 1];

			for (int i = 0; i < studentu; i++)
				studentai_didesnis[i] = studentai[i];

			delete[] studentai;
			studentai = studentai_didesnis;
		}
	}

	cout << "Dabar yra suteikiama galimybe pasirinkti isvedima."
		<< endl;

	cout << "Ar norite, jog rezultatas butu vidurkis? "
		<< "Jei pasirinksite ne, bus rodoma mediana. (T/N): ";
	cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{
		cout << left
			<< setw(20) << "Pavarde"
			<< setw(15) << "Vardas"
			<< setw(10) << "Galutinis (Vid.)"
			<< endl
			<< string(65, '-')
			<< endl;

		for (int i = 0; i < studentu; i++)
		{
			double avg = 0;

			for (int j = 0; j < studentai[i].n; j++)
				avg += studentai[i].nd[j];

			avg /= studentai[i].n;
			avg = 0.4 * avg + 0.6 * studentai[i].egzaminas;

			cout << left
				<< setw(20) << studentai[i].pavarde
				<< setw(15) << studentai[i].vardas
				<< setw(15) << setprecision(2) << avg
				<< endl;

		}
	}
	else
	{
		cout << left
			<< setw(20) << "Pavarde"
			<< setw(15) << "Vardas"
			<< setw(10) << "Galutinis (Med.)"
			<< endl
			<< string(65, '-')
			<< endl;

		for (int i = 0; i < studentu; i++)
		{
			sort(studentai[i].nd, studentai[i].nd + studentai[i].n);

			double median = 0;

			if (studentai[i].n % 2 == 1)
				median = studentai[i].nd[studentai[i].n / 2];

			else median = ((double)studentai[i].nd[studentai[i].n / 2] + (double)studentai[i].nd[studentai[i].n / 2 - 1]) / 2;

			cout << left
				<< setw(20) << studentai[i].pavarde
				<< setw(15) << studentai[i].vardas
				<< setw(15) << setprecision(2) << median
				<< endl;
		}

	}
	delete[] studentai;
	WINPAUSE;
}

void inputStudent(Studentas& studentai)
{
	string vardas, pavarde;
	int n = 0, egzaminas{};
	bool looped = false;

	int* nd = new int[n+1];
	char pasirinkimas;

	cout << "Iveskite studento varda: ";
	getline(cin, vardas);

	cout << "Iveskite studento pavarde: ";
	getline(cin, pavarde);

	cout << "Pradedami ivesti studento " << vardas << " " << pavarde << " duomenys."
		<< endl
			<< "Ar zinomas tikslus atliktu namu darbu skaicius? (T/N): ";

	cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{
		cout << "Iveskite studento atliktu namu darbu skaiciu: ";
		cin >> n;
		checkInput(n, false);

		delete[] nd;
		nd = new int[n];

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
				nd[i] = rand() % 10 + 1;

			egzaminas = rand() % 10 + 1;

			cout << endl
				<< "Gauti pazymiai: ";
			for (int i = 0; i < n; i++)
				cout << nd[i] << " ";

			cout << endl
				<< "Gautas egzamino ivertinimas: "
					<< egzaminas
						<< endl;
		}
		else if (tolower(pasirinkimas) == 'n')
		{
			cout << "Pasirinktas duomenu ivedimas ranka." <<
				endl;

			for (int i = 0; i < n; i++)
			{
				cout << "Iveskite " << i + 1 << "-aji pazymi: ";
				cin >> nd[i];
				checkInput(nd[i], true);
			}

			cout << "Iveskite egzamino pazymi: ";
			cin >> egzaminas;
			checkInput(egzaminas, true);

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
			cout << "Iveskite " << n + 1 << "-aji pazymi: ";
			cin >> nd[n];
			checkInput(nd[n], true);

			if (nd[n] == 0 && n > 0)
			{
				cout << "Iveskite egzamino pazymi: ";
				cin >> egzaminas;
				checkInput(egzaminas, true);
				break;
			}

			else if (nd[n] == 0 && n == 0)
				cout << "Studentas turi tureti bent viena pazymi!"
					<< endl;

			else
			{
				n++;

				int* nd_didesnis = new int[n + 1];

				for (int i = 0; i < n; i++)
					nd_didesnis[i] = nd[i];

				delete[] nd;
				nd = nd_didesnis;
			}

		}

	}

	studentai.vardas = vardas;
	studentai.pavarde = pavarde;
	studentai.n = n;
	studentai.nd = nd;
	studentai.egzaminas = egzaminas;

}

void checkInput(int &skaicius, bool limited) {

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

void checkInput(char& ivestis) {

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
