#include "sortingcompetition.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;

SortingCompetition::SortingCompetition()
{

}

//set the name of the inputFile name
SortingCompetition::SortingCompetition(char* inputFileName)
{
    string fileNameHolder(inputFileName);
    fileName = fileNameHolder;
}

//set the name of the input file
void SortingCompetition::setFileName(char* inputFileName)
{
    string fileNameHolder(inputFileName);
    fileName = fileNameHolder;
}

//read the data in and store it into an original vector
bool SortingCompetition::readData()
{
    ifstream inputFile(fileName.c_str());
    while(inputFile >> word)
    {
        //add the word into the wordHolder
        wordHolder.push_back(word);
    }
    return true;
}

//store the data into a copy Holder so this one can be sorted and tested and then reset
bool SortingCompetition::prepareData()
{
    for(int i = 0; i < wordHolder.size(); i++)
    {
        //push the words from wordHolder to the temporary holder
        wordHolderTemp.push_back(wordHolder[i]);
    }
    return true;
}

//sort using radix and heap
void SortingCompetition::sortDataRadixHeap()
{
    //first radix sort will be called to sort the vector by string length
    radixsort();
    cout << "end of Radix" << endl;
    //at this point, the vector has been sorted by stringlength
    int i = 0;

    //end index to parse to
    int endIndex = 0;
    //beginning index to parse from
    int beginIndex = 0;

    int first = 0;
    int second = 0;

    while(i < wordHolderTemp.size() - 1)
    {
        first = wordHolderTemp[i].length();
        second = wordHolderTemp[i+1].length();

        if(first == second)
        {
            cout << i << endl;
            cout << wordHolderTemp[i] << endl;
            cout << wordHolderTemp[i+1] << endl;
            //increase endIndex and the size
            i++;
        }
        else
        {
            //once we've gotten an endIndex, we merge from the beginIndex till the end
            endIndex = i;
            //call heap sort
            //heapsort(beginIndex, endIndex);
            heapSort(beginIndex, endIndex);
            //set begin to the end so we can parse from there
            beginIndex = i+1;
            endIndex = i+1;
            i++;
            cout << "end of " << i <<  " loop" << endl;
        }

    }
}

int SortingCompetition::getMax()
{
    //determine max length of string
    int mx = wordHolderTemp[0].length();
    for (int i = 1; i < wordHolderTemp.size(); i++)
        //if there is a bigger string length, then store that one as the biggest
        if (wordHolderTemp[i].length() > mx)
            mx = wordHolderTemp[i].length();
    //return the max stringlength
    return mx;
}

// A function to do cnting sort of vector wordHolder according to the digit represented by exp.
void SortingCompetition::countSort(int exp)
{
       vector<string> output (wordHolderTemp.size()); // output array the size of the vector holder
       int i, count[10] = {0};

       // Store count of occurrences in count[]
       for (i = 0; i < wordHolderTemp.size(); i++)
           count[ (wordHolderTemp[i].length()/exp)%10 ]++;

       // Change count[i] so that count[i] now contains actual position of this digit in output[]
       for (i = 1; i < 10; i++)
           count[i] += count[i - 1];

       // Build the output array
       for (i = wordHolderTemp.size() - 1; i >= 0; i--)
        {
            output[count[ (wordHolderTemp[i].length()/exp)%10 ] - 1] = wordHolderTemp[i];
            count[ (wordHolderTemp[i].length()/exp)%10 ]--;
        }

        // Copy the output array to wordHolder, so that wordHolder now contains sorted strings according to size length
        for (i = 0; i < wordHolderTemp.size(); i++)
        {
            wordHolderTemp[i] = output[i];
        }
}

void SortingCompetition::radixsort()
{
    // Find the maximum number to know number of digits
    int m = getMax();

    // Do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i where
    //i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(exp);
}

//Emely's heap sort
//  Heapsort code found in "Data Structures and Algorithms Analysis in Java" by Mark Allen Weiss (2nd Edition)
//  Also doubled checked with code in www.cs.fsu.edu/~breno/COP-4530/slides/21-anim.pdf

//standard heapsort that takes in vector of strings
//heapSort is supposed to take in int begin and int end
void SortingCompetition::heapsort(int begin, int end)
{
    //build the heap
    for(int i=end; i>=begin; i--)
    {
        percDown(i, end);
    }
    //deleteMax
    for(int j=end; j>begin; j--)
    {
        swap(wordHolderTemp[begin], wordHolderTemp[j]);
        percDown(begin, j);
    }
}

int SortingCompetition::leftChild(int i)
{
    return 2 * i + 1;
}

void SortingCompetition::percDown(int i, int n)
{
    int child;
    string temp;

    for(temp = wordHolderTemp[i]; leftChild(i) < n; i=child)
    {
        child = leftChild(i);
        if(child != n-1 && wordHolderTemp[child].compare(wordHolderTemp[child+1]) < 0)
            child++;
        if(temp.compare(wordHolderTemp[child]) < 0)
            wordHolderTemp[i] = wordHolderTemp[child];
        else
    break;
    }
    wordHolderTemp[i] = temp;
}

void SortingCompetition::outputData(char* outputFileName)
{
    string outputFile(outputFileName);
    ofstream output(outputFile.c_str());
    for(int i = 0; i < wordHolderTemp.size(); i++)
    {
        output << wordHolderTemp[i] << endl;
    }
}




//void shiftRight(int* arr, int low, int high)
//takes in the begining and end of the wordHolder
void SortingCompetition::shiftRight(int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;
        /*Check if root is less than left child*/
        if (wordHolderTemp[swapIdx] < wordHolderTemp[leftChild])
        {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (wordHolderTemp[swapIdx] < wordHolderTemp[rightChild]))
        {
            swapIdx = rightChild;
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            string tmp = wordHolderTemp[root];
            wordHolderTemp[root] = wordHolderTemp[swapIdx];
            wordHolderTemp[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;
        }
        else
        {
            break;
        }
    }
    return;
}
void SortingCompetition::heapify(int low, int high)
{
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int midIdx = (high - low -1)/2;
    while (midIdx >= 0)
    {
        shiftRight(midIdx, high);
        --midIdx;
    }
    return;
}
//void heapSort(int* arr, int size)
void SortingCompetition::heapSort(int begin, int end)
{
    //assert(arr);
    //assert(size > 0);
    /*This will put max element in the index 0*/
    heapify(begin, end);
    int high = end - 1;
    while (high > 0)
    {
        /*Swap max element with high index in the array*/
        string tmp = wordHolderTemp[high];
        wordHolderTemp[high] = wordHolderTemp[begin];
        wordHolderTemp[begin] = tmp;
        --high;
        /*Ensure heap property on remaining elements*/
        shiftRight(begin, end);
    }
    return;
}


