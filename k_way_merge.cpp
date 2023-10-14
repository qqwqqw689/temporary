#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

void GenerateRandNum(int n, std::fstream& of);
// clear the content of disk1.txt
void ClearFile1();
// clear the content of disk2.txt
void ClearFile2();
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
    int _BufferSize;
    bool (*_compareFunction)(const T &a, const T &b);
    
    // drives the creation of sorted sub-files stored on disk.
    void DivideAndSort();
public:
    ~KMergeSort();
    void Sort();
    KMergeSort(int n,int k,int BufferSize,bool (*compareFunction)(const T &a, const T &b));
    KMergeSort(int n,int k,int BufferSize);
};

// destructor
template <class T>
KMergeSort<T>::~KMergeSort()
{}

// constructor
template <class T>
KMergeSort<T>::KMergeSort(int n,
                        int k,
                        int BufferSize,
                        bool (*compareFunction)(const T &a, const T &b))
    : _n(n)
    , _k(k)
    , _current_pass(0)
    , _BufferSize(BufferSize)
    , _compareFunction(compareFunction)
{

}

// constructor
template <class T>
KMergeSort<T>::KMergeSort(int n,
                        int k,
                        int BufferSize)
    : _n(n)
    , _k(k)
    , _current_pass(0)
    , _compareFunction(NULL)
    , _BufferSize(BufferSize)
{

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
        temp.push_back(k);
        j++;
        if(j==_BufferSize || i==_n-1)
        {
            if(_compareFunction==NULL)
                std::sort(temp.begin(),temp.end());
            else
                std::sort(temp.begin(),temp.end(),_compareFunction);
            
            for(auto w : temp)
                file2 << w << '\n';
            temp.clear();
            j=0;
        }
    }
    file1.close();
    file2.close();
    ClearFile1();
    file1.open("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
    file2.open("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::in | std::fstream::out);
    for(int i=0; i<_n; i++)
    {
        T k;
        file2>>k;
        file1<<k<< '\n';
    }
    file1.close();
    file2.close();
    ClearFile2();
}

// sort the data
template <class T>
void KMergeSort<T>::Sort()
{
    DivideAndSort();

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

    file1.close();
    file2.close();

    _current_pass = 1;

    std::vector<std::pair<int,int>> index(_k);
    // (the index of the current element, the number of remaining elements)

    for(;; _current_pass++)
    {
        int capacity = _BufferSize*std::pow(_k,(_current_pass-1));
        if(capacity > _n)
            break;
        int real_capacity; // the real number of element in a branch.
        // Elements that need to be arranged for each branch
        int come_to_end = 1; // if current pass have come to the end.
        int total_num = _n;
        int how_many_pairs; // the index of the last valid pairs in index(vector).
        file1.open("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
        file2.open("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::in | std::fstream::out);

        while(come_to_end)
        {
            for(int i=0; i<_k; i++)
            {
                if(total_num==0)
                {
                    come_to_end=0;
                    break;
                }

                if(total_num >= capacity)
                {
                    real_capacity = capacity;
                    index[i].second = real_capacity;
                    index[i].first = _n - total_num;
                    total_num -= real_capacity;
                    how_many_pairs = i;
                }
                else
                {
                    real_capacity = total_num;
                    index[i].second = real_capacity;
                    index[i].first = _n - total_num;
                    total_num -= real_capacity;
                    come_to_end = 0; // current pass have come to the end.
                    how_many_pairs = i;
                    break;
                }
            }

            while(1)
            {
                int min_num_index;
                T min_num = std::numeric_limits<T>::max();
                for(int i=0; i<=how_many_pairs; i++)
                {
                    if(index[i].second!=0 && GetFileElement<T>(index[i].first) < min_num)
                    {
                        min_num = GetFileElement<T>(index[i].first);
                        min_num_index = i;
                    }
                }
                file2 << min_num << '\n';
                index[min_num_index].first++;
                index[min_num_index].second--;
                int all_empty = 1; // if all the branchs is empty.
                for(int i=0; i<=how_many_pairs; i++)
                {
                    if(index[i].second!=0)
                        all_empty = 0;
                }
                if(all_empty==1)
                    break;
            }
        }
        file1.close();
        file2.close();

        ClearFile1();
        
        file1.open("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::in | std::fstream::out);
        file2.open("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::in | std::fstream::out);

        T temp;
        for(int i=0; i<_n; i++)
        {
            file2 >> temp;
            file1 << temp << '\n';
        }
        
        file1.close();
        file2.close();
        ClearFile2();
    }
}

int main()
{
    ClearFile1();
    ClearFile2();
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

    KMergeSort<int> test(10000,10,10);
    test.Sort();
    
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
    }
}



void ClearFile1()
{
    std::fstream file1("C:\\Users\\Lenovo\\projects\\cpp\\disk1.txt", std::fstream::out | std::fstream::trunc);
    file1.close();
}

void ClearFile2()
{
    std::fstream file2("C:\\Users\\Lenovo\\projects\\cpp\\disk2.txt", std::fstream::out | std::fstream::trunc);
    file2.close();
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
    file1.close();

    return ret;
}
