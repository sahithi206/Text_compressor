# Text Compressor using Huffman Coding

This project implements a text compression algorithm using Huffman coding. Huffman coding is a popular method for lossless data compression, which assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters.

## Features

- Compress text files using Huffman coding
- Decompress the compressed files back to their original form
- Efficient encoding and decoding processes

## Tech Stack

- *Programming Language*: C++
- *Compiler*: g++
- *Version Control*: Git

## Installation

1. Clone the repository:
    bash
    git clone https://github.com/sahithi206/Text_compressor.git
    cd Text_compressor

2. Ensure you have a C++ compiler installed. For example, you can install g++ if it's not already installed:
    bash
    sudo apt-get install g++
    

3. Compile the project:
    bash
    g++ project.cpp -o text_compressor
    
## File Descriptions

1. project.cpp: The main C++ source file containing the implementation of the compressor and decompressor.
2. input.txt: Sample input text file. 
3. output.txt: Sample output file after compression or decompression. 

## Usage

1. *Compress a file*:
    bash
    ./text_compressor input.txt output.txt
    

2. *Decompress a file*:
    bash
    ./text_compressor -d output.txt decompressed.txt
    

## Contribution

1. Fork the repository.
2. Create a new branch (git checkout -b feature-branch).
3. Commit your changes (git commit -am 'Add new feature').
4. Push to the branch (git push origin feature-branch).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.