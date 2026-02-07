#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;


const int INITIAL_SIZE=13;
const double CUT_OFF_LOAD_FACTOR=0.5;
const int C1=3;
const int C2=5;
enum CollisionResolution {CHAINING,DOUBLE_HASHING,CUSTOM_PROBING};
enum HashFunction {HASH1,HASH2};
enum State {EMPTY,OCCUPIED,DELETED};

bool isPrime(int n)
{
    if(n<=1) return false;

    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0) return false;
    }

    return true;
}

int nextPrime(int n)
{
    n*=2;
    
    if(n%2==0) n++;

    while(!isPrime(n)) n+=2;

    return n;
}

int prevPrime(int n)
{
    n/=2;
    if(n<=2) return 2;
    n--;

    if(n%2==0) n--;

    while(!isPrime(n)) {n-=2;
        if(n<2) return 2;
    }

    return n;
}

//FMV-1a
int Hash1(const string key, int tableSize) {

    const unsigned int FNV_PRIME = 16777619u;
    const unsigned int FNV_OFFSET_BASIS = 2166136261u;
    
    unsigned int hashValue = FNV_OFFSET_BASIS;
    

    for (int i = 0; i < key.length(); i++) {
        hashValue ^= (unsigned int)(key[i]);
        hashValue *= FNV_PRIME;
    }
    

    return (int)(hashValue % tableSize);
}


//Rolling Hash
int Hash2(const string key, int tableSize) {

    const int BASE = 31;
    const unsigned long long MODULUS = 1000000007ULL;
    
    unsigned long long hashValue = 0;
    

    for (int i = 0; i < key.length(); i++) {
        hashValue = (hashValue * BASE + (unsigned long long)(key[i])) % MODULUS;
    }
    

    return (int)(hashValue % tableSize);
}


//auxiliary hash
int auxHash(const string key, int tableSize) {
    const int AUX_BASE = 37;
    
    unsigned int hashValue = 0;

    for (int i = 0; i < key.length(); i++) {
        hashValue = hashValue * AUX_BASE + (unsigned int)(key[i]);
    }
    
    int result = (hashValue % (tableSize - 1)) + 1;
    return result;
}

string randomWord(int len)
{
    string word="";

    for(int i=0;i<len;i++)
    {
        char c='a'+(rand()%26);
        word+=c;
    }

    return word;
}

vector<string> generateUniqueWords(int numWords, int len)
{
    set<string>ans;

    while(ans.size()<numWords)
    {
        string word=randomWord(len);
        ans.insert(word);
    }

   return vector<string>(ans.begin(),ans.end());
}

template<typename K,typename V>
class HashTable {
    private:
        int tableSize;
        int numElements;
        int insertsResize;
        int deleteResize;
        int collisionCount;
        int hits;

        CollisionResolution colType;
        HashFunction hashType;

        struct Node{
            K key;
            V val;
        };
        vector<vector<Node>>chainTable;

        struct Entry{
            K key;
            V val;
            State state;

            Entry() : state(EMPTY) {}

            Entry(K k, V v, State s): key(k),val(v),state(s) {}
        };

        vector<Entry>openTable;

        int getHash(K& key)
        {
            if(hashType==HASH1) return Hash1(key,tableSize);
            else return Hash2(key,tableSize);
        }

        int getAuxHash(K& key)
        {
            return auxHash(key,tableSize);
        }

        double loadFactor()
        {
            return (double)numElements/tableSize;
        }

        bool canExpand()
        {
            return loadFactor()>CUT_OFF_LOAD_FACTOR && insertsResize>= numElements/2;
        }

        bool canCompact()
        {
            return loadFactor()<0.25 && deleteResize>=numElements/2 && tableSize>INITIAL_SIZE;
        }

        void insertChain(K& key, V& val)
        {
            int index=getHash(key);

            for(int i=0;i<chainTable[index].size();i++)
            {
                if(chainTable[index][i].key==key) return;
            }

            if(chainTable[index].size()>0) collisionCount++;

            chainTable[index].push_back({key,val});
            numElements++;
            insertsResize++;

        }


        void insertOpen(K& key,V& val) 
        {
            long long h=getHash(key);
            long long aux=getAuxHash(key);

            long long index=0;
            bool collision=false;
            for(int i=0;i<openTable.size();i++)
            {
                if(colType==DOUBLE_HASHING) index=(h+ i*aux) % tableSize;

                else index=(h +C1*i*aux + (long long)C2*i*i) % tableSize;

                if(openTable[index].state==EMPTY || openTable[index].state==DELETED)
                {
                    openTable[index]={key,val,OCCUPIED};
                    numElements++;
                    insertsResize++;
                    break;
                }

                else if(openTable[index].state==OCCUPIED)
                {
                    if(openTable[index].key==key) break;
                    else collisionCount++;
                }
                    
            }
        }



        void rehash(int newSize)
        {
            int oldSize=tableSize;
            tableSize=newSize;
            numElements=0;

            if(colType==CHAINING)
            {
                vector<vector<Node>>oldTable=chainTable;
                chainTable.clear();
                chainTable.resize(tableSize);

                for(auto u:oldTable)
                {
                    for(auto node: u)
                    {
                        insertChain(node.key,node.val);
                    }
                }
            }

            else {
                vector<Entry>oldTable=openTable;
                openTable.clear();
                openTable.resize(tableSize);

                for(int i=0;i<oldSize;i++)
                {
                    Entry ent=oldTable[i];
                    if(ent.state==OCCUPIED)
                    {
                        insertOpen(ent.key,ent.val);
                    }
                }
            }

            insertsResize=0;
            deleteResize=0;

        }

        void removeChain(K key)
        {
            int index=getHash(key);

            for(auto it=chainTable[index].begin(); it!=chainTable[index].end();it++)
            {
                if(it->key==key)
                {
                    chainTable[index].erase(it);
                    numElements--;
                    deleteResize++;
                    return;
                }
            }
        }

        void removeOpen(K key)
        {
            long long h= getHash(key);
            long long aux=getAuxHash(key);
            long long index=0;

            for(int i=0;i<openTable.size();i++)
            {
                if(colType==DOUBLE_HASHING) index= (h + i*aux)%tableSize;
                else index= (h + C1*i*aux + (long long)C2*i*i)%tableSize;

                if(openTable[index].state==EMPTY) return;

                if(openTable[index].state==OCCUPIED && openTable[index].key==key)
                {
                    openTable[index].state=DELETED;
                    numElements--;
                    deleteResize++;
                    return;
                }
            }
        }

        

    public: 
        HashTable(CollisionResolution c, HashFunction h)
        {
            tableSize=INITIAL_SIZE;
            colType=c;
            hashType=h;
            numElements=0;
            insertsResize=0;
            deleteResize=0;
            collisionCount=0;
            hits=0;

            if(colType==CHAINING) chainTable.resize(tableSize);
            else openTable.resize(tableSize);

        }

        void insert(K key,V val)
        {
            if(colType==CHAINING) insertChain(key,val);
            else insertOpen(key,val);

            if(canExpand()) rehash(nextPrime(tableSize));
        }

        void remove(K key)
        {
            if(colType==CHAINING) removeChain(key);
            else removeOpen(key);

            if(canCompact())
            {
                rehash(prevPrime(tableSize));
            }
        }

        V* search(K key)
        {
            if(colType==CHAINING)
            {
                int index=getHash(key);
                for(auto& node: chainTable[index])
                {
                    hits++;
                    if(node.key==key) return &node.val;
                }
            }

            else
            {
                long long h=getHash(key);
                long long aux=getAuxHash(key);
                long long index=0;

                for(int i=0;i<openTable.size();i++)
                {
                    hits++;
                    if(colType==DOUBLE_HASHING) index= (h + i*aux)%tableSize;
                    else index= (h + C1*i*aux + (long long)C2*i*i)% tableSize;

                    if(openTable[index].state==EMPTY) return nullptr;
                    if(openTable[index].state==OCCUPIED && openTable[index].key==key) return &openTable[index].val;
                }
            }

            return nullptr;
        }


        int getCollisionCount()
        {
            return collisionCount;
        }

        int getHits()
        {
            return hits;
        }
        





};


void run(string name, CollisionResolution colType, HashFunction hashType, vector<string>& words, 
    vector<string>& searchWords)
{
    HashTable<string,int> ht(colType,hashType);

    for(int i=0;i<words.size();i++)
    {
        ht.insert(words[i],i+1);
    }

    for(auto word: searchWords)
    {
        ht.search(word);
    }

    cout<<"Hash Funtion: "<<name<<endl;
    cout<<"Total Collisions: "<<ht.getCollisionCount()<<endl;
    cout<<"Average Hits: "<< (double)ht.getHits()/searchWords.size()<<endl;
}



void solve()
{
    int n=10000;
    int q=1000;
    int len=10;

    vector<string>words=generateUniqueWords(n,len);
    vector<string> searchWords = words;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(searchWords.begin(), searchWords.end(), std::default_random_engine(seed));
    searchWords.resize(q);

    cout<<"--- CHAINING METHOD ---"<<endl;
    run("FNV-1a",CHAINING,HASH1,words,searchWords);
    run("Polynomial Rolling Hash",CHAINING,HASH2,words,searchWords);

    cout<<endl;

    cout<<"--- DOUBLE HASHING ---"<<endl;
    run("FNV-1a",DOUBLE_HASHING,HASH1,words,searchWords);
    run("Polynomial Rolling Hash",DOUBLE_HASHING,HASH2,words,searchWords);

    cout<<endl;

    cout<<"--- CUSTOM PROBING ---"<<endl;
    run("FNV-1a",CUSTOM_PROBING,HASH1,words,searchWords);
    run("Polynomial Rolling Hash",CUSTOM_PROBING,HASH2,words,searchWords);

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    srand(time(0));

    int t=1;
    //cin>>t;
    for(int i=0;i<t;i++)
    {
        solve();
    }

}

//g++ -o program filename.cpp && ./program

// g++ -O2 -o program filename.cpp && ./program < input.txt > output.txt