#include "decl.h"
double accumulatedTime = 0;

int main()
{

	std::chrono::steady_clock::time_point programStart = std::chrono::steady_clock::now();
	std::istream::sync_with_stdio(false);
	std::ostream::sync_with_stdio(false);

	std::cout << "Atsakydami i programos uzduodamus klausimus rasykite raides T (-taip) arba N (-ne)."
		<< std::endl;

	std::vector<Studentas> studentai;
    std::list<Studentas> studentai_list;
	char pasirinkimas;

	std::cout << "Ar norite vykdyti spartos testavima? "
		<< "Pasirinkus ne, programa veiks iprasta eiga. (T/N): ";

	std::cin >> pasirinkimas;
	checkInput(pasirinkimas);

	if (tolower(pasirinkimas) == 't')
	{

		std::vector<int> studentuFailuDydziai = { 1000, 10000, 100000, 1000000, 10000000};

        std::ofstream output;
		std::ifstream input;

		generateDirectories("data");
		generateDirectories("data/input");
		generateDirectories("data/output");

		for (int i : studentuFailuDydziai)
		{
			double benchmarkTime = 0;
			std::cout << std::endl << "Pradedamas darbas su "
				<< i << " duomenimis.\n======================================================" << std::endl;

            // FAILU GENERAVIMAS
			clockStart = std::chrono::steady_clock::now();
			generateFile(i, output);
			std::cout << i << " studentu failo generavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
			benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // ================================================
            // VEIKSMAI SU VECTOR
            // ================================================

            std::cout << "Vykdomi veiksmai su VECTOR" << std::endl;
            clockStart = std::chrono::steady_clock::now();
			readFromFileAutomated(studentai, i, input);
            std::cout << "Duomenu nuskaitymas is failo naudojant VECTOR uztruko:" << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // SKAICIAVIMAS DUOMENU
			clockStart = std::chrono::steady_clock::now();
            studentai = avgAndMed(studentai);
            std::cout << "Duomenu apskaiciavimas su vector uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // RUSIAVIMAS DUOMENU
            std::vector<Studentas> kietiakai;
            std::vector<Studentas> vargsiukai;

			clockStart = std::chrono::steady_clock::now();
            sort_vector(studentai, kietiakai, vargsiukai);
			std::cout << "Duomenu rusiavimas su vector uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
			benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // DUOMENU ISVEDIMAS
            clockStart = std::chrono::steady_clock::now();
            output.open("data/output/kietiakai" + std::to_string(i) + ".txt");
            writeToFile(kietiakai, output);
            output.close();

            output.open("data/output/vargsiukai" + std::to_string(i) + ".txt");
            writeToFile(vargsiukai, output);
            output.close();
            std::cout << "Isvestis su vector truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // ================================================
            // VEIKSMAI SU LIST
            // ================================================
            std::cout << "Vykdomi veiksmai su LIST" << std::endl;

            clockStart = std::chrono::steady_clock::now();
            readFromFileAutomated_list(studentai_list, i, input);
            std::cout << "Vykdomas duomenu nuskaitymas is failo naudojant LIST uztruko:" << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // SKAICIAVIMAS DUOMENU
            std::list<Studentas> kietiakai_list;
            std::list<Studentas> vargsiukai_list;

            clockStart = std::chrono::steady_clock::now();
            studentai_list = avgAndMed_list(studentai_list);
            std::cout << "Duomenu apskaiciavimas su LIST uztrukoo: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // RUSIAVIMAS DUOMENU
            clockStart = std::chrono::steady_clock::now();
            sort_list(studentai_list, kietiakai_list, vargsiukai_list);
			std::cout << "Duomenu rusiavimas su LIST uztruko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

            // FAILU ISVEDIMAS
            clockStart = std::chrono::steady_clock::now();
            output.open("data/output/kietiakai_list" + std::to_string(i) + ".txt");
            writeToFile_list(kietiakai_list, output);
            output.close();

            output.open("data/output/vargsiukai_list" + std::to_string(i) + ".txt");
            writeToFile_list(vargsiukai_list, output);
            output.close();
            std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
            benchmarkTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();


            accumulatedTime += benchmarkTime;
            std::cout << "======================================================" << std::endl;
            std::cout << "Darbas su " << i << " duomenu failu is viso truko: " << benchmarkTime << " s" << std::endl;

        }
	}

	if (tolower(pasirinkimas) == 'n')
	{
		std::cout << "Ar norite vykdyti failu generacija? (T/N): ";
		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			askForGeneration();
		}
		else std::cout << "Pasirinkta failu negeneruoti. " << std::endl;

		std::cout << "Ar norite nuskaityti duomenis is failo? (T/N): ";
		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		bool nuskaitytiDuomenys = false;
		bool skaitytiToliau = false;

		if (tolower(pasirinkimas) == 't')
		{
			readFromFile(studentai);
			nuskaitytiDuomenys = true;

		}
		if (nuskaitytiDuomenys)
		{
			std::cout << "Ar norite duomenis taip pat ivesti ranka? (T/N): ";
			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 't')
				skaitytiToliau = true;
		}
		else
			std::cout << "Nepasirinkta duomenis skaityti is failo. Pereinama prie ivedimo rankiniu budu. "
			<< std::endl;

		while (skaitytiToliau || !nuskaitytiDuomenys)
		{
			std::cin.ignore();
			inputStudent(studentai);

			std::cout << "Ar norite prideti dar viena studenta? (T/N): ";
			std::cin >> pasirinkimas;

			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 'n')
				break;
		}

		std::cout << "Vykdomas galutiniu ivertinimu skaiciavimas." << std::endl;
		clockStart = std::chrono::steady_clock::now();
		for (auto & i : studentai)
		{
			double avg = 0;
			for (int j : i.nd)
			{
				avg += j;
			}
			avg /= i.nd.size();
			i.galutinisVid = 0.4 * avg + 0.6 * i.egzaminas;

			i.galutinisMed = findMedian(i.nd, i.nd.size()) * 0.4 + i.egzaminas * 0.6;
		}
		std::cout << "Galutiniu ivertinimu skaiciavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
		accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

		bool outputDone = false;
		std::cout << "Dabar yra suteikiama galimybe pasirinkti isvedima."
			<< std::endl;

		std::cout << "Ar norite, jog rezultatas butu skirstomas pagal galutini vidurki? "
			<< "Jei pasirinksite ne, jis bus neskirstomas. (T/N): ";

		std::cin >> pasirinkimas;
		checkInput(pasirinkimas);

		if (tolower(pasirinkimas) == 't')
		{
			std::vector<Studentas> kietiakai;
			std::vector<Studentas> vargsiukai;

            std::list<Studentas> kietiakai_list;
            std::list<Studentas> vargsiukai_list;

			outputDone = true;

			std::cout << "Pasirinkote surusiavima ir isvesti i faila."
				<< std::endl << "Ar norite, jog rezultatas isvedamas butu pagal galutini ivertinima? "
				<< "Pasirinkus ne, bus skaiciuojama pagal mediana. (T/N): ";

			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			generateDirectories("data");
			generateDirectories("data/output");

			if (tolower(pasirinkimas) == 't')
			{
				clockStart = std::chrono::steady_clock::now();
				for (auto & i : studentai)
				{
					if (i.galutinisVid >= 5.00)
						kietiakai.push_back(i);
					else
						vargsiukai.push_back(i);
				}
				std::cout << "Rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
				clockStart = std::chrono::steady_clock::now();
				std::ofstream output;

				output.open("data/output/kietiakai.txt");
                writeToFile(kietiakai, output);
				output.close();

				output.open("data/output/vargsiukai.txt");
                writeToFile(vargsiukai, output);
				output.close();

				std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}

			if (tolower(pasirinkimas) == 'n')
			{
				clockStart = std::chrono::steady_clock::now();
				for (auto & i : studentai)
				{
					if (i.galutinisMed >= 5)
						kietiakai.push_back(i);
					else
						vargsiukai.push_back(i);
				}
				std::cout << "Rusiavimas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();

				clockStart = std::chrono::steady_clock::now();
				std::ofstream output;

				output.open("data/output/kietiakai.txt");
                writeToFile(kietiakai, output);
				output.close();

				output.open("data/output/vargsiukai.txt");
                writeToFile(vargsiukai, output);
				output.close();

				std::cout << "Isvestis truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
		}

		if (tolower(pasirinkimas) == 'n' && !outputDone)
		{
			std::sort(studentai.begin(), studentai.end(), palyginimas());
			std::cout << "Pasirinkote paprasta isvesti i komandine eilute."
				<< std::endl << "Ar norite, jog rezultate butu rodomas vidurkis? "
				<< "Pasirinkus ne, bus rodoma mediana. (T/N): ";

			std::cin >> pasirinkimas;
			checkInput(pasirinkimas);

			if (tolower(pasirinkimas) == 't')
			{
				clockStart = std::chrono::steady_clock::now();
                writeToFile(studentai, std::cout);
				std::cout << "Israsymas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
			if (tolower(pasirinkimas) == 'n')
			{
				clockStart = std::chrono::steady_clock::now();
				writeToConsoleMed(studentai, std::cout);
				std::cout << "Israsymas truko: " << std::fixed << std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count() << "s" << std::endl;
				accumulatedTime += std::chrono::duration<double>(std::chrono::steady_clock::now() - clockStart).count();
			}
		}
	}
	std::cout << std::endl << "Galutinis vykdymas truko: " << accumulatedTime << " s." << std::endl;
	std::cout << "Galutinis programos gyvavimo laikas: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - programStart).count() << " s.";
}

