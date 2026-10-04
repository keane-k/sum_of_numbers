#include <iostream> // cin, cout 
#include <fstream> // std::ifstream ('input file stream')
#include <string>
#include <vector> // this mod lets you hold lists of values of the same type
#include <cctype>
#include <cstring>
using namespace std;

/*
int main() {
    cout << "Hello World!" << endl;  // <std::cout> writes to the screen
    std::cout << "Given Example (expects 183)\n" << "My solution: " << "183";
    return 0;
}
*/

/////////////////////////////////////////////

/* Test Grounds 

// For Variables & Types; you will always write in this format <type name = value;>
int x = 5; // x holds a whole number
std::string s = "2two4"; // 's' holds a text, this is basically <string> in python but C++ format
                         // indexing works the same in python, count starts from 0

int main() // setting this up just to avoid error line from plaguing the screen
           // FYI: naming convention is important, we use `main()` then we don't need to specify a return value
           // If you use `int example()`, you need to specify a returned integer number else there'll be error 
{
    // Building the `for` loop
    for (int i = 0; i < s.size(); i++)  // start with `i=0`, as long as `i < 5`, 
                                        // run code inside {}
                                        // After each run, do `i++` (increase i by 1) 
    {
        std::cout << "i is now: " << i << "\n";
    }
    std::cout << "Loop finished\n";

    // Building an `if` statement
    if (x==5) // `==` means 'is equal to', `=` means 'assign a value', know the difference
    {
        std::cout << "x is five\n";
    }
    // return 0;
}
*/

/////////////////////////////////////////////

/* Q2 workings*/
/* Let's figure out how to find the first and last digit of this text */

/*
std::string line = "a2b4c9d";
int main()
{
    int first = -1; // to hold the first digit we find, `-1` is a placeholder 
                    // implying "haven't found anything yet", 
                    // since no real digit is ever `-1`, it's a safe flag to use
    int last = -1;  // to hold the last digit we find

    for (size_t i = 0; i < line.size(); ++i) // use <type> `size_t` instead of `int` for loop counter (best use for <string> or <vector> types)
                                             // it's a whole-number <type> meant for sizes/indexes - you can just treat it like `int`
                                             // Why use `size_t` instead of `int`?
                                             // -> `.size()` returns a `size_t`, and matching types avoids a compiler warning
                                             // `i++` and `++i` do the same thing here 'increase by 1' but their math process is different
    {   
        std::cout << "Looking at index " << i << ", character '" << line[i] << "'";

        if (std::isdigit(static_cast<unsigned char>(line[i]))) // `std::isdigit()` is a func that takes one character and answers True/False
                                                               // `static_cast<unsigned char>(line[i])` is a technical safety to prevent a RARE CRASH on certain non-English text
                                                               // but it essentially means "the character at position i"                                                                
        {
            int d = line[i] - '0'; // every character is stored as a number in C++, character '0' is stored as number 48, '1' as 49 and so on
                                   // so if line[i] = '7' <string>, '7' - '0' = 55 - 48 = 7 <int>
                                   // tl;dr - this is how you turn a DIGIT CHARACTER into DIGIT NUMBER
            std::cout << " -> IS A DIGIT, value = " << d;
            
            if (first == -1) first = d; // `first = -1` if we haven't recorded the first digit yet, thus, the first number digit we get becomes `first = first_digit`
            last = d; // no `if` guard, thus will run every single time we find a digit - by the time the loop ends, `last` holds whichever digit was found last
        }
        std:cout << "\n";
    }
    std::cout << "\nFinal State: first = " << first << "  last = " << last << "\n";

}
*/


/* However, our soln above can only detect numerical characters ('2') in text, 
it CANNOT detect words conveying numerical values ('five'). 
And so, we build a function that checks one position at a time......
But before that, let's learn how function works in C++, 
it operates similarly to python, requiring an input and you need to specify the return value */

/* Building Block: functions*/
/*
int square(int n)
{
    return n * n;
}

int main()
{
    int result = square(4); // calling the `square()` function
                            // note how we always adhere to <type name = value;> format
    std::cout << "square(4) = " << result << "\n";

    // another way of calling and printing together in one line
    std::cout << "square(7) = " << square(7) << "\n";
}
*/


/* Building Block: function that report 'I found nothing' */
/* We want a function that answers one of two kinds of questions:
    1) yes, a number starts here and it's worth X
    2) no, nothing starts here
   Since there isn't a digit value that naturally means "no", we can use a SENTINEL again
   - just like `first = -1` meant "nothing found yet" in earlier examples.
   Here, a function returns `-1` to mean "no" or "nothing is found". 
   TLDR; we're learning how to create a function that tells us 'no' */

// if number is positive, double it, else, return `-1` --> this is our 'no'
/*
int double_if_positive(int n)
{
    if (n > 0)
    {
        return n * 2;
    }
    return -1;
}

int main()
{
    std::cout << double_if_positive(5) << "\n";  // this will print 10
    std::cout << double_if_positive(-3) << "\n"; // this will print -1
}
*/
// Note: `return` isn't just "hand back a value", but it's also "stop running this function right now"


/* Building Block: asking "does this exact text start at this position?" */
/* We need a way to check "does the string, starting at index `i`, spell out a specific word?" 
   C++'s `std::string` has a built-in tool for this called `.compare(...)`.
   --> How to use `.compare()`?
   ----> .compare(starting_index, how_many_chars_to_compare, what_to_compare_against)
   Expected output: 0 for "yes", -1 for "no" */
/*
int main()
{
    std::string line = "catdog";

    // does line, starting at index 0, for 3 characters (inclusive of index char), equal "cat"?
    int result1 = line.compare(0, 3, "cat");
    std::cout << "Comparing line start at 0 for 3 chars to \"cat\": " << result1  << "\n"; // returns 0 - means TRUE

    // does line, starting at index 3, for 3 characters (inclusive of index char), equal "dog"?
    int result2 = line.compare(3, 3, "dog");
    std::cout << "Comparing line start at 3 for 3 chars to \"dog\": " << result2  << "\n"; // returns 0 - means TRUE

    // FALSE SCENARIO - does line, starting at index 0, for 3 characters (inclusive of index char), equal "dog"?
    int result3 = line.compare(0, 3, "dog");
    std::cout << "Comparing line start at 0 for 3 chars to \"dog\": " << result3  << "\n"; // returns -1 - means FALSE

    return 0;
}
*/


/* Building Block: a `vector` - a list of multiple values */
/* Every variable thus far has held exactly one value, but....
   `std::vector` holds a whole LIST of values of the SAME TYPE that you can loop over. */
/*
int main()
{
    // Initialize vector with a list of strings, note how this is formatted and that list bracket is {} instead of []
    std::vector<std::string> words = {"one", "two", "three"};

    std::cout << "Number of words in this list: " << words.size() << "\n";

    // Create a for loop that loops through `words` and return the word at the specific index
    for (size_t i = 0; i < words.size(); i++)
    {
        std::cout << "Word at index " << i << " is " << words[i] << "\n";
    }

    return 0;
}
*/


/* Now that we have all these building blocks, let's proceed with the next phase of answering Q2
   Recall, our soln above can only detect numerical characters ('2') in text, 
   it CANNOT detect words conveying numerical values ('five').
   Let us build that function to resolve it now. */

/* This function answers: "does a digit or a number-word start at position `i` in this string?"
   - This would require two parallel lists --> one for the words, one for their values
   - And then we loop through them checking each one with `.compare()`. */

// DEPRECATED: THIS VERSION DOESN'T DISTINGUISH BETWEEN lowercase & UPPERCASE CHARS, UPDATED VERSION FOUND BELOW....
// this <decoder()> will take an input string, and an index i; it'll be put up against our digit and number-word detector
/*
int decoder(const std::string& s, size_t i) // don't worry about `const` and `&`, 
                                            // just know it means "s is the string that got passed in, and this function
                                            // won't modify your original."
                                            // <size_t i> is the index from the `main()` function, keep this in mind
{
    // First check, if the char at position i is a plain-digit ('7'), rmbr to '7' - '0'
    if(std::isdigit(s[i])) // OPTIONAL: rmbr `static_cast<unsigned char>(line[i])` prevents crash on certain non-English text
    {
        int d = s[i] - '0'; // tl;dr - this is how you turn a DIGIT CHARACTER into DIGIT NUMBER
        return d; 
    }


    // Otherwise,
    // Second check, check every spelled-out word to see if it starts exactly at position i
    std::vector<std::string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    // Mirror your {words} with the respective numerical_values
    std::vector<int> numerical_values = {1,2,3,4,5,6,7,8,9};

    // Create a for loop that loops through `words` and use `.compare()`, if `.compare()` is TRUE, return the numerical_value
    // --> How to use `.compare()`?
    // ----> list.compare(starting_index, how_many_chars_to_compare(len), what_to_compare_against)
    for (size_t k = 0; k < words.size(); k++)
    {
        if(s.compare(i, words[k].size(), words[k]) == 0) // this is how we say if compare() result is TRUE or FALSE
                                                         // rmbr, compare() returns 0 if TRUE, and returns -1 if FALSE
        {
            return numerical_values[k];
        }
    }

    // If nothing is matched then return -1
    return -1;
}
*/

// main() is where we will parse the string, call the decoder() func and print the result we want to see
/*
int main()
{
    std::string s = "eighttwo1";

    // lets run some test,  call the function, parse the string and randomly choose any index
    std::cout << "decoder(s, 0) = " << decoder(s,0) << " (expect 8, 'eight' starts here)" << "\n";
    std::cout << "decoder(s, 1) = " << decoder(s,1) << " (expect -1, nothing starts here)" << "\n";
    std::cout << "decoder(s, 5) = " << decoder(s,5) << " (expect 2, 'two' starts here)" << "\n";
    std::cout << "decoder(s, 8) = " << decoder(s,8) << " (expect 1, plain digit)" << "\n";
}
*/


/* CORE FUNCTION: line_value() & decoder() */
/* Now that we have decoder(), let's return back to our very first starting point of putting the 2 numbers together
   using `first = -1` and `last = -1`, but this time round, values return from decoder() will be used.
   How the workflow looks like:
   text --> line_value() which calls decoder() --> text gets processed by decoder() --> spits out value for line_value() to take */
/*
int line_value(const std::string& line)
{
    int first = -1; // to hold the first digit
    int last = -1; // to hold the last digit

    for (size_t i = 0; i < line.size(); i++)
    {
        // we no longer need the <if> statement here to check "if digit or not" since decode() returns numbers
        // we also no longer need to do the whole <'7' - '0'> thing since decode() is returning int numbers
        int d = decoder(line, i);

        // do the SENTINEL check to determine if decoder() spits out a number or -1, if no, we process further
        if (d != -1)
        {
            // do SENTINEL check to determine if this is the first number to be processed or not, if yes, let `first` take this number
            if (first == -1) first = d;
            last = d;
        }
    }

    if (first == -1) return 0; // if the line has no numbers in it at all (our database all have numbers)
                               // This is just a safeguard against a crash should both `first` and `last` be `-1`, we won't catch the final compuation of `-11`
    
    // combine first(TENS-DIGIT) and last(ONES-DIGIT) together to become the FULL number
    return first * 10 + last;
}
*/
/*
int main()
{
    std::string line = "eightwo1";
    std::string line2 = "Fouruyguyguyfive5";
    std::string line3 = "Sixeighttwo1";
    std::string line4 = "Fivesevensixeight23";

    // lets run some test, call the line_value() func, no need to parse the string or choose any index
    std::cout << line_value(line) << "\n";
    std::cout << line_value(line2) << "\n";
    std::cout << line_value(line3) << "\n";
    std::cout << line_value(line4) << "\n";
    
    return 0;
}
*/


// We have line_value() to determine the 2 digit number in line using decoder()
/* line_value() answers "what's the two-digit value of one line", now we need a function that does that for EVERY LINE in a file and add the results up
   - New pieces required:
   1) a running total that increases across loop iterations
   2) `std::ifstream` + `std::getline` to pull lines out of a real file one at a time
   
   We'll start small with building blocks first*/

/* Building block (1): a running total*/
/* we used `first`|`last` in line_value() that gets updated as a loop runs, we want a "running total" that adds everything instead of overwriting */
/*
int main()
{
    std::vector<int> numbers = {10, 20, 30};

    int total = 0; // start at 0 -- means "nothing added yet"

    for (size_t i = 0; i < numbers.size(); i++) // `for` loop loops through the list 'numbers'
    {
        total = total + numbers[i]; // tallying up each count as list 'numbers' is being looped through
                                    // another way of writing this is:
                                    // total += numbers[i];

        // print some results
        std::cout << "After adding " << numbers[i] << ", total = " << total << "\n";
        
    }

    std::cout << "Final Total = " << total << "\n";
    return 0;
}
*/


/* Building block (2): reading a file, one line at a time */
/* `std::ifstream` --> ("input file stream") opens a file for reading.
   `std::getline(input_file, place_to_store_text)`  --> pulls one line out of the file at a time and tells you, via its return value, 
                                                        whether it actually found a line or hit the end of the file (EOF) */

/*
int main()
{
    std::ifstream in("example.txt"); // path to file; program and file needs to exist in the same folder for this to work
    std::string line; // initialize an empty string for us to callback later as we're extract lines from the `txt` file

    while (std::getline(in, line)) // reads as "keep looping as long as `getline()` successfully reads another line"
                                   // `getline()` returns something that behaves like TRUE - if there's still a line to read, or FALSE - the moment it hits the end of the file
                                   // You don't need to (1) check `.size()` or (2) count lines yourself - the stream will tell you when it's done.
    {
        std::cout << "Read a line: " << line << "\n";
    }

    // When reached the End-of-File (EOF), display message saying it's the end
    std::cout << "No more lines -- End of File" << "\n";
    return 0;
}
*/

/* Main takeaway from this:
   `std::ifstream any_name("file_name.txt")` --> ("input file stream") opens a file for reading.
   `std::getline(input_file, place_to_store_text (ie. empty string))`  --> pulls one line out of the file at a time and tells you, 
                                                                           via its return value, 
                                                                           whether it actually found a line or hit the end of the file (EOF)
*/


/* Combine everything we've built thus far to form the function `sum_of_words()`*/
/* sum_of_words() will take the filename as input arg 
   - it'll read the the file using the given "file_name" - refer to Building Block 2 
   - it'll add all the decoded numbers together - refer to Building Block 1 
*/

/*
int sum_of_words(const std::string& file_name)
{
    std::ifstream in(file_name); // set input file
    std ::string line; // initialise an empty string for callback later

    int total = 0; // captures the total sum of all the numbers

    while(std::getline(in, line))
    {
        // call line_value() since it returns numerical values, decoder() is already called within line_value() 
        total += line_value(line);

        // print some results
        std::cout << line << "\n";
        std::cout << "After adding = " << line_value(line) << ", total = " << total << "\n";
    }

    return total; // rmbr to return the total summation value
}
*/

// run sum_of_words()
/*
int main()
{
    std::string filename = "example.txt";
    
    return sum_of_words(filename);
}
*/

/* However in "example.txt", it contains uppercase characters that we have not accounted for, 
   thus "Two1four3" gives "13" instead of the expected "23".
   This problem stems from decoder() lacking this feature, let us fix this. */


/* Building block: `std::tolower('string_to_lowercase')`
   - Note: use 'string' instead of "string", else there'll be errors
   - takes one character and returns its lowercase version, if char is already lowercase (or isn't a letter at all), char remains unchanged */
/*
int main()
{
    std::cout << (char)std::tolower('S') << "\n";   // returns 's'
    std::cout << (char)std::tolower('s') << "\n";   // returns 's' (unchanged)
    std::cout << (char)std::tolower('7') << "\n";   // returns '7' (unchanged)
}
*/


/* Building block: parsing strings into `std::tolower('string')` to become lowercase, compare the result to an initialized lowercased word */
/*
int main()
{
    std::string s = "Sixeighttwo1";
    std::string word = "six";

    size_t i = 0; // check starting at index 0, to be used with <s> to determine the starting index

    bool word_matches = true;

    // create <for> loop, we'll use <k> here to determine how much char to be lowercased in <s> 
    // and then determine if <s[index]> matches with <word[index]>
    for (size_t k = 0; k < word.size(); k++)
    {
        if (std::tolower(s[i + k]) != word[k]) // <if> condition - if char_lowercased doesn't matches with the char from word[k]
                                               // we just break contact since there's no point checking further
        {
            word_matches = false;
            break;
        }
    }

    std::cout << "does \"" << s << "\" starting at index " << i << " match \"" << word << "\" (case-insensitive)? ";
    std::cout << (word_matches ? "yes" : "no") << "\n";
    // prints (does "Sixeighttwo1" starting at index 0 match "six" (case-insensitive)? yes)

    return 0;
}
*/


/* Apply this new feature to decoder() */

int decoder(const std::string& s, size_t i) // don't worry about `const` and `&`, 
                                            // just know it means "s is the string that got passed in, and this function
                                            // won't modify your original."
                                            // <size_t i> is the index from the `main()` function, keep this in mind
{
    // First check, if the char at position i is a plain-digit ('7'), rmbr to '7' - '0'
    if(std::isdigit(s[i])) // OPTIONAL: rmbr `static_cast<unsigned char>(line[i])` prevents crash on certain non-English text
    {
        int d = s[i] - '0'; // tl;dr - this is how you turn a DIGIT CHARACTER into DIGIT NUMBER
        return d; 
    }


    // Otherwise,
    // Second check, check every spelled-out word to see if it starts exactly at position i
    std::vector<std::string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    // Mirror your {words} with the respective numerical_values
    std::vector<int> numerical_values = {1,2,3,4,5,6,7,8,9};

    // Create a for loop that loops through `words` and use `.compare()`, if `.compare()` is TRUE, return the numerical_value
    // --> How to use `.compare()`?
    // ----> list.compare(starting_index, how_many_chars_to_compare(len), what_to_compare_against)
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

int line_value(const std::string& line)
{
    int first = -1; // to hold the first digit
    int last = -1; // to hold the last digit

    for (size_t i = 0; i < line.size(); i++)
    {
        // we no longer need the <if> statement here to check "if digit or not" since decode() returns numbers
        // we also no longer need to do the whole <'7' - '0'> thing since decode() is returning int numbers
        int d = decoder(line, i);

        // do the SENTINEL check to determine if decoder() spits out a number or -1, if no, we process further
        if (d != -1)
        {
            // do SENTINEL check to determine if this is the first number to be processed or not, if yes, let `first` take this number
            if (first == -1) first = d;
            last = d;
        }
    }

    if (first == -1) return 0; // if the line has no numbers in it at all (our database all have numbers)
                               // This is just a safeguard against a crash should both `first` and `last` be `-1`, we won't catch the final compuation of `-11`
    
    // combine first(TENS-DIGIT) and last(ONES-DIGIT) together to become the FULL number
    return first * 10 + last;
}

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

// re-run sum_of_words() with updated decoder() func to cater for uppercase characters in example.txt
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