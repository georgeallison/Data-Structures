// ==========================================
// Assignment 1 CSCI-2270 Data Structures Boese
// @author George Allison, assisted by JuanFran Ferrer
// Due September 5, 2016
//
// Description: Counts unique words in a file
// outputs the top N most common words
// ==========================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

struct wordItem// struct to store word + count combinations
{
	string word;
	int count;
};


/*
* Function name: readBook
* Purpose: read the file and use the following functions to store the words
* @param *fileName - the file to read from
* @param *totalWords - the total non common words
* @param *uniqueWords - the amount of unique non common words  
* @param *arrayDoubles - number of times the array has doubled
* @param *arraySize - the size of the array
* @return wordArray - the array of unique non common words
*/
wordItem *readBook(char *fileName, int *totalWords, int *uniqueWords, int *arrayDoubles, int *arraySize, vector<string> myVec);

/*
* Function name: doubleArray
* Purpose: double the length of the array when it becomes full
* @param array[] - the array that is being doubled
* @param *size - the size of the full array
* @return - new array that is double the size
*/
//void doubleArray(wordItem array[], int *size);

/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into vector
* @param ignoreWordFile - fileName (the file storing ignore words)
* @param _vecIgnoreWords - store ignore words from the file (pass by reference)
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(char *ignoreWordFileName, vector<string> &_vecIgnoreWords);

/*
* Function name: isCommonWord
* Purpose: to see if a word is a common word
* @param word - a word (which you want to check if it is a common word)
* @param _vecIgnoreWords - the vector type of string storing
ignore/common words
* @return - true (if word is a common word), or false (otherwise)
*/
bool isCommonWord(string word, vector<string>& _vecIgnoreWords);

/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to an array of wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);

const int STOPWORD_LIST_SIZE = 50;

// ./a.out 10 HW1-HungerGames_edit.txt HW1-ignoreWords.txt
int main(int argc, char* argv[])
{
	vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);
	// verify we have the correct # of parameters, else throw error msg & return
	if (argc != 4)
	{
		cout << "Usage: ";
		cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>";
		cout << endl;
		return 0;
	}
	
    char *filePath1 = argv[2];
    char *filePath2 = argv[3];
    int topXWords = stoi(argv[1]);
    
    int totalWords = 0;
    int uniqueWords = 0;
    int arrayDoubles = 0;
    int arraySize = 100;
        
    cout << "\n\n\n\n";
	getStopWords(filePath2, vecIgnoreWords);
	
    wordItem *words = readBook(filePath1, &totalWords, &uniqueWords, &arrayDoubles, &arraySize, vecIgnoreWords);
    printTopN(words, topXWords);
    
    cout << "#\nArray Doubled: " << arrayDoubles << endl;
    cout << "#\nUnique non-common words: " << uniqueWords <<  endl;
    cout << "#\nTotal non-common words: " << totalWords << endl; 
    
	return 0;
}

wordItem *readBook(char *fileName, int *totalWords, int *uniqueWords, int *arrayDoubles, int *arraySize, vector<string> myVec)
{
	wordItem *wordArray = new wordItem[*arraySize];
	ifstream myFile;
	myFile.open(fileName);
	string word;
	if(myFile.good())
	{
		cout << "*file opened successfully*\n" << endl;
		while(myFile >> word)
		{
			if(!isCommonWord(word, myVec))
			{
				*totalWords+=1;
				if(*uniqueWords == (*arraySize - 1))
				{
					//doubleArray(*wordArray, arraySize);
					wordItem tempArray[*arraySize * 2];
					for(int k = 0; k < *arraySize; k++)
					{
						tempArray[k] = wordArray[k];
					}
					wordArray = tempArray;
					*arraySize = *arraySize * 2;
					*arrayDoubles+=1;
					break;
				}	
				for(int i = 0; i < *arraySize; i++)
				{
					//cout << i << "word:" << wordArray[i].word << endl;
					if(wordArray[i].word.empty())
					{
						wordItem w;
						w.word = word;
						w.count = 1;
						wordArray[i] = w;
						*uniqueWords += 1;
						break;
					}
					else
					{
						if(wordArray[i].word.compare(word) == 0)
						{
							wordArray[i].count += 1;
							break;
						}
					}
					
				}
			}
		}
	}
	else
	{
		cout << "file not opened" <<  endl;
	}
	myFile.close();
	
	//sort array by count size before returning
	
	bool isChange = true;
	while(isChange)
	{
		isChange = false;
		for(int i = 0; i < *arraySize -1; i++)
		{
			if(wordArray[i].word == "")
			{
				break;
			}
			else
			{			
				if(wordArray[i].count < wordArray[i+1].count)
				{
					wordItem temp = wordArray[i+1];
					wordArray[i+1] = wordArray[i];
					wordArray[i] = temp;
					isChange = true;
				}
			}
		}
	}
	
	return wordArray;
}

/*void doubleArray(wordItem &array[], int *size)
{
	wordItem tempArray[size * 2];

	for(int k = 0; k < size; k++)
	{
		tempArray[k] = *array[k];
	}
	
	*array = tempArray;
	
	size = size * 2;	
}*/

void getStopWords(char *ignoreWordFileName, vector<string> &_vecIgnoreWords)
{
	ifstream inFile;
	inFile.open(ignoreWordFileName);
	string word;
	if(inFile.good())
	{
		int i = 0;
		while(inFile >> word)
		{	
			_vecIgnoreWords[i] = word;
			i++;
		} 
	}
}

bool isCommonWord(string word, vector<string>& _vecIgnoreWords)
{
	for(string x : _vecIgnoreWords)
	{
		if(word == x)
		{
			return true;
		}
	}
		
	return false;
}

void printTopN(wordItem wordItemList[], int topN)
{
	for(int i = 0; i < topN; i++)
	{
		cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
	}
}
