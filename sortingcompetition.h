#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class SortingCompetition
{
private:
    vector<string> wordHolder;
    vector<string> wordHolderTemp;
    string word;
    string fileName;
public:
    SortingCompetition();
    SortingCompetition(char* inputFileName);
    void setFileName(char* inputFileName);
    bool readData();
    bool prepareData();
    void clearTemp();
    void outputData(char* outputFileName);

    //sort functions
    void sortDataRadixHeap();
    int getMax();
    void countSort(int exp);
    void radixsort();
    void heapsort(int begin, int end);
    int leftChild(int i);
    void percDown(int begin, int end);

    void shiftRight(int low, int high);
    void heapify(int low, int high);
    void heapSort(int begin, int end);


};

#endif // SORTINGCOMPETITION_H
