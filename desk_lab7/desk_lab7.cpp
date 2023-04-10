#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int** incidence;
int** adjacency;
int vertices;
int edges;

void initGraph(string fname);
void makeIncidenceMatrix(string line, int lineNumber);
void makeAdjacencyMatrix(string line);
string adjacencyMatrixToString();
string incidenceMatrixToString();
void printMatrix(string matrix);
string Degree();
void Save();
string isolated();
string hanging();
bool isolatedCalc();
int Regular();

int main()
{
    char fname[] = "graph_01.txt";
    initGraph(fname);
    int menu;
    do
    {
        cout << "1 - Vyznachyty stepin vershyn hrafa" << endl;
        cout << "2 - Zberehty stupin vershyn hrafa" << endl;
        cout << "3 - Vidobrazyty vsi izolovani ta vysyachi vershyny" << endl;
        cout << "4 - Rehulyarnyy indeks" << endl;
        cout << "0 - Exit" << endl;
        cin >> menu;
        switch (menu)
        {
        case 1:
            printMatrix(Degree());
            break;

        case 2:
            Save();
            break;

        case 3:
            printMatrix(isolated());
            break;

        case 4:
            if (Regular() != -1)
                cout << "Rehulyarnyy = " << Degree() << endl;
            else
                cout << "Graph ne rehulyarnyy" << endl;
            break;

        default:
            break;
        }
    } while (menu != 0);
}

void initGraph(string fname) {
    ifstream input(fname);
    if (!input.is_open()) {
        cout << "Error opening file " << fname << endl;
        return;
    }

    string line;
    getline(input, line);
    if (!line.empty()) {
        istringstream iss(line);
        iss >> vertices >> edges;
        incidence = new int* [vertices];
        adjacency = new int* [vertices];
        for (int i = 0; i < vertices; i++) {
            incidence[i] = new int[edges];
            adjacency[i] = new int[vertices];
        }
    }
    else {
        cout << "Porozhniy vkhidnyy fayl" << endl;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacency[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            incidence[i][j] = 0;
        }
    }

    int lineNumber = 0;
    while (getline(input, line)) {
        makeIncidenceMatrix(line, lineNumber);
        makeAdjacencyMatrix(line);
        lineNumber++;
    }

    input.close();
}

void makeIncidenceMatrix(string line, int lineNumber) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));

    if (from == to) {
        incidence[from - 1][lineNumber] = 2;
    }
    else {
        incidence[from - 1][lineNumber] = -1;
        incidence[to - 1][lineNumber] = 1;
    }
}

void makeAdjacencyMatrix(string line) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));
    adjacency[from - 1][to - 1]++;
}

string adjacencyMatrixToString() {
    stringstream result;
    result << "| v\\v |";
    for (int i = 1; i <= vertices; i++) {
        result << " v" << setw(2) << setfill(' ') << i << "|";
    }
    for (int i = 0; i < vertices; i++) {
        result << "\n| v" << setw(2) << setfill(' ') << i + 1 << " |";
        for (int j = 0; j < vertices; j++) {
            result << " " << setw(2) << setfill(' ') << adjacency[i][j] << " |";
        }
    }
    return result.str();
}

string incidenceMatrixToString() {
    stringstream result;
    result << "| v\\e |";
    for (int i = 1; i <= edges; i++) {
        result << " e" << setw(2) << setfill(' ') << i << "|";
    }
    for (int i = 0; i < vertices; i++) {
        result << "\n| v" << setw(2) << setfill(' ') << i + 1 << " |";
        for (int j = 0; j < edges; j++) {
            result << " " << setw(2) << setfill(' ') << incidence[i][j] << " |";
        }
    }
    return result.str();
}

void printMatrix(string matrix) {
    cout << matrix << endl;
}

string Degree() {
    stringstream result;

    int degree[100][2] = { 0 };
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            degree[j][0] += adjacency[j][i];
            degree[j][1] += adjacency[j][i];
        }
    }

    result << "| V " << "| v-stupeni " << "| poza-stupenem |" << endl;
    for (int i = 0; i < vertices; i++)
    {
        result << "| V" << i + 1 << "|" << right << setw(11) << degree[i][0] << "|   " << right << setw(12) << degree[i][1] << "|" << endl;
    }

    return result.str();
}

void Save() {
    string filename;
    cout << "Vvedit nazvu faylu: ";
    cin >> filename;

    ofstream outfile(filename);
    if (!outfile) {
        cout << "Pomylka vidkryttya faylu." << endl;
        return;
    }

    outfile << Degree();

    outfile.close();
}

string isolated() {
    stringstream res;

    bool var[100][100];

    int degree[100][2] = { 0 };
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            degree[j][0] += adjacency[j][i];
            degree[j][1] += adjacency[j][i];
        }
    }
    for (int i = 0; i < vertices; i++) {
        if (degree[i][0] + degree[i][1] == 0) var[i][0] = true;
        if (degree[i][0] + degree[i][1] == 1) var[i][1] = true;
    }

    res << "| Izolovani vershyny| Vysyachi vershyny|" << endl;

    for (int i = 0; i < vertices; i++) {
        if (var[i][0] && var[i][1])
            res << "| " << "v" << i << right << setw(18) << " | " << right << setw(15) << "v" << i << " |" << endl;
        else if (var[i][0])
            res << "| " << "v" << i + 1 << right << setw(18) << " | " << right << setw(17) << "" << " |" << endl;
        else if (var[i][1])
            res << "| " << "" << right << setw(20) << " | " << right << setw(15) << "v" << i + 1 << " |" << endl;
    }

    return res.str();
}

bool isolatedCalc() {
    bool var[100][100];

    int degree[100][2] = { 0 };
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            degree[j][0] += adjacency[j][i];
            degree[j][1] += adjacency[j][i];
        }
    }
    for (int i = 0; i < vertices; i++) {
        if (degree[i][0] + degree[i][1] == 0) var[i][0] = true;
        if (degree[i][0] + degree[i][1] == 1) var[i][1] = true;
    }

    return var;
}

string hanging() {
    stringstream res;

    return res.str();
}

int Regular() {
    int degree[100][2] = { 0 };
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            degree[j][0] += adjacency[j][i];
            degree[j][1] += adjacency[j][i];
        }
    }
    int k = degree[0][0];
    for (auto& part : degree) {
        if (part[0] != part[1] || part[0] != k) return -1;
    }
    return k;
}
