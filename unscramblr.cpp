/*

Quinn Perfetto 2014

Amortized constant time word unscrambling using a unordered_multimap.

I designed a hashing aglorithm which will generate a single hash for all permuatations of a string.
This was achieved by assigning the values a...z each to a corresponding prime number from 2...101.
The hash was then computed by finding the product of these values.
Since multiplication is assosicative and only prime numbers were used in the hashing, all words which consist of the same
letters will get an identical hash.  This allows me to look up any of the permutations and get the rest in constant time. 

Usage: unscramblr [<path to dictionary file>]
Specifying the dictionary file is optional, if no file is specified "dictionary.txt" will be used.

*/

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

long long wordHash(const std::string&);

int main(int argc, char** argv){
	std::string filename;
	if(argc == 1)
		filename = "dictionary.txt";
	else
		filename = argv[1];
	std::ifstream f(filename);
	if(!f.is_open()){
		std::cout << "error opening dictionary file" << std::endl;
		return 0;
	}

	std::unordered_multimap<long long, std::string> words;
	std::string tmp;
	while(f >> tmp)
		words.insert(std::pair<long long, std::string>(wordHash(tmp), tmp));
	f.close();

	while(true){
		std::cout << "Enter a scambled word: ";
		std::string lookup;
		std::cin >> lookup;
		if(lookup == "exit") break;
		auto range = words.equal_range(wordHash(lookup));
		std::cout << "Unscrambled:" << std::endl;
		for_each (
			range.first,
			range.second,
			[](std::unordered_map<long long, std::string>::value_type& x){ std::cout << x.second << std::endl;}
		);
	}
	return 0;
}

long long wordHash(const std::string& s){
	int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
	std::size_t hash = 1;
	for(char c : s)
		hash *= primes[c - 'a'];
	return hash;
}