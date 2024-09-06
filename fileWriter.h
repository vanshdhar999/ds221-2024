#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;


// define an extern variable to store and increment the duration for each function call
// supprress the warning for global variable
#pragma GCC diagnostic ignored "-Wreturn-type"
extern auto fileIo = 0;


/**
 * @brief Do not modify this code. 
 * 
 */
void writeOutputToFile(const vector<int> group,string outputPath)
{
    auto start = high_resolution_clock::now();
    ofstream outputFile(outputPath);
    if (!outputFile)
    {
        cerr << "Failed to create output file." << endl;
        return;
    }

    for (const auto &value : group)
    {
        outputFile << value << ",";
    }

    outputFile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    fileIo += duration.count();
    cout<<"Time taken by file write: "<<duration.count()<<" microseconds"<<endl;
    cout<<"Total time taken by file write: "<<fileIo<<" microseconds"<<endl;

}
