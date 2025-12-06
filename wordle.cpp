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
void getWords(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int windex, std::string& word, std::set<std::string>& palabras);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  // Add your code here
  
  std::set<std::string> palabras;
  std::string word = in;

  getWords(in, floating, dict, 0, word, palabras);
  return palabras;
}

// Define any helper functions here
void getWords(const std::string& in, const std::string& floating, const std::set<std::string>& dict, int windex, std::string& word, std::set<std::string>& palabras){
  //le base case
  //index is at last pos of input and all floating letters have been used
  int sze = in.size();
  if(windex == sze){
    if(floating.empty() == true){//all floating used
      if(dict.find(word) != dict.end()){//find if word exists by using .find() in the dict
        palabras.insert(word);
      }
    }
    return;
  }

  int b = 0;
  for(int i=windex; i<sze; i++){
    if(in[i] == '_' || in[i] == '-'){
      b++;
    }
  }
  if(floating.size() > b){
    return;
  }
  
  //case where da letter is green
  if(in[windex]!='_' && in[windex] != '-'){
    word[windex] = in[windex];
    getWords(in, floating, dict, windex+1, word, palabras);
    return;
  }

  //case where letter slot is empty "_"
  for(char alph = 'a'; alph<='z'; alph++){

    word[windex] = alph;
  
    //check if letter is in floating
    int findex = floating.find(alph);

    if(findex != -1){
      string eFloat = floating;
      eFloat.erase(findex, 1);
      getWords(in, eFloat, dict, windex+1, word, palabras);
    }
    else{
      int numb = b-1;
      if(floating.size() <= numb){
        getWords(in, floating, dict, windex+1, word, palabras);
      }
    }
  }
}

