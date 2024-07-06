#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
#include <map>

using namespace std;
/*
 Intution-
 The frequencies of the elements in the input are noted.
 The New Node with {Character, Frequencies} are Created and Pushed into th Priority Queue 
 Then the Huffman Tree is created such that the elements with the least are chosen
 The a parent node is created with  equal to sum of the two elements and pushed into the queue
 At the End after popping all the elements the last element present in the queue is root of the Tree

Generating Code:
 The codes are assigned in such a way that if we are traversing through 
 left side:"0" is added to the code
 right side:"1" is added to the code
 If we reach the leaf node then the code is assigned to that particular Character

Encoding:
 We use the stored Codes in the map to encode each character.
 Then we store the Encoded string in the Output File

Decoding:
  We insert all the elements of the Output File into a string
  Using that String,we traverse through the Tree and then Decode the entire Code into text.
*/
// Node structure for Huffman tree
struct Node {
    char data;
    long long int freq;
    Node* left;
    Node * right;

    // Constructor
    Node(char _data, long long int _freq) {
        left =NULL;
        right = NULL;
        data = _data;
        freq = _freq;
    }
};

// Comparison functor for priority queue
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

// Function to generate Huffman codes recursively
void Codes(Node* root, string str, unordered_map<char, string>& cnt) {
    if (!root)
        return;

    // If leaf node is reached (character node), store its Huffman code
    if (root->data != '\0') {
        cnt[root->data] = str;
        // cout << root->data << " " << cnt[root->data] << endl;
    }

    // Traverse left and right sub-trees
    //if we are traversing through left root then we should add the value 0 
    Codes(root->left, str + "0", cnt);

    //if traversing through the right root add value 1;
    Codes(root->right, str + "1", cnt);
}

// Function to build Huffman tree and return root
Node* HuffmanCodes(unordered_map<char, int>& freq) {

    // Priority queue to store nodes
    //The elements with least frequency are always at the top of priority queue
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create a node for each character and its frequency, push to priority queue
    for (auto i : freq) {
        pq.push(new Node(i.first, i.second));
    }
    
    // Build Huffman tree by merging nodes until only one node remains
    //Only leaf nodes contain characters other than thhose nodes all the other nodes contain '\0'
    while (pq.size() != 1) {

        //Select the charcters with least Frequencies in the queue
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Create a new internal node with '&' as data and sum of frequencies
        Node* top = new Node('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    // Return the root of the Huffman tree
    return pq.top();
}

// Function to encode text using Huffman codes
string encode(string& t, unordered_map<char,string>& cnt) {

    string ans;
    // Encode each character in the input text using its Huffman code
    for (auto ch : t) {
        string s = cnt[ch];
        ans += s;
    }
    //The below string contains is the encoded version of input
    return ans;
}

// Function to decode Huffman-encoded text
string decode(string& encoded, Node* root) {
    
    string decoded ;
    Node*newnode = root;

    // Traverse the Huffman tree to decode each bit of the encoded text
    for (char bit : encoded) {
        if (bit == '0')
            newnode = newnode->left;
        else
            newnode = newnode->right;

        // If a leaf node is reached, append the character to decoded text and reset to root
        if (newnode->left == NULL && newnode->right == NULL) {
            decoded += newnode->data;
            newnode=root;
        }
    }
    return decoded;
}

// Function to free dynamically allocated memory for the Huffman tree
void freeMemory(Node* root) {
    if (root) {
        freeMemory(root->left);
        freeMemory(root->right);
        delete root;
    }
}

int main() {

    // Read input text from file
    ifstream inFile("input.txt");

    //If the file is not Open
    if (!inFile) {
        return -1;
    }

    string t;
    getline(inFile, t);
    inFile.close();

    // Calculate frequency of each character in the input text
    unordered_map<char, int> freq;
    for (char ch : t) {
        freq[ch]++;
    }

    // Map to store Huffman codes for each character
    unordered_map<char, string> cnt;
    
    // Build Huffman tree and generate Huffman codes
    Node* root = HuffmanCodes(freq);
    Codes(root, "", cnt);

    // Encode input text using Huffman codes
    string encoded = encode(t,cnt);

    // Write encoded text to output file
    ofstream outFile("output.txt");

    //Write the encoded text in the output.txt    
    outFile << encoded;

    outFile.close();
    cout << "Encoded text saved to output.txt" << endl;

    // Decode the encoded text from output file using Huffman tree
    //If there is a Output File, the File will be opened else Output.txt file is created.
    //But here I haven't Created the Output
    //After Execution of the code the Output File is Created int the Folder
    ifstream encodedFile("output.txt");
    if (!encodedFile) {
        return -1;
    }

    string encodedText;
    getline(encodedFile, encodedText);
    
    //The text in the Output.txt is Copied to the encodedText string
    encodedFile.close();

    // Decode the encoded text using Huffman tree and print decoded text
    string decoded = decode(encodedText, root);
    //print the Decoded text 
    cout << "Decoded text: " << decoded << endl;

    // Clean up allocated memory
    freeMemory(root);


    return 0;
}