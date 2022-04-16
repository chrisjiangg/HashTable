#include "HashTableQuad.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool HashTableQuad::prime(int n) { //prime or not, n running time, 1 space
    if (n == 1 || n == 0) {
        return false;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

HashTableQuad::HashTableQuad(int maxNum, double load) //n^2 running time, 1 space
{
    size = maxNum / load;
    double dsize = maxNum / load;
    if (dsize > size) {
        size++;
    }
    while (!prime(size)) {
        size++;
    }
    vector<int> temp(size);
    table = temp;
    keys = 0;
    maxkey = size * load;
    maxload = load;
}

void HashTableQuad::insert(int n) //n^2 running time, 1 space
{
    int count = 1;
    if (!isIn(n)) {
        
        int i = n % size;
        if (table[i] == NULL) {
            table[i] = n;
            keys++;
        }
        else {
            while (table[i] != NULL) {
                i = (n%size + (count*count)) % size; //quad probing
                
                if (count == size) { //exits the method once the counter equals the size
                    return;
                }
                count++;
            }
            table[i] = n;
            keys++;
        }
        if (maxkey < keys) {
            rehash();
        }
    }
}

void HashTableQuad::rehash() //n^2 running time, 1 space
{
    size *= 2; // double size
    maxkey = size * maxload;
    std::vector<int> tablecopy = table; 
    while (!prime(size)) {
        size++;
    }
    keys = 0; 
    table.resize(0);
    table.resize(size);
    for (int i = 0; i < tablecopy.size(); i++) {
        if (tablecopy[i] != NULL) {
            insert(tablecopy[i]);
        }
    }
}

bool HashTableQuad::isIn(int n) // n running time, 1 space
{
    int count = 1;
    int i = n % size;
    while (table[i] != NULL) {
        if (table[i] == n) {
            return true;
        }
        else {
            i = (n%size + (count*count)) % size; //quad probing
 
            if (count==size) {
                return false;
            }
            count++;
        }
    }
    return false;
}

void HashTableQuad::printKeys() //n running time, 1 space
{
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            cout << table[i] << ", ";
        }
    }
}

void HashTableQuad::printKeysAndIndexes() //n running time, 1 space
{
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            cout << i << ", " << table[i];
        }
    }
}

int HashTableQuad::getNumKeys() { //n running time, 1 space
    int keycount = 0;
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            keycount++;
        }
    }
    return keycount;
}

int HashTableQuad::getTableSize() { //1 running time, 1 space
    return size;
}

double HashTableQuad::getMaxLoadFactor() { //1 running time, 1 space
    return maxload;
}
int HashTableQuad::insertCount(int n) { //n^2 running time, 1 space
    int probe = 0;
    int count = 1;
    if (!isIn(n)) {

        int i = n % size;
        if (table[i] == NULL) {
            table[i] = n;
            keys++;
            probe++;
        }
        else {
            while (table[i] != NULL) {
                i = (n % size + (count * count)) % size;
                probe++;
                if (count == size) {
                    return 0;
                }
                count++;
            }
            table[i] = n;
            keys++;
            probe++;
        }
        if (maxkey < keys) {
            rehash();
        }
    }
    return probe;
}
std::vector<double> HashTableQuad::simProbeSuccess()
{
    vector<double> result(9);
    int maxsize = 100000;
    int randnumlist[100000];
    double sum = 0;
    double avgprobe = 0;
    double somesize = 100000;
    int count = 0;
    for (int i = 0; i < maxsize; i++) {
        int randnum;
        bool isin = true;
        while (isin) {
            isin = false;
            randnum = (rand() * rand());
            for (int j = 0; j < i; j++) {
                if (randnum == randnumlist[j]) {
                    isin = true;
                    break;
                }
            }
        }
        randnumlist[i] = randnum;
    }
    for (double loadfactor = 0.1; loadfactor < 0.99; loadfactor += 0.1) {
        sum = 0;
        for (int i = 0; i < 100; i++) {
            HashTableQuad hashtable = HashTableQuad(maxsize, loadfactor);
            for (int j = 0; j < somesize; j++) {
                sum += (hashtable.insertCount(randnumlist[j])) / (somesize);
            }
        }
        /* cout << "SUM: " << sum << "\n";*/
        avgprobe = sum / 100;
        //cout << "AVGPROBES: " << avgprobe << "\n";
        result[count] = avgprobe;
        //cout << "COUNT: " << count << "\n";
        count++;
    }
    return result;
}
