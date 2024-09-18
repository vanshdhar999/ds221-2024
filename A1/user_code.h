#ifndef USER_CODE_H
#define USER_CODE_H

#include <vector>
#include<map>
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
map<int, vector<string> > getHashtagMap(fileIterator& hashtags){
    map<int, vector<string>> hashtagMap;
    string line, word;
    while (hashtags.hasNext()) {
        line = hashtags.next();
        cout << line << endl;
        stringstream s(line);

        std::vector<string> tokens;

        while (getline(s, word, ',')){
            tokens.push_back(word);
        }

        if(tokens.size() > 1){

            int product_ID = std::stoi(tokens[0]);
            
            vector<string> hashtags;
            for(int i = 1; i < tokens.size(); i++){
                
                if(tokens[i].empty()){
                    continue;
                }
                hashtags.push_back(tokens[i]);
                
            }
            hashtagMap[product_ID] = hashtags;
        }
    }
    return hashtagMap;
}
//#PROMPT#// Give the same function to return a map of customer purchases.
map<int, vector<int> > getCustomerPurchases(fileIterator& purchases){

    map<int, vector<int>> customerPurchases;
    string line, word;
    while (purchases.hasNext()) {
        line = purchases.next();
        cout << "Purchase row: " << line << endl;
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


map<int, map<string, int>> getCustomerInterests(fileIterator& purchases,const map<int, vector<string>>& productHashtags) 
{
    map<int, map<string, int>> customerInterests;
    string line, word;
   
    while (purchases.hasNext()) {
        line = purchases.next();

        
        if (line.empty()) {
            continue;
        }

        stringstream s(line); 
        vector<int> tokens;

        
        while (getline(s, word, ',')) {
            try {
                tokens.push_back(stoi(word));  
            } catch (exception& e) {
                continue;
            }
        }
        if (tokens.size() != 2) {
            continue;  
        }

        int customer_id = tokens[0]; 
        int product_id = tokens[1]; 

        std::cout << "Processing Customer ID: " << customer_id << ", Product ID: " << product_id << endl;

        if (productHashtags.find(product_id) != productHashtags.end()) {
            for (const string& hashtag : productHashtags.at(product_id)) {
                customerInterests[customer_id][hashtag]++;  
                std::cout << "Adding Hashtag: " << hashtag << " for Customer ID: " << customer_id << endl;
            }
        } else {
            cerr << "Warning: Product ID " << product_id << " not found in productHashtags." << endl;
        }
    }
    for(auto& customer : customerInterests){
        cout << "Customer ID: " << customer.first << endl;
        for(auto& interest : customer.second){
            cout << "Interest: " << interest.first << " Frequency: " << interest.second << endl;
        }
    }
    return customerInterests;
}

map<int, vector<string> > getTopKInterests(const map<int, map<string, int>>& customerInterests, int k)
{
    map<int, vector<string>> topKInterests;
    for (const auto& customer : customerInterests) {
        vector<pair<string, int>> interests(customer.second.begin(), customer.second.end());
        sort(interests.begin(), interests.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        vector<string> topK;
        for (int i = 0; i < k && i < interests.size(); i++) {
            topK.push_back(interests[i].first);
        }

        topKInterests[customer.first] = topK;
    }

    for(auto& customer : topKInterests){
        cout << "Customer ID: " << customer.first << endl;
        for(auto& interest : customer.second){
            cout << "Interest: " << interest << endl;
        }
    }
    return topKInterests;
}

vector<vector<int >> groupCustomersByInterestsList(const map<int, vector<string>>& topKInterests, int k ){

    //#PROMPT#// If the interest list is {"tech", "gadget"} and {"gadget", "tech"} then they are the same group.
    //So we need to sort the interests before comparing them.
    vector<vector<int>> groups;
    map<vector<string>, vector<int>> groupMap;
    for(auto& customer : topKInterests){
        vector<string> interests = customer.second;
        sort(interests.begin(), interests.end());
        groupMap[interests].push_back(customer.first);
    }

    for(auto& group : groupMap){
        groups.push_back(group.second);
    }

    for(auto& group : groups){
        cout << "Group: ";
        for(auto& customer : group){
            cout << customer << " ";
        }
        cout << endl;
    }
    return groups;
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
    auto start = high_resolution_clock::now();
    //  Write your code here

    map<int, vector<string> > hashtagMap;
    hashtagMap = getHashtagMap(hashtags);
    cout << "Hashtag Map Size: " << hashtagMap.size() << endl;
    
    map<int, vector<int> > customerPurchases;
    customerPurchases = getCustomerPurchases(purchases);

    purchases.reset();
    hashtags.reset();

    map<int, map<string, int>>  customerInterests;
    customerInterests = getCustomerInterests(purchases, hashtagMap);
    purchases.reset();

    map<int, vector<string>> topKInterests;
    topKInterests = getTopKInterests(customerInterests, k);

    vector<vector<int>> groups;
    groups = groupCustomersByInterestsList(topKInterests, k);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by compute part of the function: "<< duration.count() << " microseconds" << endl;

    vector<int> group;
    for(auto& customerGroup: groups){
        writeOutputToFile(customerGroup, outputFilePath);
    }
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
