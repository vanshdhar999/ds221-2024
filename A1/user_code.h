#ifndef USER_CODE_H
#define USER_CODE_H

#include <vector>
#include<unordered_map>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include "fileIterator.h"
#include "fileWriter.h"
#include<sstream>
using namespace std;



//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
unordered_map<int, vector<string> > getHashtagMap(fileIterator& hashtags){

    unordered_map<int, vector<string>> productHashtags;
    string line, word;
    while (hashtags.hasNext()) {
        line = hashtags.next();
        stringstream s(line);

        std::vector<string> tokens;


        while (getline(s, word, ',')){

            tokens.push_back(word);
        }

        if(tokens.size() > 1){

            int product_ID = std::stoi(tokens[0]);
            
            vector<string> hashtags;
            for(int i = 1; i < tokens.size(); i++){
                hashtags.push_back(tokens[i]);
                
            }

            productHashtags[product_ID] = hashtags;
        }
    return productHashtags;
    }
}
//PROMPT#// Give the same function to return a map of customer purchases.
unordered_map<int, vector<int> > getCustomerPurchases(fileIterator& purchases){

    unordered_map<int, vector<int>> customerPurchases;
    string line, word;
    while (purchases.hasNext()) {
        line = purchases.next();
        stringstream s(line);

        std::vector<int> tokens;

        while (getline(s, word, ',')){

            tokens.push_back(std::stoi(word));
        }

        if(tokens.size() > 1){

            int customer_ID = tokens[0];
            
            vector<int> purchases;
            for(int i = 1; i < tokens.size(); i++){
                purchases.push_back(tokens[i]);
                
            }
            customerPurchases[customer_ID] = purchases;
        }
    }
    return customerPurchases; 
}

//Prompt#// Write a function to read customer purchases and return a map of interests list for each customer.

unordered_map<int, vector<string> > getCustomerInterests(fileIterator& purchases, fileIterator& prices){

    unordered_map<int, vector<string>> customerInterests;
    string line, word;
    while (purchases.hasNext()) {
        line = purchases.next();
        stringstream s(line);

        std::vector<int> tokens;

        while (getline(s, word, ',')){

            tokens.push_back(std::stoi(word));
        }

        if(tokens.size() > 1){

            int customer_ID = tokens[0];
            
            vector<string> interests;
            for(int i = 1; i < tokens.size(); i++){
                interests.push_back(tokens[i]);
                
            }
            customerInterests[customer_ID] = interests;
        }
    }
    return customerInterests; 
}

/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param hashtags 
 * @param purchases 
 * @param prices 
 */
void groupCustomersByHashtags(fileIterator& hashtags, fileIterator& purchases,fileIterator& prices, int k, string outputFilePath)
{
    //Use this to log compute time    
    auto start = high_resolution_clock::now();
    //  Write your code here
    std::cout << "Question 1 Starting ...." << std::endl;

    unordered_map<int, vector<string> > hashtagMap;
    hashtagMap = getHashtagMap(hashtags);

    unordered_map<int, vector<int> > customerPurchases;
    customerPurchases = getCustomerPurchases(purchases);


    


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by compute part of the function: "<< duration.count() << " microseconds" << endl;

    // Use the below utility function to write the output to a file
    // Call this function for every group as a vector of integers
    vector<int> group;
    writeOutputToFile(group, outputFilePath);
    return;
}

//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param customerList 
 * @param purchases 
 * @param prices
 */
float calculateGroupAverageExpense(vector<int> customerList, fileIterator& purchases,fileIterator& prices){
    //Use this to log compute time    
    auto start = high_resolution_clock::now();
    //  Write your code here
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by this function: "<< duration.count() << " microseconds" << endl;

    return 0.0;
}


//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param hashtags 
 * @param purchases 
 * @param prices
 * @param newHashtags
 * @param k
 * @param outputFilePath
 */
void groupCustomersByHashtagsForDynamicInserts(fileIterator& hashtags, fileIterator& purchases,fileIterator& prices,vector<string> newHashtags, int k, string outputFilePath){
    //Use this to log compute time    
    auto start = high_resolution_clock::now();
    //  Write your code here
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by compute part of the function: "<< duration.count() << " microseconds" << endl;

    // Use the below utility function to write the output to a file
    // Call this function for every group as a vector of integers
    vector<int> group;
    writeOutputToFile(group, outputFilePath);
    return;
    
}



#endif // USER_CODE_H
