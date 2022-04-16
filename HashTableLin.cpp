#include "HashTableLin.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool HashTableLin::prime(int n) { //prime or not, n running time, 1 space
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

HashTableLin::HashTableLin(int maxNum, double load) //n^2 running time, 1 space
{
    size = maxNum / load; //loadfactor
    double dsize = maxNum / load;
    if (dsize > size) { 
        size++;
    }
    while(!prime(size)) { //not prime increase size
        size++;
    }
    vector<int> temp(size);
    table = temp; //initillize table
    keys = 0;
    maxkey = size * load;
    maxload = load;
}

void HashTableLin::insert(int n) //n^2 running time if rehash n running time without rehash, 1 space
{
    if (!isIn(n)) { //inserts if its not in
        keys++;
        if (maxkey < keys) { //rehash if not enough space
            rehash();
        }
        int i = n % size;
        if (table[i] == NULL) { //inserts if the spot is empty
            table[i] = n;
        }
        else {
            while (table[i] != NULL) { //deals with collision
                i=(i+1)%size;
            }
            table[i] = n;
        }
    }
}

void HashTableLin::rehash() //n^2 running time, 1 space
{
    size *= 2; // double size
    maxkey = maxload * size;
    std::vector<int> tablecopy = table; //empty table to copy over original table to it
    while (!prime(size)) {
        size++;
    }
    keys = 0; 
    table.resize(0); //resets the table size to make it the new size
    table.resize(size);
    for (int i = 0; i < tablecopy.size(); i++) { //copies table over
        if (tablecopy[i] != NULL) {
            insert(tablecopy[i]);
        }
    }
}

bool HashTableLin::isIn(int n) // n running time, 1 space
{
    int i = n % size;
    while (table[i] != NULL) { //table not empty
        if (table[i] == n) { //check is n is the same as the table index
            return true;
        }
        else {
            i = (i + 1) % size; //move down one
            if (i == n % size) { //new index is the same as onld index meaning it go a full time around
                return false;
            }
        }
    }
    return false;
}

void HashTableLin::printKeys() //n running time, 1 space
{
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            cout << table[i] << ", ";
        }
    }
}

void HashTableLin::printKeysAndIndexes() //n running time, 1 space
{
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            cout << i << ", " << table[i];
        }
    }
}

int HashTableLin::getNumKeys() { //n running time, 1 space
    int keycount = 0;
    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            keycount++;
        }
    }
    return keycount;
}

int HashTableLin::getTableSize() { //1 running time, 1 space
    return size;
}

double HashTableLin::getMaxLoadFactor() { //1 running time, 1 space
    return maxload;
}

int HashTableLin::insertCount(int n) { //n^2 running time, 1 space
    int probe = 0;
    if (!isIn(n)) {
        keys++;
        if (maxkey < keys) {
            rehash();
        }
        int i = n % size;
        if (table[i] == NULL) {
            table[i] = n;
            probe++;
        }
        else {
            while (table[i] != NULL) {
                i = (i + 1) % size;
                probe++;
            }
            table[i] = n;
            probe++;
        }
    }
    return probe;
}

std::vector<double> HashTableLin::simProbeSuccess()
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
            HashTableLin hashtable = HashTableLin(maxsize, loadfactor);
            for (int j = 0; j < somesize; j++) {
                sum += (hashtable.insertCount(randnumlist[j])) / (somesize);
            }
        }
        /* cout << "SUM: " << sum << "\n";*/
        avgprobe = sum / 100;
        //cout <<"AVGPROBES: " << avgprobe << "\n";
        result[count] = avgprobe;
        count++;
    }
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
