
#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include "ConsoleApplication3.h"
using namespace std;

// declare global variables
int iGlobal = 0;
int flag = 0;
char arrChar[256];

struct MinHeapNode
{
	char data;
	unsigned freq;
	MinHeapNode *left, *right;
	MinHeapNode(char data, unsigned freq) 
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};


struct compare
{// For comparison of two heap nodes
	bool operator()(MinHeapNode *l, MinHeapNode *r) 
	{
		return (l->freq > r->freq);
	}
};

void printCodes(struct MinHeapNode *root, string str) 
{// Print huffman codes from the root of huffman tree
	if (!root) 
	{
		return;
	}
	if (root->data != '$') 
	{
		cout << root->data << ":" << str << "\n";
	}
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void printDecodes(struct MinHeapNode *root, char c[256]) 
{// Print decodes from huffman codes.
	if (!root)
	{
		return;
	}
	if (root->data != '$')
	{
		cout << root->data << endl;
		return;
	}
	else 
	{
		if (c[iGlobal] == '0') 
		{// go left
			++iGlobal;
			printDecodes(root->left, arrChar);
		}
		else if(c[iGlobal] == '1')
		{// go right
			++iGlobal;
			printDecodes(root->right, arrChar);
		}
		else {
			//do nothing.
			flag = 1;
			return;
		}
	}

}



void HuffmanCodes(char data[], int freq[], int size) 
{
	/*
	Main function for huffman encoding and decoding
	1.Build a Huffman tree and print codes by traversing
	the built Hulfman tree.
	2.Decode the code based on huffman tree.
	*/
// ENCODING
	struct MinHeapNode *left, *right, *top;

	// Create a min heap
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>minHeap;
	// Insert all characters of data[]
	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	//Iterate while size of heap doesn't become 1
	while (minHeap.size() !=1)
	{
		// Extract the two minimum freq items from min heap
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	cout <<"============ HUFFMAN CODES ============" << "\n";
	printCodes(minHeap.top(), "");
	cout << "======================================" << "\n\n\n";
// DECODES
	ifstream decodeFile;
	decodeFile.open("a4-2.txt");
	int index = 0;
	while (decodeFile.get(arrChar[index])) 
	{
		index = index + 1;
	}
	arrChar[index] = '\0';

	//printDecodes(minHeap.top(),arrChar);
	cout << "============ DECODING ============" << endl;
	while (flag == 0) {
		printDecodes(minHeap.top(), arrChar);
	}
	cout << "==================================" << endl;
}


int main() 
{
	cout <<"============ WELCOME TO ASSIGNMENT 4 ============ " << endl;
	cout << "============ AUTHOR: MAOXU LIU ============ " << endl;
	cout << "============ Program starts ============" << endl;
	string storeLine;
	ifstream myFile;
	int size = 9;
	char arr;
	int freq;
	myFile.open("a4-1.txt");
	if (myFile.good()) {
		// read first line
		getline(myFile, storeLine);
		stringstream convert(storeLine);//object from the class stringstream
		convert >> size;
		size = 9;
		char arr[9];
		int freq[9];
		int i = 0;
		//vector<int> freq;
		cout <<"============ Input values ============" << endl;
		while (!myFile.eof())
		{
			getline(myFile, storeLine);
			arr[i] = storeLine.at(0);
			stringstream convert(storeLine.substr(2));
			convert >> freq[i];
			cout << arr[i] << " " << freq[i] << endl;
			i++;
		}
		cout << "======================================" << endl;
		cout << "\n\n";
		
		HuffmanCodes(arr, freq, size);// Huffman encoding and decoding.
		cout << "============ PROGRAM ENDS ============" << endl;
		

	}
	else 
		cout << " Can not read file " << endl;

	return 0;
}
