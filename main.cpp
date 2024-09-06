#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
#include "user_code.h"
using namespace std;
using namespace std::chrono;


/**
 * @brief Do not modify this code. 
 * 
 */
void question1(string hashtagsPath, string purchasesPath,string pricesPath,string outputPath)
{

    fileIterator hashtags(hashtagsPath);
    fileIterator purchases(purchasesPath);
    fileIterator prices(pricesPath);
    
    auto start = high_resolution_clock::now();

    groupCustomersByHashtags(hashtags, purchases,prices,outputPath);
   
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    auto computeDuration = duration.count() - fileIo;
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    cout << "Total time taken: "<< computeDuration << " microseconds" << endl;

}

void question2()
{   

}


void question3()
{
    
}




//////////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Do not modify this code. FIXME add comments.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv){
    
    string hashtagsPath = argv[1];
    string purchasesPath = argv[2];
    string pricesPath = argv[3];
    string groupsPath = argv[4];
    string outputPath = argv[5];
    question1(hashtagsPath, purchasesPath,pricesPath,outputPath);
    return 0;
}




