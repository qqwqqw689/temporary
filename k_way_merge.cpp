#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

void GenerateRandNum(int n, std::fstream& of);
// clear the content of disk1.txt
void ClearFile1(std::fstream& of);
// clear the content of disk2.txt
void ClearFile2(std::fstream& of);
// get the a specific element in disk1.txt
template <class T>
T GetFileElement(int pos);

template<class T>
class KMergeSort
{
private:
    int _n; // the number of items to sort.
    int _k; // the k of k merge sort.
    int _current_pass;
    int _total_pass;
    int _BufferSize;
    bool (*_compareFunction)(const T &a, const T &b);
    
    // drives the creation of sorted sub-files stored on disk.
    void DivideAndSort();
public:

};

// destructor
template <class T>
KMergeSort<T>::~KMergeSort()
{}

// constructor
template <class T>
KMergeSort<T>::KmergeSort(int n,
                        int k
                        int BufferSize,
                        bool (*compareFunction)(const T &a, const T &b))
    : _n(n)
    , _k(k)
    , _current_pass(0)
    , _BufferSize(BufferSize)
    , _compareFunction(compareFunction)
{
    if((_n % _BufferSize)!=0)
        _total_pass = int(std::log(_n / _BufferSize + 1) / std::log(_k)) + 1;
    else
        _total_pass = int(std::log(_n / _BufferSize) / std::log(_k)) + 1;
}

// constructor
template <class T>
KMergeSort<T>::KmergeSort(int n,
                        int k
                        int BufferSize,)
    : _n(n)
    , _k(k)
    , _current_pass(0)
    , _BufferSize(BufferSize)
{
    if((_n % _BufferSize)!=0)
        _total_pass = int(std::log(_n / _BufferSize + 1) / std::log(_k)) + 1;
    else
        _total_pass = int(std::log(_n / _BufferSize) / std::log(_k)) + 1;
}

template <class T>
void KMergeSort<T>::DivideAndSort()
{
    std::fstream file1("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
    if(!file1.is_open())
    {
        std::cerr << "Error!! The file didn't open.";
        exit(1);
    }

    std::fstream file2("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::in | std::fstream::out);
    if(!file2.is_open())
    {
        std::cerr << "Error!! The file didn't open.";
        exit(1);
    }

    std::vector<T> temp;
    int j=0; // the number of element in temp
    for(int i=0; i<_n; i++)
    {
        T k;
        file1>>k;
        temp.pusk_back(k);
        j++;
        if(j==_BufferSize || i==_n-1)
        {
            if(_compareFunction==NULL)
                std::sort(temp.begin(),temp.end());
            else
                std::sort(temp.begin(),temp.end(),_compareFunction);
            
            for(auto w : temp)
                w>>file2;
            temp.clear();
            j=0;
        }
    }
    file1.close();
    file2.close();
    ClearFile1(file1);
    file1.open("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
    file2.open("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::in | std::fstream::out);
    for(int i=0; i<_n; i++)
    {
        T k;
        file2>>k;
        k>>file1;
    }
    file1.close();
    file2.close();
    ClearFile2(file2);
}



int main()
{
    int n, BufferSize, k;
    std::cout << "Please specify the total number of numbers to sort: \n";
    std::cin >> n;
    // std::cout << "Choose the InputBuffer size and number of merge ways: \n";
    // std::cin >> BufferSize >> k;
    std::fstream file("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
    if(!file.is_open())
    {
        std::cerr << "Error!! The file didn't open.";
        exit(1);
    }

    GenerateRandNum(n,file);
    file.close();
    // Closes the file currently associated with the object, disassociating it from the stream.
    // Any pending output sequence is written to the file.

    return 0;
}

void GenerateRandNum(int n, std::fstream& of)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,n*10);
    for(int i=0; i < n; i++)
    {
        if(i != n-1)
            of << distrib(gen) << '\n';
        else
            of << distrib(gen);
    }
}



void ClearFile1(std::fstream& of)
{
    of.open("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::out | std::fstream::trunc);
    of.close();
}

void ClearFile2(std::fstream& of)
{
    of.open("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::out | std::fstream::trunc);
    of.close();
}

template <class T>
T GetFileElement(int pos)
{
    std::fstream file1("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
    T ret;
    for(int i=0; i<=pos; i++)
    {
        file1>>ret;
    }
    file1.open();

    return ret;
}
