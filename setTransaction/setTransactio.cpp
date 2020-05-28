#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include <cstring>
#include "timer.h"
#include "RytisMasterClassOnHashingAlgorithms.h"
unsigned t0,t1;
thread_local static std::mt19937 rg{
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
thread_local static std::uniform_int_distribution<int> pick(0, goodCharsLength-1);
thread_local static std::uniform_int_distribution<int> randommoney(100, 10000);//valor asignado para la trasaccion de modo random no influencia en la generacion o variacion del hash
thread_local static std::uniform_int_distribution<int> person(0, 99);
thread_local static std::uniform_int_distribution<int> amount(1, 100);
std::chrono::high_resolution_clock Timer = std::chrono::high_resolution_clock();
long long static getTime(){ return Timer.now().time_since_epoch().count();}
std::string random_string( size_t length )
{
    auto randchar = []() -> char {return goodChars[pick(rg)];};
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
class Person{//asignacion de clase y estructura del codigo
public:
    Person(int mon, std::string s, std::string d){
        money = mon;
        name = s;
        key = d;
    }
    int money;
    std::string name;
    std::string key;
};

class Transaction{//asignacion de clase y estructura
public:
    Transaction(int mon, std::string s, std::string d){
        amount = mon;
        from = s;
        to = d;
        timestamp = getTime();
        this->hash = HASHING_RYTISMASTERCLASSONHASHINGALGORITHMS_H::hash(std::to_string(mon) + s + d + std::to_string(timestamp));
    }
    int amount;
    long long timestamp;
    std::string from;
    std::string to;
    std::string hash;
};

class Block{//asignacion de clase y estructura para el nonce
public:
    Block(std::string prevhash, std::string merkel,int diff, int nonce, std::vector<Transaction> b){
        transactions = b;
        this->prevhash = prevhash;
        this->merkel = merkel;
        this->timestamp = getTime();
        this->diff = diff;
        this->nonce = nonce;
    }
    std::string version = "1.0";
    std::string prevhash;
    std::string merkel;
    long long int timestamp;
    std::vector<Transaction> transactions;
    int diff;
    int nonce;
};

std::vector<Block> blockChain;
std::string MerkleRoot(std::vector<Transaction> transactions){
    std::vector<std::string> merkleTree;
    for (Transaction t : transactions)
        merkleTree.push_back(hash(std::to_string(t.amount)+t.from+t.to));

    while (merkleTree.size() > 1){
        if (merkleTree.size()%2 != 0)
            merkleTree.emplace_back("");
        std::vector<std::string> newMerkleTree;
        for (int i = 0; i < merkleTree.size(); i += 2){
            std::string first = merkleTree.at(i);
            std::string second = merkleTree.at(i+1);
            newMerkleTree.push_back(hash(first + second));
        }
        merkleTree = newMerkleTree;
    }
    return merkleTree.at(0);
}
std::vector<Person> people;


std::vector<Transaction> transactions;

std::vector<Transaction> generateTransactions(){
    std::vector<Transaction> transactions;
    for (int i = 0; i < 10000; ++i) {
        auto sender = person(rg);
        auto receiver = person(rg);
        while(sender == receiver) receiver = person(rg);
        auto money = amount(rg);
        if(people.at(sender).money < money){ // check if has sufficient funds
            --i;
            continue;
        }
        people.at(sender).money -= money;
        people.at(receiver).money += money;
        auto transaction = new Transaction(money, people.at(sender).name, people.at(receiver).name);
        transactions.push_back(*transaction);
    }
    return transactions;
}

int generateBlock(std::string prevHash, int difficulty, int startIndex , int searchMultiplier, std::vector<Transaction> transactions){//generacion de un nuevo bloque para minar 
    std::string zeros = "0000000000000000000000";//tamaño del ajuste de 64b
    auto merkle = MerkleRoot(transactions);
    int nonce = 100000 * startIndex;
    for (; nonce <nonce + 100000 * searchMultiplier; ++nonce) {
        std::ostringstream full;
        full << prevHash << merkle << nonce;
        auto hashed = hash(full.str());
        if(strncmp(hashed.c_str(), zeros.c_str(), difficulty)==0){
            std::cout<<hashed<<std::endl;
            return nonce;
        }

    }
    return -1;
}
std::string hashBlock(Block block){
    std::ostringstream full;
    full << block.prevhash << block.merkel << block.nonce;
    return hash(full.str());
}

std::vector<Transaction> getTransactionsForBlock(std::vector<Transaction> &newtransactions, int size) {
    std::vector<Transaction> transactionsForBlock;
    for (int k = 0; k < size ; ++k) {
        if(strncmp(newtransactions.at(k).hash.c_str(),
                   hash(std::__cxx11::to_string(newtransactions.at(k).amount)
                        + newtransactions.at(k).from
                        + newtransactions.at(k).to
                        + std::__cxx11::to_string(newtransactions.at(k).timestamp)).c_str(), hashSize) != 0) // hashses dont match
        {
            newtransactions.erase(newtransactions.begin()+k);//remove bad input
            --k;//get full amount
            if(newtransactions.size()<100){//if too little left, reduce final output size
                size = newtransactions.size();
                continue;
            }

        }
        transactionsForBlock.push_back(newtransactions.at(k));
    }
    newtransactions.erase(newtransactions.begin() + transactionsForBlock.size());
    return transactionsForBlock;
}


void reinsertUnusedTransactions(std::vector<Transaction> &transactionsForBlockb,
                                std::vector<Transaction> &transactionsForBlockc,
                                std::vector<Transaction> &transactionsForBlockd,
                                std::vector<Transaction> &transactionsForBlocke
) {
    transactions.insert(end(transactions), begin(transactionsForBlockb), begin(transactionsForBlockb));
    transactions.insert(end(transactions), begin(transactionsForBlockc), begin(transactionsForBlockc));
    transactions.insert(end(transactions), begin(transactionsForBlockd), begin(transactionsForBlockd));
    transactions.insert(end(transactions), begin(transactionsForBlocke), begin(transactionsForBlocke));
}
//paso de la transaccion para no perder el historial de transacciones 
int getNewBlockNonce(std::vector<Transaction> &newtransactions, int size, int difficulty, int startIndex,
                     int startingsearchMultiplier) {//continuacion del nuevobloque generado por el nonce
    auto transactionsForBlocka = getTransactionsForBlock(newtransactions, size);
    auto transactionsForBlockb = getTransactionsForBlock(newtransactions, size);
    auto transactionsForBlockc = getTransactionsForBlock(newtransactions, size);
    auto transactionsForBlockd = getTransactionsForBlock(newtransactions, size);
    auto transactionsForBlocke = getTransactionsForBlock(newtransactions, size);
    int nonce =-1;
    while(nonce == -1){
            nonce = generateBlock(hashBlock(blockChain.back()),difficulty,startIndex,startingsearchMultiplier,transactionsForBlocka);
            if(nonce != -1) {reinsertUnusedTransactions(transactionsForBlockb, transactionsForBlockc, transactionsForBlockd, transactionsForBlocke);continue;}

            nonce = generateBlock(hashBlock(blockChain.back()),difficulty,startIndex,startingsearchMultiplier,transactionsForBlockb);
            if(nonce != -1) {reinsertUnusedTransactions(transactionsForBlocka, transactionsForBlockc, transactionsForBlockd, transactionsForBlocke); continue;}

            nonce = generateBlock(hashBlock(blockChain.back()),difficulty,startIndex,startingsearchMultiplier,transactionsForBlockc);
            if(nonce != -1) {reinsertUnusedTransactions(transactionsForBlockb, transactionsForBlocka, transactionsForBlockd, transactionsForBlocke); continue;}

            nonce = generateBlock(hashBlock(blockChain.back()),difficulty,startIndex,startingsearchMultiplier,transactionsForBlockd);
            if(nonce != -1) {reinsertUnusedTransactions(transactionsForBlockb, transactionsForBlockc, transactionsForBlocka, transactionsForBlocke); continue;}

            nonce = generateBlock(hashBlock(blockChain.back()),difficulty,startIndex,startingsearchMultiplier,transactionsForBlocke);
            if(nonce != -1) {reinsertUnusedTransactions(transactionsForBlockb, transactionsForBlockc, transactionsForBlockd, transactionsForBlocka); continue;}

            startingsearchMultiplier++;//verificacion del nonce si es unico o si este se repite en el historial si este se repite el nonce inicial es desechado para poder cumplir con las caracteristicas
        }
    return nonce;
}

int main(void) {
    for (int i = 0; i < 100; ++i) {
        auto person = new Person(randommoney(rg),random_string(8),random_string(52));
        people.push_back(*person);
    }

    auto newtransactions = generateTransactions();


    int size = 100;
    if(newtransactions.size()<100){
        size = newtransactions.size();
    }

    auto transactionsForBlock = getTransactionsForBlock(newtransactions, size);

////IMPORTANTE
for(int p=1; p<5;p++){//bucle for para la inicializacion del numero de ceros de los cuales van a ir de 1 cero a 5 ceros estableciendo el tiempo de ejecucion
    int difficulty = p;//el grado de dificultad lo hace
    int startIndex = 1;//para poder verificar la cualidad que distingue un nonce
    int searchMultiplier = 1;//lo hace unico su startIndex y su searchMultiplier



    t0=clock();//MEDICION
    int correctNonce = generateBlock("000000000000000000000000", difficulty, startIndex, searchMultiplier, transactionsForBlock);//si este cumple con la condicion del nonce pasa a la siguiente parte de generacion de mas nonce aparttir de ese bloque
    t1=clock();
    double tim=(double(t1-t0)/CLOCKS_PER_SEC);//diferencia de tiempo del primer nonce
    std::cout << "\n Tiempo de ejecución: \n  "<< tim;

    auto firstBock = new Block("000000000000000000000000", MerkleRoot(transactionsForBlock),difficulty,correctNonce,transactionsForBlock);
    //toma el primer nonce y genera el bloque 
    blockChain.push_back(*firstBock);
    
    //genera bloques con respecto al nonce analizado    
    for (int j = 0; j < 2; ++j) {
        t0=clock();
        int nonce = getNewBlockNonce(newtransactions, size, difficulty, startIndex, searchMultiplier);
        blockChain.push_back(*new Block(hashBlock(blockChain.back()), MerkleRoot(transactionsForBlock),difficulty,nonce,transactionsForBlock));
        t1=clock();
         double tim=(double(t1-t0)/CLOCKS_PER_SEC);
         std::cout << "\n Tiempo de ejecución: \n  "<< tim;
    }
    }
    
    return 0;
}
