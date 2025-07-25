#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int n, m; // Number of processes and resources
vector<vector<int>> allocation, maxNeed, need;
vector<int> available;

bool isSafeSequence(vector<int>& safeSequence) {
    vector<bool> finished(n, false);
    vector<int> work = available;

    for (int count = 0; count < n; count++) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safeSequence.push_back(i);
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false; // No safe sequence found
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " input.txt output.txt" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin || !fout) {
        cout << "Error opening input/output file." << endl;
        return 1;
    }

    fin >> n >> m;

    allocation.resize(n, vector<int>(m));
    maxNeed.resize(n, vector<int>(m));
    need.resize(n, vector<int>(m));
    available.resize(m);

    // Read Allocation Matrix
    fout << "Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> allocation[i][j];
            fout << allocation[i][j] << " ";
        }
        fout << "\n";
    }

    // Read Max Need Matrix
    fout << "\nMax Need Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> maxNeed[i][j];
            fout << maxNeed[i][j] << " ";
        }
        fout << "\n";
    }

    // Read Available Resources
    fout << "\nAvailable Resources:\n";
    for (int i = 0; i < m; i++) {
        fin >> available[i];
        fout << available[i] << " ";
    }
    fout << "\n";

    // Calculate Need Matrix
    fout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
            fout << need[i][j] << " ";
        }
        fout << "\n";
    }

    // Check for Safe Sequence
    vector<int> safeSequence;
    if (isSafeSequence(safeSequence)) {
        fout << "\nSystem is in a SAFE state.\nSafe Sequence: ";
        for (int p : safeSequence)
            fout << "P" << p << " ";
    } else {
        fout << "\nSystem is in DEADLOCK (Unsafe State).";
    }

    fin.close();
    fout.close();

    return 0;
}
