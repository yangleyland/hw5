// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

#include <string>

// Add prototypes of helper functions here

std::set<std::string> stringFinder( std::string in,  std::string floating,int n,int count);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int count=0;
    for (int i=0; i<(int)in.length();i++){
        if (in[i]=='-') {
            count++;
        }
    }
    std::set<std::string> temp = stringFinder(in,floating,0,count);
    std::set<std::string> result;
    for (std::set<std::string>::iterator it=temp.begin(); it!=temp.end();++it){
        if (dict.find(*it) != dict.end()){
            result.insert(*it);
        }
    }
    return result;
    //compare it to dict and remove ones that are not real words

}

// Define any helper functions here
std::set<std::string> stringFinder( std::string in,  std::string floating, int n,int count) {
    if (n==(int)in.length()) {
        std::set<std::string> temp = {in};
        return temp;
    }
    std::set<std::string> answer;
    if (in[n]=='-'){
        for (int i=0; i<(int)floating.length(); i++){
            in[n]=floating[i];
            std::string newFloating = floating.substr(0,i)+floating.substr(i+1);
            //remove value from floating
            std::set<std::string> temp = stringFinder(in,newFloating,n+1,count-1);
            answer.insert(temp.begin(),temp.end());
            // answer.merge(stringFinder(in,newFloating,n+1));
            in[n]='-';
        }
        if ((int)floating.length()< count){
            for (int i=0;i<26;i++){
                in[n]=(char)(i+97);
                std::set<std::string> temp = stringFinder(in,floating,n+1,count-1);
                answer.insert(temp.begin(),temp.end());
                // answer.merge(stringFinder(in,floating,n+1));
                in[n]='-';
            }
        }
    } else {
        std::set<std::string> temp = stringFinder(in,floating,n+1,count);
        answer.insert(temp.begin(),temp.end());
    }

    
    return answer;
}