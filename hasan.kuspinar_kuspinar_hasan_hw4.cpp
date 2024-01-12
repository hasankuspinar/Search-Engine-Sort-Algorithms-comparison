#include <iostream>
#include<string>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "randgen.h"
#include <chrono>
using namespace std;

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <class Comparable>
inline void myswap(Comparable & obj1,
                 Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <class Comparable>
const Comparable & median3( vector<Comparable> & a,
                          int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ] < a[ left ] )
        myswap( a[ left ], a[ center ] );
    if ( a[ right ] < a[ left ] )
        myswap( a[ left ], a[ right ] );
    if ( a[ right ] < a[ center ] )
        myswap( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    myswap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

template <class Comparable>
void quicksortMedian( vector<Comparable> & a,
                int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                myswap( a[ i ], a[ j ] );
            else
                break;
        }
        myswap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quicksortMedian( a, left, i - 1 );       // Sort small elements
        quicksortMedian( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

template <class Comparable>
void quicksortFirst( vector<Comparable> & a,
                      int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = a[left+1];
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }
        myswap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quicksortFirst( a, left, i - 1 );       // Sort small elements
        quicksortFirst( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

template <class Comparable>
void quicksortRandom( vector<Comparable> & a,
                     int left, int right )
{
    RandGen rand;
    if ( left + 10 <= right )
    {
        int rand_num = rand.RandInt(left,right);
        Comparable pivot = a[rand_num];
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }
        myswap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quicksortRandom( a, left, i - 1 );       // Sort small elements
        quicksortRandom( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

template <class Comparable>
void quicksortMedian( vector<Comparable> & a )
{
    quicksortMedian( a, 0, a.size( ) - 1 );
}

template <class Comparable>
void quicksortFirst( vector<Comparable> & a )
{
    quicksortFirst( a, 0,a.size()-1);
}

template <class Comparable>
void quicksortRandom( vector<Comparable> & a )
{
    quicksortRandom( a, 0,a.size()-1);
}

template <class Comparable>
int binarySearch(vector<Comparable>& myVector, Comparable target)
{
    int left = 0;
    int right = myVector.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (myVector[mid] == target)
        {
            return mid;
        } else if (myVector[mid] < target)
        {
            left = mid + 1;
        } else
        {
            right = mid - 1;
        }
    }

    return -1;
}

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;
    // loop over the passes
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
        // loop over the elements
        for (j = p; j > 0 &&  tmp < a[j-1]; j--)
        {
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

inline int leftChild( int i )
{
    return 2*i+1;
}

template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp=a[i];

    for ( ; leftChild(i) < n; i = child )
    {
        child = leftChild(i);
        if ( child != n-1 && a[ child  ] < a[ child+1 ] )
            child++;
        if ( a[child ] > tmp )
            a[i] = a[ child ];
        else
            break;
    }
    a[ i ] = tmp;
}


template <class Comparable>
void heapsort(vector<Comparable> & a)
{
    // buildHeap
    for (int i = a.size()/2; i >=0; i--)
    percDown(a, i, a.size());

    // sort
    for (int j = a.size() -1; j >0; j--)
    {
        myswap(a[0], a[j]);    // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}

template <class Comparable>
void merge(  vector<Comparable> & a,
             vector<Comparable> & tmpArray,
             int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    // Main loop
    while ( leftPos <= leftEnd && rightPos <= rightEnd )
        if ( a[ leftPos ] <= a[ rightPos ])
            tmpArray[ tmpPos++ ] = a[ leftPos++ ];
        else
            tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    while ( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = a[ leftPos++ ];

    while ( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    // Copy tmpArray back
    for ( int i = 0; i < numElements; i++, rightEnd-- )
        a[ rightEnd ] = tmpArray[ rightEnd ];
}

template <class Comparable>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right )
{
    if ( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

int vector_search_for_sort(const vector<WordItem> & v, string s)
{
    if(!v.empty())
    {
        for(int i = 0; i < v.size(); i++)
        {
            if(v[i].word == s)
            {
                return i;
            }
        }
    }
    return -1;
}

int vector_search(const vector<DocumentItem> & v, string s) //searches the given s in vector of document items and returns the index of it, if it is not found returns -1
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].documentName == s)
        {
            return i;
        }
    }
    return -1;
}

bool tree_has_queries(vector<string> & queries, BinarySearchTree<string,WordItem*> & myTree) //checks if the given tree has the
{                                                                                         // given queries in it returns true if so
    for(const string & query:queries)
    {
        if(myTree.find(query) == "item not found")
        {
            return false;
        }
    }
    return true;
}

bool vector_has_queries(vector<string> & queries, vector<WordItem> & myVector) //checks if the given vector has the
{                                                                                         // given queries in it returns true if so
    for(const string & query:queries)
    {
        WordItem w1;
        w1.word = query;
        if(binarySearch(myVector,w1) == -1)
        {
            return false;
        }
    }
    return true;
}

bool hash_has_queries(HashTable<WordItem> & hTable, vector<string> queries) //checks if the given hash table has the queries in it
{
    for(const string & query:queries)
    {
        WordItem w1;
        w1.word = query;
        if(hTable.find(w1) == NULL)
        {
            return false;
        }
    }
    return true;
}

bool doc_has_queries(vector<string> & queries, BinarySearchTree<string,WordItem*> & myTree, string fName) //checks if the given file in the tree has all the queries in it
{
    for(const string & query:queries)
    {
        if(vector_search(myTree.valueOf(query)->documentList, fName) == -1)
        {
            return false;
        }
    }
    return true;
}

bool doc_has_queries(vector<string> & queries, HashTable<WordItem> & hTable, string fName) //checks if the given file in the hash table has all the queries in it
{
    for(const string & query:queries)
    {
        WordItem w1;
        w1.word = query;
        if(vector_search(hTable.find(w1)->documentList, fName) == -1)
        {
            return false;
        }
    }
    return true;
}

bool doc_has_queries(vector<string> & queries, vector<WordItem> & myVector, string fName) //checks if the given file in the vector has all the queries in it
{
    for(const string & query:queries)
    {
        WordItem w1;
        w1.word = query;
        DocumentItem d;
        d.documentName == fName;
        if(binarySearch(myVector[binarySearch(myVector,w1)].documentList,d) == -1)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int file_count;
    cout << "Enter number of input files: ";
    cin >> file_count;

    vector<string> file_names; //creating a vector to store the document(file) names
    BinarySearchTree<string , WordItem*> Search_Engine; //creating the tree to store the word items
    HashTable<WordItem> Search_Hash(53);
    vector<WordItem> vector1;
    vector<WordItem> vector2;
    vector<WordItem> vector3;
    vector<WordItem> vector4;
    vector<WordItem> vector5;
    vector<WordItem> vector6;

    for(int i = 0; i < file_count; i++)
    {
        string f;
        cout << "Enter " << i + 1 << ". " << "file name: ";
        cin >> f;

        file_names.push_back(f); //adding the file name to the vector
    }
    for(int i = 0; i < file_names.size(); i++)
    {
        string file_name;
        file_name = file_names[i];
        ifstream file1;
        file1.open(file_name);

        char ch;
        DocumentItem doc1;
        WordItem *word1;
        string str;
        str = "";
        while(file1.get(ch)) //getting characters from the file
        {
            if(isalpha(ch)) //if the character is alphabetic making it lowercase and adding it to the string that would become the word
            {
                ch = tolower(ch);
                str += ch;
            }
            else //if the character is not alphabetic not adding this char to the str and inserting the current word string to the hash table and tree
            {
                if(str!= "") //if the str is not empty
                {
                    word1 = new WordItem;
                    doc1.documentName = file_name; //assigning the file name to the document name
                    doc1.count = 1; //making the count 1 since we are adding it for the first time
                    word1->word = str; //assigning the str to the word of the word item object
                    word1->documentList.push_back(doc1); //inserting the document item object to the document list of word item

                    if(vector_search_for_sort(vector1, str) == -1)
                    {
                        vector1.push_back(*word1);
                    }
                    else
                    {
                        int idx = vector_search(vector1[vector_search_for_sort(vector1,str)].documentList, file_name);
                        if(idx != -1)
                        {
                            vector1[vector_search_for_sort(vector1,str)].documentList[idx].count++;
                        }
                        else
                        {
                            vector1[vector_search_for_sort(vector1,str)].documentList.push_back(doc1);
                        }
                    }


                    if(Search_Engine.find(str) == "item not found") //checking if the word is already in the tree or not
                    {
                        Search_Engine.insert(str,word1); //inserting the word item object to the tree
                    }
                    else //if the word is already in the tree
                    {
                        int idx = vector_search(Search_Engine.valueOf(str)->documentList, file_name);
                        if(idx != -1) //checking if the document of the word that is in the tree is the current one
                        {
                            Search_Engine.valueOf(str)->documentList[idx].count++; //if so incrementing the count of the word for that document
                        }
                        else
                        {
                            Search_Engine.valueOf(str)->documentList.push_back(doc1); //if it is not in the document list adding it as a new document to the document list
                        }
                    }
                    if(Search_Hash.find(*word1) == NULL) //searching the hash table for the current word
                    {
                        Search_Hash.insert(*word1); //if it is not found then inserting it
                    }
                    else
                    {
                        int idx1 = vector_search(Search_Hash.find(*word1)->documentList, file_name);
                        if(idx1 != -1) //checking if the document of the word that is in the hash is the current one
                        {
                            Search_Hash.find(*word1)->documentList[idx1].count++; //if so incrementing the count of the word for that document
                        }
                        else
                        {
                            Search_Hash.find(*word1)->documentList.push_back(doc1); //if it is not in the document list adding it as a new document to the document list
                        }
                    }
                    str = ""; //emptying the string for the next word
                }
            }

        }
        //getting the last word of the file since it could not be get above
        if(str!= "")
        {
            word1 = new WordItem;
            doc1.documentName = file_name; //assigning the file name to the document name
            doc1.count = 1; //making the count 1 since we are adding it for the first time
            word1->word = str; //assigning the str to the word of the word item object
            word1->documentList.push_back(doc1); //inserting the document item object to the document list of word item

            if(vector_search_for_sort(vector1, str) == -1)
            {
                vector1.push_back(*word1);
            }
            else
            {
                int idx = vector_search(vector1[vector_search_for_sort(vector1,str)].documentList, file_name);
                if(idx != -1)
                {
                    vector1[vector_search_for_sort(vector1,str)].documentList[idx].count++;
                }
                else
                {
                    vector1[vector_search_for_sort(vector1,str)].documentList.push_back(doc1);
                }
            }

            if(Search_Engine.find(str) == "item not found") //checking if the word is already in the tree or not
            {
                Search_Engine.insert(str,word1); //inserting the word item object to the tree
            }
            else //if the word is already in the tree
            {
                int idx = vector_search(Search_Engine.valueOf(str)->documentList, file_name);
                if(idx != -1) //checking if the document of the word that is in the tree is the current one
                {
                    Search_Engine.valueOf(str)->documentList[idx].count++; //if so incrementing the count of the word for that document
                }
                else
                {
                    Search_Engine.valueOf(str)->documentList.push_back(doc1); //if it is not in the document list adding it as a new document to the document list
                }
            }
            if(Search_Hash.find(*word1) == NULL) //searching the hash table for the current word
            {
                Search_Hash.insert(*word1); //if it is not found then inserting it
            }
            else
            {
                int idx1 = vector_search(Search_Hash.find(*word1)->documentList, file_name);
                if(idx1 != -1)//checking if the document of the word that is in the hash is the current one
                {
                    Search_Hash.find(*word1)->documentList[idx1].count++; //if so incrementing the count of the word for that document
                }
                else
                {
                    Search_Hash.find(*word1)->documentList.push_back(doc1); //if it is not in the document list adding it as a new document to the document list
                }
            }
        }
        file1.close();
    }
    Search_Hash.printInfo();
    cout << endl;
    vector2 = vector1;
    vector3 = vector1;
    vector4 = vector1;
    vector5 = vector1;
    vector6 = vector1;

    string queries;
    cout << "Enter queried words in one line: ";

    cin.ignore();
    getline(cin, queries); // getting a line of input

    istringstream iss(queries);
    char ch;
    vector<string> query_list;
    string word;
    word = "";
    while (iss.get(ch)) //getting characters
    {
        if(isalpha(ch)) //
        {
            ch = tolower(ch);
            word += ch;
        }
        else
        {
            if(word != "")
            {
                query_list.push_back(word); //adding the word to a vector to further use them
            }

            word = "";
        }
    }
    if(word != "")
    {
        query_list.push_back(word);
    }

    //Insertion Sort
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(vector1);
    auto InsertionSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);


    //Heap Sort
    start = std::chrono::high_resolution_clock::now();
    heapsort(vector2);
    auto HeapSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    //Merge Sort
    start = std::chrono::high_resolution_clock::now();
    mergeSort(vector3);
    auto MergeSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    //Quick Sort(median)
    start = std::chrono::high_resolution_clock::now();
    quicksortMedian(vector4);
    auto QuickSortMedianTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    //Quick Sort(first)
    start = std::chrono::high_resolution_clock::now();
    quicksortFirst(vector5);
    auto QuickSortFirstTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    //Quick Sort(random)
    start = std::chrono::high_resolution_clock::now();
    quicksortRandom(vector6);
    auto QuickSortRandomTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

    //Tree
    int k = 100;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        //-----------------------------------------TREE--------------------------------------------------------
        bool query_not_found = false; //a bool to check if queries are in the files
        if (!tree_has_queries(query_list, Search_Engine)) //checking if the queries are in the tree
        {
            if(i == 0)
                cout << "No document contains the given query" << endl; //if they are not in the tree
        } else //if they are in the tree
        {
            for (const string &file_name: file_names) //iterating over file names
            {
                if (doc_has_queries(query_list,Search_Engine,file_name)) //checking if the file contains the queries
                {
                    if(i == 0)
                        cout << "In Document " << file_name << ", ";

                    for (const string &query: query_list) //iterating over words to display their values
                    {
                        vector<DocumentItem> documents = Search_Engine.valueOf(query)->documentList;
                        int idx = vector_search(documents, file_name);
                        if(i == 0)
                            cout << query << " found "<< documents[idx].count << " times";

                        if (query != query_list[query_list.size() - 1] && (i == 0)) {
                            cout << ", ";
                        }
                    }
                    if(i == 0)
                        cout << "." << endl;
                    query_not_found = true; //if neither of the files contain the queries the variable is false
                }
            }

            if (!query_not_found && (i == 0)) //if neither of the files contain the queries, displaying the info for that
            {
                cout << "No document contains the given query" << endl;
            }
        }
        //-----------------------------------------TREE--------------------------------------------------------
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);


    
    //Hash Table
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        //-----------------------------------------HASH--------------------------------------------------------
        bool query_not_found = false; //a bool to check if queries are in the files
        if (!hash_has_queries(Search_Hash, query_list)) //checking if the queries are in the hash table
        {
            if(i == 0)
                cout << "No document contains the given query" << endl; //if they are not in the tree
        } else //if they are in it
        {
            for (const string &file_name: file_names) //iterating over file names
            {
                if (doc_has_queries(query_list,Search_Hash,file_name)) //checking if the file contains the queries
                {
                    if(i == 0)
                        cout << "In Document " << file_name << ", ";

                    for (const string &query: query_list) //iterating over words to display their values
                    {
                        WordItem w1;
                        w1.word = query;
                        vector<DocumentItem> documents = Search_Hash.find(w1)->documentList;
                        int idx = vector_search(documents, file_name);
                        if(i == 0)
                            cout << query << " found "<< documents[idx].count << " times";

                        if (query != query_list[query_list.size() - 1] && (i == 0)) {
                            cout << ", ";
                        }
                    }
                    if(i == 0)
                        cout << "." << endl;
                    query_not_found = true; //if neither of the files contain the queries the variable is false
                }
            }

            if (!query_not_found && (i == 0)) //if neither of the files contain the queries, displaying the info for that
            {
                cout << "No document contains the given query" << endl;
            }
        }
        //-----------------------------------------HASH--------------------------------------------------------
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
    (std::chrono::high_resolution_clock::now() - start);

    //Binary Search
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {

        bool query_not_found = false; //a bool to check if queries are in the files
        if (!vector_has_queries(query_list, vector2)) //checking if the queries are in the vector
        {
            if(i == 0)
                cout << "No document contains the given query" << endl; //if they are not in the tree
        } else //if they are in it
        {
            for (const string &file_name: file_names) //iterating over file names
            {
                if (doc_has_queries(query_list,vector2,file_name)) //checking if the file contains the queries
                {
                    if(i == 0)
                        cout << "In Document " << file_name << ", ";

                    for (const string &query: query_list) //iterating over words to display their values
                    {
                        WordItem w1;
                        w1.word = query;
                        //int idx1 = vector_search_for_sort(vector3,query);//vector_search_for_sort(vector1,query);
                        int idx1 = binarySearch(vector2,w1);
                        vector<DocumentItem> documents = vector2[idx1].documentList;
                        int idx = vector_search(documents, file_name);
                        if(i == 0)
                            cout << query << " found "<< documents[idx].count << " times";

                        if (query != query_list[query_list.size() - 1] && (i == 0)) {
                            cout << ", ";
                        }
                    }
                    if(i == 0)
                        cout << "." << endl;
                    query_not_found = true; //if neither of the files contain the queries the variable is false
                }
            }

            if (!query_not_found && (i == 0)) //if neither of the files contain the queries, displaying the info for that
            {
                cout << "No document contains the given query" << endl;
            }
        }

    }
    auto BinarySearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);


    cout << "\nBinary Search Tree Time: " << BSTTime.count() / k << "\n";
    cout << "Hash Table Time: " << HTTime.count() / k << "\n";
    cout << "Binary Search Time: " << BinarySearchTime.count() / k << "\n";
    cout << "\nQuick Sort(median) Time: " << QuickSortMedianTime.count() << "\n";
    cout << "Quick Sort(random) Time: " << QuickSortRandomTime.count() << "\n";
    cout << "Quick Sort(first) Time: " << QuickSortFirstTime.count() << "\n";
    cout << "Merge Sort Time: " << MergeSortTime.count() << "\n";
    cout << "Heap Sort Time: " << HeapSortTime.count() << "\n";
    cout << "Insertion Sort Time: " << InsertionSortTime.count() << "\n";

    if(BSTTime.count()/k > HTTime.count()/k)
    {
        cout << "Speed Up BST/HST: " << ((BSTTime.count() / k)*1.0) / (HTTime.count() / k) << endl;
    }
    else
    {
        cout << "Speed Up HST/BST: " << ((HTTime.count() / k)*1.0) / (BSTTime.count() / k) << endl;
    }
    if(MergeSortTime.count()/k > QuickSortMedianTime.count()/k)
    {
        cout << "Speed Up Merge Sort/Quick Sort(Median): " << (MergeSortTime.count()*1.0) / QuickSortMedianTime.count() << endl;
    }
    else
    {
        cout << "Speed Up Quick Sort(Median)/Merge Sort: " << (QuickSortMedianTime.count()*1.0) / MergeSortTime.count() << endl;
    }
    if(HeapSortTime.count()/k > QuickSortMedianTime.count()/k)
    {
        cout << "Speed Up Heap Sort/Quick Sort(Median): " << (HeapSortTime.count()*1.0) / QuickSortMedianTime.count() << endl;
    }
    else
    {
        cout << "Speed Up Quick Sort(Median)/Heap Sort: " << (QuickSortMedianTime.count()*1.0) / HeapSortTime.count() << endl;
    }
    if(InsertionSortTime.count()/k > QuickSortMedianTime.count()/k)
    {
        cout << "Speed Up Insertion Sort/Quick Sort(Median): " << (InsertionSortTime.count()*1.0) / QuickSortMedianTime.count() << endl;
    }
    else
    {
        cout << "Speed Up Quick Sort(Median)/Insertion Sort: " << (QuickSortMedianTime.count()*1.0) / InsertionSortTime.count() << endl;
    }


    if(BSTTime.count()/k > BinarySearchTime.count()/k)
    {
        cout << "\nSpeed Up Binary Search Tree / Binary Search Time: " << ((BSTTime.count() / k)*1.0) / (BinarySearchTime.count() / k) << endl;
    }
    else
    {
        cout << "\nSpeed Up Binary Search / Binary Search Tree Time: " << ((BinarySearchTime.count() / k)*1.0) / (BSTTime.count() / k) << endl;
    }
    if(BinarySearchTime.count()/k > HTTime.count()/k)
    {
        cout << "Speed Up Binary Search / Hash Table Time: " << ((BinarySearchTime.count() / k)*1.0) / (HTTime.count() / k) << endl;
    }
    else
    {
        cout << "Speed Up Hash Table / Binary Search Time: " << ((HTTime.count() / k)*1.0) / (BinarySearchTime.count() / k) << endl;
    }








    return 0;
}
