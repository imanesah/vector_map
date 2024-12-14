#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>
using namespace std;
using namespace std;
using namespace std::chrono;
int main() {
    string nomFichier = "monFichier.txt";
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return 1;
    }

    map<string, int> dictionnaire; 
    vector<string> mots;
    string mot;

  
    while (fichier >> mot) {
        dictionnaire[mot]++; 
        mots.push_back(mot);
    }

   
    
    fichier.close();

    string nomFichierDictionnaire = "dictionnaire.txt";
    ifstream fichierDictionnaire(nomFichierDictionnaire);
    map<string, string> definitions; 
    if (fichierDictionnaire.is_open()) {
        string ligne;
        while (getline(fichierDictionnaire, ligne)) {
            size_t delimPos = ligne.find(':');
            if (delimPos != string::npos) {
                string mot = ligne.substr(0, delimPos); 
                string signification = ligne.substr(delimPos + 1); 
                definitions[mot] = signification;
            }
        }
        fichierDictionnaire.close();
    }
    else {
        cout << "Erreur : Impossible d'ouvrir le fichier dictionnaire.txt" << endl;
    }
    int choix;
    do {
        cout << "\n********** MENU **********\n";
        cout << "1. Voir le contenu du vecteur\n";
        cout << "2. Chercher un mot\n";
        cout << "3. Supprimer un mot\n";
        cout << "4. utiliser dictionnaire pour voir les occurencces \n";
        cout << "5. Trier le vecteur\n";
        cout << "6. Rechercher la signification d'un mot (dictionnaire map )  \n";
        cout << "7. Quitter\n";
        
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
        case 1: { 
            auto debut = high_resolution_clock::now(); 
            cout << "\n********** Contenu du vecteur **********\n";
            for (const auto& mot : mots) {
                cout << mot << " ";
            }
            cout << endl;

            auto fin = high_resolution_clock::now(); 
            auto duree = duration_cast<duration<double>>(fin - debut).count(); 
            cout << "Temps d'exécution : " << duree << " secondes.\n";

            break;
        }
        case 2: { 

            cout << "Entrez un mot à rechercher : ";
            string motRecherche;
            cin >> motRecherche;
            auto debut = high_resolution_clock::now();
            auto it = find(mots.begin(), mots.end(), motRecherche);
            if (it != mots.end()) {
                int nbOccurrences = count(mots.begin(), mots.end(), motRecherche);
                cout << "Le mot '" << motRecherche << "' a été trouvé avec " << nbOccurrences << " occurrence(s)." << endl;
            }
            else {
                cout << "Le mot '" << motRecherche << "' n'existe pas dans le vecteur." << endl;
            }

            auto fin = high_resolution_clock::now(); 
            auto duree = duration_cast<duration<double>>(fin - debut).count(); 
            cout << "Temps d'exécution : " << duree << " secondes.\n";
            break;
        }
        case 3: { 
            cout << "Entrez un mot à supprimer : ";
            string motASupprimer;
            cin >> motASupprimer;
            auto debut = high_resolution_clock::now();
            auto it = find(mots.begin(), mots.end(), motASupprimer);
            if (it != mots.end()) {
                cout << "Voulez-vous vraiment supprimer le mot '" << motASupprimer << "' ? (o/n) : ";
                char confirmation;
                cin >> confirmation;

                if (confirmation == 'o' || confirmation == 'O') {
                    mots.erase(remove(mots.begin(), mots.end(), motASupprimer), mots.end());
                    cout << "Le mot '" << motASupprimer << "' a été supprimé." << endl;
                }
                else {
                    cout << "Suppression annulée." << endl;
                }
            }
            else {
                cout << "Le mot '" << motASupprimer << "' n'existe pas dans le vecteur." << endl;
            }

            auto fin = high_resolution_clock::now(); 
            auto duree = duration_cast<duration<double>>(fin - debut).count(); 
            cout << "Temps d'exécution : " << duree << " secondes.\n";
            break;
        }
        case 4: { 
            cout << "Entrez le mot  : ";
            string motATraduire;
            cin >> motATraduire;
            auto debut = high_resolution_clock::now();

            if (dictionnaire.find(motATraduire) != dictionnaire.end()) {
                cout << "Le mot '" << motATraduire << "' existe avec "
                    << dictionnaire[motATraduire] << " occurrence(s)." << endl;
                cout << "voullez-vous voir le dictionnaire : ";
                char affichedictionnaire;
                cin >> affichedictionnaire;

                if (affichedictionnaire == 'o' || affichedictionnaire == 'O') {
                    for (const auto& entry : dictionnaire) {
                        cout << entry.first << " : " << entry.second << endl;
                    }
                }
             
                else {
                    break;
                }

            }
            else {
                cout << "Le mot '" << motATraduire << "' n'est pas disponible dans le dictionnaire." << endl;
            }

            auto fin = high_resolution_clock::now(); 
            auto duree = duration_cast<duration<double>>(fin - debut).count(); 
            cout << "Temps d'exécution : " << duree << " secondes.\n";
            break;
        }
        case 5: {
            cout << "Tri en cours...\n";
            auto debut = high_resolution_clock::now();
            sort(mots.begin(), mots.end());
            cout << "Le vecteur a été trié.\n";
            cout << "Voulez-vousvoir le vector trie  ? (o/n) : ";
            char confirmation;
            cin >> confirmation;

            if (confirmation == 'o' || confirmation == 'O') {
                for (const auto& mot : mots) {
                    cout << mot << endl;
                }
            }
            else if (confirmation == 'n' || confirmation == 'N') {
                cout << "Le vecteur a été trié.\n";
            }
            else {
                cout << "Choix invalide " << endl;
            }

            auto fin = high_resolution_clock::now(); 
            auto duree = duration_cast<duration<double>>(fin - debut).count(); 
            cout << "Temps d'exécution : " << duree << " secondes.\n";
            break;
        }
        case 6 :{
            cout << "Entrez un mot pour voir sa signification : ";
            string motCherche;
            cin >> motCherche;

            auto debut = high_resolution_clock::now();

            // Rechercher dans la map 'definitions'
            auto it = definitions.find(motCherche);
            if (it != definitions.end()) {
                cout << "Signification de '" << motCherche << "': " << it->second << endl;
            }
            else {
                cout << "Le mot '" << motCherche << "' n'existe pas dans le dictionnaire." << endl;
            }

            auto fin = high_resolution_clock::now();
            auto duree = duration_cast<duration<double>>(fin - debut).count();
            cout << "Temps d'exécution : " << duree << " secondes.\n";

            break;
        }
        case 7: {
            cout << "Au revoir !" << endl;

            
            break;
        }
        default:
            cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 7);

    return 0;
}
