#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// --- Constants & Enums ---
enum State { EMPTY, OCCUPIED, DELETED };

// --- Hash Functions ---

// Hash1: FNV-1a (For Outer Table) [cite: 10]
int Hash1(int key, int tableSize) {
    string s = to_string(key);
    const unsigned int FNV_PRIME = 16777619u;
    const unsigned int FNV_OFFSET_BASIS = 2166136261u;
    unsigned int hashValue = FNV_OFFSET_BASIS;
    for (char c : s) {
        hashValue ^= (unsigned int)c;
        hashValue *= FNV_PRIME;
    }
    return (int)(hashValue % tableSize);
}

// Hash2: Polynomial Rolling Hash (For Inner Table) [cite: 12]
int Hash2(int key, int tableSize) {
    string s = to_string(key);
    const int BASE = 31;
    const unsigned long long MODULUS = 1000000007ULL;
    unsigned long long hashValue = 0;
    for (char c : s) {
        hashValue = (hashValue * BASE + (unsigned long long)c) % MODULUS;
    }
    return (int)(hashValue % tableSize);
}

// --- Inner Hash Table Class ---
// Stores (user_id, permission)
class InnerHashTable {
    struct UserNode {
        int user_id;
        string permission;
    };

    int size;
    vector<UserNode> table;
    vector<State> status;

public:
    // Default constructor needed for vector resizing in OuterTable
    InnerHashTable() : size(0) {}

    // Initialize the table with size N
    void init(int n) {
        size = n;
        table.assign(size, {0, ""});
        status.assign(size, EMPTY);
    }

    // Quadratic Probing Insert [cite: 19, 20]
    void insert(int uid, string perm) {
        if (size == 0) return; // Safety check
        int h = Hash2(uid, size);

        for (int i = 0; i < size; i++) {
            // Index = (hash2(user_id) + i^2) mod N [cite: 21]
            long long index = (h + (long long)i * i) % size;

            if (status[index] == EMPTY || status[index] == DELETED) {
                table[index] = {uid, perm};
                status[index] = OCCUPIED;
                return;
            } else if (status[index] == OCCUPIED && table[index].user_id == uid) {
                table[index].permission = perm; // Update existing
                return;
            }
        }
    }

    // Search for a specific user
    string search(int uid) {
        if (size == 0) return "";
        int h = Hash2(uid, size);

        for (int i = 0; i < size; i++) {
            long long index = (h + (long long)i * i) % size;

            if (status[index] == EMPTY) return ""; // Not found
            if (status[index] == OCCUPIED && table[index].user_id == uid) {
                return table[index].permission;
            }
        }
        return "";
    }

    // Remove user and return string for printing
    string remove(int uid) {
        if (size == 0) return "";
        int h = Hash2(uid, size);

        for (int i = 0; i < size; i++) {
            long long index = (h + (long long)i * i) % size;

            if (status[index] == EMPTY) return "";
            if (status[index] == OCCUPIED && table[index].user_id == uid) {
                status[index] = DELETED;
                return "(" + to_string(uid) + ", " + table[index].permission + ")";
            }
        }
        return "";
    }

    // Print all users in this group
    void printAll() {
        bool first = true;
        for (int i = 0; i < size; i++) {
            if (status[i] == OCCUPIED) {
                if (!first) cout << ", ";
                cout << "(" << table[i].user_id << ", " << table[i].permission << ")";
                first = false;
            }
        }
        cout << endl;
    }
};

// --- Outer Hash Table Class ---
// Stores (group_id, InnerHashTable)
class OuterHashTable {
    struct GroupNode {
        int group_id;
        // DIRECT OBJECT, NO POINTER [cite: 6]
        InnerHashTable innerTable; 
    };

    int size;
    vector<GroupNode> table;
    vector<State> status;

public:
    OuterHashTable(int n) : size(n) {
        table.resize(size);
        status.resize(size, EMPTY);
    }

    // Returns index of the group, or creates it if missing
    int getOrInsertGroupIndex(int gid) {
        int h = Hash1(gid, size);
        int firstDeleted = -1;

        for (int i = 0; i < size; i++) {
            // Linear Probing: (hash1(group_id) + i) mod N [cite: 18]
            int index = (h + i) % size;

            if (status[index] == EMPTY) {
                // Determine insertion spot (either here or recycled deleted spot)
                int targetIndex = (firstDeleted != -1) ? firstDeleted : index;
                
                status[targetIndex] = OCCUPIED;
                table[targetIndex].group_id = gid;
                // Initialize the inner table at this index
                table[targetIndex].innerTable.init(size); 
                return targetIndex;
            }

            if (status[index] == OCCUPIED && table[index].group_id == gid) {
                return index; // Found existing
            }

            if (status[index] == DELETED && firstDeleted == -1) {
                firstDeleted = index;
            }
        }
        return -1; // Table full
    }

    // Returns index of the group if found, else -1
    int searchGroupIndex(int gid) {
        int h = Hash1(gid, size);

        for (int i = 0; i < size; i++) {
            int index = (h + i) % size;

            if (status[index] == EMPTY) return -1;
            if (status[index] == OCCUPIED && table[index].group_id == gid) {
                return index;
            }
        }
        return -1;
    }

    // Helper to access inner table operations directly
    void insertUser(int gid, int uid, string perm) {
        int idx = getOrInsertGroupIndex(gid);
        if (idx != -1) {
            table[idx].innerTable.insert(uid, perm);
        }
    }

    void searchUser(int gid, int uid) {
        int idx = searchGroupIndex(gid);
        if (idx == -1) {
            cout << "Group not found" << endl;
        } else {
            string res = table[idx].innerTable.search(uid);
            if (res == "") cout << "User not found in group " << gid << endl;
            else cout << res << endl;
        }
    }

    void printGroup(int gid) {
        int idx = searchGroupIndex(gid);
        if (idx == -1) {
            cout << "Group not found" << endl;
        } else {
            table[idx].innerTable.printAll();
        }
    }

    void deleteUser(int gid, int uid) {
        int idx = searchGroupIndex(gid);
        if (idx == -1) {
            cout << "Group not found" << endl;
        } else {
            string res = table[idx].innerTable.remove(uid);
            if (res == "") cout << "User not found in group " << gid << endl;
            else cout << res << " deleted" << endl;
        }
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;

    // Outer Table initialized with size N
    OuterHashTable db(N); 

    // Consume the rest of the first line (newline character)
    string dummy;
    getline(cin, dummy);

    for (int k = 0; k < Q; k++) {
        string line;
        getline(cin, line);
        if (line.empty()) continue;

        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "INSERT") { // [cite: 35]
            int gid, uid;
            string perm;
            ss >> gid >> uid >> perm;
            db.insertUser(gid, uid, perm);
        } 
        else if (type == "SEARCH") { 
            int gid;
            ss >> gid;
            int uid;
            
            // Check if user_id exists in the input line
            if (ss >> uid) {
                // SEARCH <group_id> <user_id> [cite: 41]
                db.searchUser(gid, uid);
            } else {
                // SEARCH <group_id> [cite: 44]
                db.printGroup(gid);
            }
        } 
        else if (type == "DELETE") { // [cite: 47]
            int gid, uid;
            ss >> gid >> uid;
            db.deleteUser(gid, uid);
        }
    }

    return 0;
}