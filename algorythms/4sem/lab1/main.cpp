#include "HumanResourceDepartment.h"

int prime = 101;

class HashRow{
public:
    unsigned int a;
    unsigned int b;
    unsigned int size;

    Subdepartment* subdepartments;
};

int mod = 137;

int STR_hash(const string& str){
    int result = 0;
    int m = 1, k = 37;
    for (int i = 0; i < str.size(); i++) {
        result += ((int) str[i] * m) % mod;
        m = (m * k) % mod;
    }
    return result;
}

int univHash(const string& key, int a, int b, int m){
    int stringHash = STR_hash(key);
    //cout << stringHash << '\n';
    return ((a*stringHash + b) % prime) % m;
}

void perfectHashing(HashRow* perfHashTable, vector<Subdepartment>& subdepartments){
    vector<vector<Subdepartment>> countHashes;
    countHashes.resize(subdepartments.size());
    cout << subdepartments.size() << '\n';
    for (int i = 0; i < subdepartments.size(); i++){
        int hash = univHash(subdepartments[i].getName(), 3, 88, subdepartments.size());
        countHashes[hash].push_back(subdepartments[i]);
    }
    for (int i = 0; i < subdepartments.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < countHashes[i].size(); j++)
            cout << countHashes[i][j].getName() << " ";
        cout << '\n';
    }

    for (int i = 0; i < subdepartments.size(); i++){
        if (!countHashes[i].empty()){

            perfHashTable[i].subdepartments = new Subdepartment[countHashes[i].size() * countHashes[i].size()];
            perfHashTable[i].size = countHashes[i].size() * countHashes[i].size();

            if (countHashes[i].size() == 1){
                perfHashTable[i].subdepartments[0] = countHashes[i][0];
                perfHashTable[i].a = perfHashTable[i].b = 0;
                continue;
            }

            bool perfectHashed = false, sameHash = false;
            bool* usedHash = new bool[countHashes[i].size() * countHashes[i].size()];
            for (int j = 0; j < countHashes[i].size() * countHashes[i].size(); j++)
                usedHash[j] = 0;

            perfHashTable[i].b = perfHashTable[i].a = 1;


            while (!perfectHashed){
                for (int j = 0; j < countHashes[i].size() * countHashes[i].size(); j++)
                    usedHash[j] = 0;

                for (int j = 0; j < countHashes[i].size(); j++) {//якщо хеш з колізіями то сеймхешп оставити тру
                    int hash = univHash(countHashes[i][j].getName(),
                                        perfHashTable[i].a,
                                        perfHashTable[i].b,
                                        perfHashTable[i].size);
                   // cout<< countHashes[i][j].getName()<<perfHashTable[i].a<<" "<<perfHashTable[i].b<<" "<<hash<<'\n';
                    if (usedHash[hash])
                        sameHash = true;
                   else usedHash[hash]=true;

                }

                if (sameHash) {
                    sameHash = false;
                    if (perfHashTable[i].a == prime - 1) {
                        perfHashTable[i].a = 1;
                        perfHashTable[i].b++;
                    } else {
                        perfHashTable[i].a++;
                    }
                  //  cout<<perfHashTable[i].a<<" "<<perfHashTable[i].b<<'\n';
                    continue;

                } else {
                    perfectHashed = true;
                 for (int j = 0; j < perfHashTable[i].size; j++) {
                     perfHashTable[i].subdepartments[j].setName("");
                     perfHashTable[i].subdepartments[j].setFY(-1);
                 }
                    for (int j = 0; j < countHashes[i].size(); j++) {
                        int hash = univHash(countHashes[i][j].getName(),
                                            perfHashTable[i].a,
                                            perfHashTable[i].b,
                                            perfHashTable[i].size);
                       // cout<<i<<" "<<j<<" "<<hash<<'\n';
                        perfHashTable[i].subdepartments[hash] = countHashes[i][j];
                    }
                }
            }
        }
    }

}
void search(HashRow* perfHashTable, string STR,int size){


 int hash=univHash(STR,3,88,size);
 int  hashr=univHash(STR,perfHashTable[hash].a,perfHashTable[hash].b,perfHashTable[hash].size);

    if(perfHashTable[hash].subdepartments[hashr].getFY()==-1) cout<<"No data";
    else
    cout<<"Yearfound:"<<perfHashTable[hash].subdepartments[hashr].getFY();
}
int main() {
    int m;
    cout << "Enter amount of data:";
    cin >> m;
    cout << "\n...Generating " << m << " subdepartments\n";
    vector<Subdepartment> Subdepartments;
    Subdepartments = Subdepartment::genSubdepartment(m);
    HashRow* perfectHashTable = new HashRow[m];
   for (int i = 0; i < m; i++) {
       perfectHashTable[i].a = perfectHashTable[i].b = perfectHashTable[i].size = 0;
       perfectHashTable[i].subdepartments = nullptr;
  }
    cout << "Hashing\n";
    perfectHashing(perfectHashTable, Subdepartments);
    cout << "Result\n";

    for (int i = 0; i < Subdepartments.size(); i++){
        cout << i << ": ";
        if (perfectHashTable[i].subdepartments == nullptr)
            cout << "()\n";
        else{
            for (int j = 0; j < perfectHashTable[i].size; j++)
                cout << " (" << perfectHashTable[i].subdepartments[j].getName() << " "<<perfectHashTable[i].subdepartments[j].getFY()<<  ") ";
            cout << '\n';
        }
    }
    string Search_str;
    cout<<"Input search str"<<'\n';
    cin>>Search_str;
   search(perfectHashTable,Search_str,m);
    delete [] perfectHashTable;

    return 0;
}