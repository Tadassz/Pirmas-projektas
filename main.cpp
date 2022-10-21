#include "declarationss.h"

int main()
{
ofstream isvedimoFailas("results.txt");
	cout << "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)."
		<< endl;

	vector<Studentas> studentai;
	char pasirinkimas;

	cout << "Ar norite nuskaityti duomenis is failo? (T/N): ";
	cin >> pasirinkimas;
	checkInput(pasirinkimas);

	bool nuskaitytiDuomenys = false;
	bool skaitytiToliau = false;

	if(tolower(pasirinkimas) == 't')
	{
		readFromFile(studentai);
		nuskaitytiDuomenys = true;
		cout << "Failo duomenys nuskaityti. "
			<< endl;
	}
	if (nuskaitytiDuomenys)
	{
		cout << "Ar norite duomenis taip pat ivesti ranka? (T/N): ";
		cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
			skaitytiToliau = true;
	}
	else
		cout << "Nepasirinkta duomenis skaityti is failo. Pereinama prie ivedimo rankiniu budu. "
			<< endl;

	while (skaitytiToliau || !nuskaitytiDuomenys)
	{
		cin.ignore();
		inputStudent(studentai);

		cout << "Ar norite prideti dar viena studenta? (T/N): ";
		cin >> pasirinkimas;

		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 'n')
			break;
	}
	cout << "Dabar yra suteikiama galimybe pasirinkti isvedima."
		<< endl;

	cout << "Ar norite, jog rezultatas butu vidurkis? "
		<< "Jei pasirinksite ne, bus rodoma mediana. (T/N): ";
	cin >> pasirinkimas;
	checkInput(pasirinkimas);

	sort(studentai.begin(), studentai.end(), palyginimas());

	if (tolower(pasirinkimas) == 't')
	{
		isvedimoFailas << left
			<< setw(20) << "Pavarde"
			<< setw(15) << "Vardas"
			<< setw(10) << "Galutinis (Vid.)"
			<< endl
			<< string(65, '-')
			<< endl;

		for (int i = 0; i < studentai.size(); i++)
		{
			double avg = 0;

			for (int j = 0; j < studentai[i].nd.size(); j++)
				avg += studentai[i].nd[j];

			avg = avg / studentai[i].nd.size();
			avg = 0.4 * avg + 0.6 * studentai[i].egzaminas;

			isvedimoFailas << left
				<< setw(20) << studentai[i].pavarde
				<< setw(15) << studentai[i].vardas
				<< setw(15) << fixed << setprecision(2) << avg
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

		for (int i = 0; i < studentai.size(); i++)
		{
			sort(studentai[i].nd.begin(), studentai[i].nd.end());

			double median = 0;

			if (studentai[i].nd.size() % 2 == 1)
				median = studentai[i].nd[studentai[i].nd.size() / 2];

			else median = ((double)studentai[i].nd[studentai[i].nd.size() / 2] + (double)studentai[i].nd[studentai[i].nd.size() / 2 - 1]) / 2;

			double final = median * 0.4 + studentai[i].egzaminas * 0.6;
			cout << left
				<< setw(20) << studentai[i].pavarde
				<< setw(15) << studentai[i].vardas
				<< setw(15) << fixed << setprecision(2) << final
				<< endl;
		}

	}
	WINPAUSE;
}
