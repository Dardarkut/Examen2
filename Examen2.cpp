#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <limits>
#include <cctype>

using namespace std;

struct Candidate {
    string name;
    string party;
    string platform;
    int votes = 0;
};

vector<Candidate> candidates;
set<string> voterIDs;

//Validacion si es numerico
bool isDigit(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

//Validacion si es string
bool isString(const string& input) {
    for (char c : input) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

//Funcion de registro de cantidato
void registerCandidate() {
    Candidate newCandidate;

    do {
        cout << "Ingrese nombre completo del candidato: ";
        cin.ignore();
        getline(cin, newCandidate.name);
        if (!isString(newCandidate.name)) {
            cout << "Error: El nombre solo debe contener letras.\n";
        }
    } while (!isString(newCandidate.name));

    do {
        cout << "Ingrese partido del candidato: ";
        getline(cin, newCandidate.party);
        if (!isString(newCandidate.party)) {
            cout << "Error: El partido solo debe contener letras.\n";
        }
    } while (!isString(newCandidate.party));

    do {
        cout << "Ingrese plataforma del candidato: ";
        getline(cin, newCandidate.platform);
        if (!isString(newCandidate.platform)) {
            cout << "Error: La plataforma solo debe contener letras.\n";
        }
    } while (!isString(newCandidate.platform));

    candidates.push_back(newCandidate);
     cout << "Candidato registrado exitosamente.\n";
}

//Funcion de registro de voto
void registerVote() {
    if (candidates.empty()) {
        cout << "No hay candidatos registrados.\n";
        return;
    }

    string voterID;
    do {
        cout << "Ingrese su cedula: ";
        cin >> voterID;
        if (!isDigit(voterID)) {
            cout << "Error: La cedula debe contener solo números.\n";
        }
    } while (!isDigit(voterID));

    if (voterIDs.find(voterID) != voterIDs.end()) {
        cout << "Error: Ya se ha registrado un voto con esta cedula.\n";
        return;
    }

    int choice;
    do {
        cout << "Ingrese el numero del candidato por el que desea votar:\n";
        for (int i = 0; i < candidates.size(); ++i) {
            cout << i + 1 << ". " << candidates[i].name << " (" << candidates[i].party << ")\n";
        }
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > candidates.size()) {
            cout << "Error: Opcion no valida. Ingrese un numero entre 1 y " << candidates.size() << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > candidates.size() || cin.fail());

    candidates[choice - 1].votes++;
    voterIDs.insert(voterID);
    cout << "Voto registrado exitosamente.\n";
}

//Funcion de muestra de resultados
void showResults() {
    if (candidates.empty()) {
        cout << "No hay candidatos registrados.\n";
        return;
    }

    int totalVotes = 0;
    for (const auto& candidate : candidates) {
        totalVotes += candidate.votes;
    }

    if (totalVotes == 0) {
        cout << "No se han registrado votos.\n";
        return;
    }

    cout << "\n--- Resultados de las Votaciones ---\n";
    for (const auto& candidate : candidates) {
        double percentage = (static_cast<double>(candidate.votes) / totalVotes) * 100;
        cout << candidate.name << " (" << candidate.party << ") - Votos: " << candidate.votes << " (" << percentage << "%)\n";
    }

    vector<Candidate> winners;
    int maxVotes = 0;
    for (const auto& candidate : candidates) {
        if (candidate.votes > maxVotes) {
            maxVotes = candidate.votes;
            winners.clear();
            winners.push_back(candidate);
        } else if (candidate.votes == maxVotes) {
            winners.push_back(candidate);
        }
    }

    if (winners.size() == 1) {
        cout << "\nEl ganador es: " << winners[0].name << " (" << winners[0].party << ")\n";
    } else {
        cout << "\nHay un empate entre los siguientes candidatos:\n";
        for (const auto& winner : winners) {
            cout << winner.name << " (" << winner.party << ")\n";
        }
    }
}

//Funcion principal que muestra menu de comandos
int main() {
    char option;
    do {
        cout << "\n--- Menu de Sistema de Votaciones ---\n";
        cout << "1. Ingresar Candidatos\n";
        cout << "2. Registrar Votos\n";
        cout << "3. Mostrar Resultados\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;

        if (cin.fail()) {
            cout << "Error: Entrada no valida. Ingrese un numero entre 1 y 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
            case '1':
                registerCandidate();
                break;
            case '2':
                registerVote();
                break;
            case '3':
                showResults();
                break;
            case '4':
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
                break;
        }
    } while (option != '4');

    return 0;
}
