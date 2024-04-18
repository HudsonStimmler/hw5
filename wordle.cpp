#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void RecursiveFunc(const std::string& in, const std::string& floating, const std::set<string>& dict, const size_t NumUnknownChars, std::set<string>& answers, size_t position, const std::string& combo);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict){
  // Add your code here
  size_t NumUnknownChars = 0;
  for(size_t i = 0; i < in.size(); i++){
    if(in[i] == '-'){
      NumUnknownChars += 1;
    }
  }
  set<string> answers;
  RecursiveFunc(in, floating, dict, NumUnknownChars, answers, 0, "");
  return answers;  
}

// Define any helper functions here

void RecursiveFunc(const std::string& in, const std::string& floating, const std::set<string>& dict, const size_t NumUnknownChars, set<string>& answers, size_t position, const string& combo){
  if(position == in.size()){
    if(dict.find(combo) != dict.end()){
      answers.insert(combo);
    }
    return;
  }

  // add current character to word
  if(in[position] != '-'){ 
    RecursiveFunc(in, floating, dict, NumUnknownChars, answers, position+1, combo+in[position]);
  }
  else{
    if(NumUnknownChars > floating.length()) {
      for(char curr = 'a'; curr <= 'z'; curr++) {
        string editFloat = floating;
        size_t currPos = editFloat.find(curr);
        if(currPos != string::npos){
          editFloat = editFloat.substr(0, currPos) + floating.substr(currPos + 1);
        }
        RecursiveFunc(in, editFloat, dict, NumUnknownChars-1, answers, position+1, combo+curr);
      }
    } 
    else{
      for(size_t i = 0; i < floating.length(); i++){
        string editFloat = floating;
        char curr = editFloat[i];
        editFloat = editFloat.substr(0, i) + floating.substr(i + 1);
        RecursiveFunc(in, editFloat, dict, NumUnknownChars-1, answers, position+1, combo+curr);
      }
    }
  }
}
