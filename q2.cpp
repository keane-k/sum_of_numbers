// Q2: Sum of Numbers
// In each line, first number (digit or spelled-out) is TENS digit, last number is ONES digit,
// combine them to form a two-digit value.
// Sum this value across all lines.

// Given the example:
// 2two4 ---> 24
// Fouruyguyguyfive5 ---> 45
// Sixeighttwo1 ---> 61
// Fivesevensixeight23 ---> 53
// Total sum = 183

#include <iostream> // cin, cout 
#include <fstream>  // file-stream header, needed for <std::ofstream out()>, std::ifstream ('input file stream'), etc.
#include <string>
#include <vector> // this mod lets you hold lists of values of the same type
#include <cctype>
#include <cstring>
using namespace std;

// determines the numerical value of either (1) numbers in string or (2) word-numbers in string
// even though 'input.txt' doesn't have any uppercase char, the given example contains uppercase char (ie. "Fouruyguyguyfive5")
// decoder() also contains the feature to change uppercase char into lowercase to accommodate for this condition
int decoder(const std::string& s, size_t i) 
{
    // First check, if the char at position i is a plain-digit ('7')
    if(std::isdigit(s[i])) // OPTIONAL: `static_cast<unsigned char>(line[i])` prevents crash on certain non-English text
    {
        int d = s[i] - '0'; // turn DIGIT CHARACTER into DIGIT NUMBER
        return d; 
    }

    // Second check, check every spelled-out word to see if it starts exactly at position i
    std::vector<std::string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    // Mirror your {words} with the respective numerical_values
    std::vector<int> numerical_values = {1,2,3,4,5,6,7,8,9};


    for (size_t k = 0; k < words.size(); k++)
    {
        const std::string& word = words[k];

        if (i + word.size() > s.size()) // conduct guard check in the event `word` would run past the end of `s`
        {
            continue; // skip this word, move on to the next word
        }

        bool word_matches = true; // set TRUE initially, if word from `word` and `s` do not match, we'll set to FALSE
        for (size_t j = 0; j < word.size(); j++)
        {
            if (std::tolower(s[i + j]) != word[j]) // In python: if s.lowercase() not equal to word[j], break contact since there's no point checking further
            {
                word_matches = false;
                break;
            }
        }

        
        // But if the word_matches remains TRUE, return the numerical value
        if (word_matches)
        {
            return numerical_values[k];
        }
    }

    // If nothing is matched then return -1
    return -1;
}

// takes the returned value from decoder()
// adds up the first (TENS) and last (ONES) numbers to form the 2-digit number for that specific line in txt
int line_value(const std::string& line)
{
    int first = -1; // to hold the first digit
    int last = -1; // to hold the last digit

    for (size_t i = 0; i < line.size(); i++)
    {
        // decode() returns int numbers
        int d = decoder(line, i);

        // conduct SENTINEL check to determine if decoder() spits out a number or -1, if not -1 (which is good condition), we process further
        if (d != -1)
        {
            // conduct SENTINEL check to determine if this is the first number to be processed or not, if yes, let `first` take this number
            if (first == -1) first = d;
            last = d;
        }
    }

    if (first == -1) return 0; 
    
    // combine first(TENS-DIGIT) and last(ONES-DIGIT) together to become the FULL number
    return first * 10 + last;
}


// takes the 2-digit number from line_value() 
// and keeps adding the decoded number until there are no more lines left in txt - EOF
int sum_of_words(const std::string& file_name)
{
    std::ifstream in(file_name); // set input file
    std ::string line; // initialise an empty string for callback later

    int total = 0; // captures the total sum of all the numbers

    while(std::getline(in, line))
    {
        // call line_value() since it returns numerical values, decoder() is already called within line_value() 
        total += line_value(line);

        // print each line for manual inspection, the decoded value will be shown for you to double-check
        // std::cout << line << "\n";
        // std::cout << "After adding = " << line_value(line) << ", total = " << total << "\n";
    }

    return total; // rmbr to return the total summation value
}


// run the program, using both given example (transferred into "example.txt") and input.txt
int main()
{
    // Check against the given example
    {
        std::string given_example = "example.txt";
        std::cout << "Given Example (expects 183): " << sum_of_words(given_example) << "\n";
    }

    // Check against the real input text file "input.txt"
    {
    std::string real_input = "input.txt";
    std::cout << "input.txt total: " << sum_of_words(real_input) << "\n";
    }

    return 0;
}