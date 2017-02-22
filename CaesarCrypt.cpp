#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include "CaesarCrypt.h"

using namespace std;

void encrypt()
{
	char text[100];									// declare char array for text
	for(int i = 0; i < 100; ++i) text[i] = 0;		// fill it with nothing
	char encrypted[100];							// declare char array for encrypted text
	for(int i = 0; i < 100; ++i) encrypted[i] = 0;	// fill it with nothing

	cout << "Enter text: ";
	cin.ignore();
	cin.get(text, 100);	// read text to encrypt
	int n = strlen(text);	// get length of word to encrypt

	int *key = new int[n*2];	// declare key array
	srand(time(NULL));
	for(int i = 0; i < (n*2); ++i) {	// fill key array with random numbers so when added their max value is 94
		if(i % 2 == 0) { key[i] = (rand() % 10); }
		else {
			if(key[i-1] == 9) { key[i] = rand() % 5; }
			else { key[i] = rand() % 10; }
		}
	}
	
	/*********************************************************************************************************/
	int tempKey;
	int x = 0;
	for(int i = 0; i < (n*2); i+=2)	// start encrypting process
	{
		tempKey = key[i] * 10 + key[i+1];	// combine a pair of numbers of the key array
		if(text[x] - tempKey < 32)	{ encrypted[x] = (127) - (32 - (text[x] - tempKey)); }	// if it exceeds the 32 when encrypting, continue at 126
		else { encrypted[x] = text[x] - tempKey; }	// encrypt letter
		++x;
	}
	cout << "\nDone encrypting!" << endl;
	/*********************************************************************************************************/

	ofstream file;
	file.open("encrypted.txt");	// create "encrypted.txt" text file
	file << encrypted << endl;	// print encrypted text to file
	file << "Key: ";
	for(int a = 0; a < (n*2); ++a) file << key[a];	// print key to file
	file.close();
	delete[] key;
	cout << "Opening file...\n" << endl;
	system("start encrypted.txt");	// open file
}

void decrypt()
{
	char text[100];									// declare char array for text
	for (int i = 0; i < 100; ++i) text[i] = 0;		// fill it with nothing
	char decrypted[100];							// declare char array for encrypted text
	for (int i = 0; i < 100; ++i) decrypted[i] = 0;	// fill it with nothing

	cout << "Enter text: ";
	cin.ignore();
	cin.get(text, 100);		// read text to decrypt
	int n = strlen(text);	// get length of text

	int *key = new int[n * 2];

	/*********************************************************************************************************/
	cout << "Key: ";
	char *fullKey = new char[n * 2 + 1];
	cin.ignore();
	cin.getline(fullKey, n * 2 + 1);	// read encryption key

	for (int i = 0; i < strlen(fullKey); ++i) key[i] = fullKey[i] - 48; // save the key digit by digit in the array
	
	ofstream file;
	file.open("decrypted.txt");	// create "decrypted.txt" text file
	decryptText(n, key, text, decrypted);
	file << decrypted;		// print decrypted text to file
	file.close();
	/*********************************************************************************************************/
	
	cout << endl << "Done decrypting!" << endl;
	cout << "Opening file...\n" << endl;
	system("decrypted.txt");	// open file
	system("del decrypted.txt");	// delete file after closing it
	
}


void decryptText(int n, int *key, char *text, char *decrypted)
{
	int tempKey;
	int x = 0;
	for(int i = 0; i < (n * 2); i+=2)	// iterate through all chars
	{
		tempKey = key[i] * 10 + key[i + 1];	// combine a pair of numbers of the key array
		if(text[x] + tempKey > 126)	{ decrypted[x] = 32 + ((text[x] + tempKey) - 127); }	// if it exceeds the 126 when decrypting, continue at 32
		else { decrypted[x] = text[x] + tempKey; }	// decrypt letter
		++x;
	}
}

int main()
{
	system("title CaesarCrypt");

	cout << " *****************" << endl;
	cout << "$   CaesarCrypt   $" << endl;
	cout << "$ by Hendrik Tete $" << endl;
	cout << " *****************" << endl;

	cout << "\nDo you want to encrypt (1) or decrypt (2)? -> ";	// read operation
	int operation;													// 1 = encryption
	cin >> operation;												// 2 = decryption

	if(operation == 1) { encrypt(); }		// if user entered 1, start the encrypt function
	else if(operation == 2) { decrypt(); }	// else if he entered 2, start the decrypt function
	else { cout << "\nERROR: Wrong input!" << endl; }	// else print error

	system("pause");
	return(0);
}
