# Huffman-coding
A C++ compression and decompression program based on Huffman Coding.
## Introduction
This project is to design compression and decompression programs based on Huffman Coding an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes".
## Implementation
The programs can compress text files and decompress compress file consisting of 128 ASCII characters.
### Compression
1. Open input file, count and store the frequencies of different characters.
2. Construct Priority Queue and then Huffman Tree with frequencies we got.
3. Calculate Huffman Encode Table from Huffman Tree.
4. Encode the file, store Huffman Encode Table and encoded to the file.
### Decompression
1. Open file, get frequencies of different characters from start of files.
2. Construct Priority Queue and then Huffman Tree with frequencies we got.
3. Decode the file based on the tree and store it to the file.
