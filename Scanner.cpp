#include<iostream>
#include<fstream>
#include<string>
#include <set>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: *23
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Adam Cervantes
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n |consonant - pair vowel | consonant - pair vowel n) ^ +


string removeFirst(string s) {
    return s.substr(1, s.size());
}

const char VOWELARR[] = { 'a', 'e', 'i', 'o', 'u', 'I', 'E' };
const char DWZYJARR[] = {'d', 'w', 'z', 'y', 'j'};
const char BGHKMPRARR[] = { 'b', 'g', 'h', 'k', 'm', 'p', 'r' };

set<char> VOWEL(VOWELARR, VOWELARR+7);
set<char> DWZYJ(DWZYJARR, DWZYJARR + 5);
set<char> BGHKMP(BGHKMPRARR, BGHKMPRARR+7);

bool stateQ0QY(string word);
bool stateQY(string word);
bool stateQC(string word);
bool stateQS(string word);
bool stateQT(string word);
bool stateQSA(string word);
bool stateQ0Q1(string word);
bool stateQ0(string word);


bool word(string s)
{

    int state = 0;
    int charpos = 0;
    /* replace the following todo the word dfa  **
    while (s[charpos] != '\0')
      {
        if (state == 0 && s[charpos] == 'a')
        state = 1;
        else
        if (state == 1 && s[charpos] == 'b')
        state = 2;
        else
        if (state == 2 && s[charpos] == 'b')
        state = 2;
        else
        return(false);
        charpos++;
      }//end of while

    // where did I end up????
    if (state == 2) return(true);  // end in a final state
     else return(false);
    */
    return stateQ0(s);
}

// PERIOD DFA 
// Done by: Armando
bool period(string s){
    return s == ".";
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Adam

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, SUBJECT, OBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJECT", "DESTINATION", "PRONOUN", "CONNECTOR" };
string reservedWords[30] = { "masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "m\
ata", "soshite", "shikashi", "dakara", "eofm" };


// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 
//Returns if a word is WORRD1 or WORD2
tokentype whichWord(string s) {
    if (s[s.length() - 1] == 'I' || s[s.length() - 1] == 'E') {
        return WORD2;
    }
    else {
        return WORD1;
    }
}


ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Everett
void scanner(tokentype& tt, string& w)
{

    // ** Grab the next word from the file via fin
    // 1. If it is eofm, return right now.   

    /*  **
    2. Call the token functions (word and period)
       one after another (if-then-else).
       Generate a lexical error message if both DFAs failed.
       Let the tokentype be ERROR in that case.

    3. If it was a word,
       check against the reservedwords list.
       If not reserved, tokentype is WORD1 or WORD2
       decided based on the last character.

    4. Return the token type & string  (pass by reference)
    */

    fin >> w;
    if (w == "eofm") {
        return;
    }
    else if (word(w)) {
        int count = -1;
        for (int i = 0; i < 30; i++) {
            if (w == reservedWords[i]) {
                count = i;
          break;
            }
        }

        switch (count) {
        case -1:
            tt = whichWord(w);
            break;
        case 0:
            tt = VERB;
            break;
        case 1:
            tt = VERBNEG;
            break;
        case 2:
            tt = VERBPAST;
            break;
        case 3:
            tt = VERBPASTNEG;
            break;
        case 4:
            tt = IS;
            break;
        case 5:
            tt = WAS;
            break;
        case 6:
            tt = OBJECT;
            break;
        case 7:
            tt = SUBJECT;
            break;
        case 8:
            tt = DESTINATION;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            tt = PRONOUN;
            break;
        case 14:
        case 15:
        case 16:
        case 17:
            tt = CONNECTOR;
            break;
        }
    }
    else if (period(w)) {
        tt = PERIOD;
    }
    else {
        tt = ERROR;
    }

}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
    
    tokentype thetype;
    string theword;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    fin.open(filename.c_str());

    // the loop continues until eofm is returned.
    while (true)
    {
        scanner(thetype, theword);  // call the scanner which sets
                                    // the arguments  
        if (theword == "eofm") break;  // stop now

        cout << "Type is:" << tokenName[thetype] << endl;
        cout << "Word is:" << theword << endl << endl;
    }

    cout << "End of file is encountered." << endl;
    fin.close();
}// end

//Returns true if c is in the given set, otherwise false: Vowel
bool isVowel(char c) {
    return VOWEL.find(c) != VOWEL.end();
}

//Returns true if c is in the given set, otherwise false: DWZYJ
bool isDWZYJ(char c) {
    return DWZYJ.find(c) != DWZYJ.end();
}

//Returns true if c is in the given set, otherwise false: BGHKMPR
bool isBGHKMPR(char c) {
    return BGHKMP.find(c) != BGHKMP.end();
}

/*
    Represents state Q0
    Calls one of the following states: Q0Q1, QSA, QY, QT, QS, QC, or a false statement
*/
bool stateQ0(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (isDWZYJ(c)) {
        return stateQSA(removeFirst(word));
    }
    else if (isBGHKMPR(c) || c == 'n') {
        return stateQY(removeFirst(word));
    }
    else if (c == 't') {
        return stateQT(removeFirst(word));
    }
    else if (c == 's') {
        return stateQS(removeFirst(word));
    }
    else if (c == 'c') {
        return stateQC(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state Q0Q1
    Calls one of the following states: Q0Q1, QSA, QY, QT, QS, QC, Q0QY, or a false statement
    Returns true if it is the last state
*/
bool stateQ0Q1(string word) {
    if (word.empty()) {
        return true;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (isDWZYJ(c)) {
        return stateQSA(removeFirst(word));
    }
    else if (isBGHKMPR(c)) {
        return stateQY(removeFirst(word));
    }
    else if (c == 't') {
        return stateQT(removeFirst(word));
    }
    else if (c == 's') {
        return stateQS(removeFirst(word));
    }
    else if (c == 'c') {
        return stateQC(removeFirst(word));
    }
    else if (c == 'n') {
        return stateQ0QY(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state QSA
    Calls one of the following states: QoQ1, or a false statement
*/
bool stateQSA(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state QT
    Calls one of the following states: Q0Q1, QSA, or a false statement
*/
bool stateQT(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (c == 's') {
        return stateQSA(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state QS
    Calls one of the following states: Q0Q1, QSA, or a false statement
*/
bool stateQS(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (c == 'h') {
        return stateQSA(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state QC
    Calls one of the following states: QSA, or a false statement
*/
bool stateQC(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (c == 'h') {
        return stateQSA(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state QY
    Calls one of the following states: Q0Q1, QSA, or a false statement
*/
bool stateQY(string word) {
    if (word.empty()) {
        return false;
    }

    char c = word[0];

    if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (c == 'y') {
        return stateQSA(removeFirst(word));
    }
    else {
        return false;
    }
}

/*
    Represents state Q0QY
    Calls one of the following states: QSA, Q0Q1, QT, QC, QY, QS, or a false statement
    Ends by calling true if it is the last state
*/
bool stateQ0QY(string word) {
    if (word.empty()) {
        return true;
    }

    char c = word[0];

    if (isDWZYJ(c)) {
        return stateQSA(removeFirst(word));
    }
    else if (isVowel(c)) {
        return stateQ0Q1(removeFirst(word));
    }
    else if (c == 't') {
        return stateQT(removeFirst(word));
    }
    else if (c == 'c') {
        return stateQC(removeFirst(word));
    }
    else if (isBGHKMPR(c) || c == 'n') {
        return stateQY(removeFirst(word));
    }
    else if (c == 's') {
        return stateQS(removeFirst(word));
    }
    else {
        return false;
    }
}
