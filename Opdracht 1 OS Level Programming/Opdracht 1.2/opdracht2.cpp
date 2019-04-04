// Opdracht voltooid 

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main(int argc, char* argv[]){
	int increment = atoi(argv[1]);
	int fd = open("infile.txt", O_RDONLY);
	int fd1 = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd < 0){
		perror(" r1");
		exit(1);
	}
	char *c = (char *) calloc(100, sizeof(char));
	int infile = read(fd, c, 100);
	string sentence = string(c);
	int i = 0;
	const char* characters = sentence.c_str();
	string newSentence;
	while(true){
		newSentence.push_back(characters[i]);
		if(i + increment > 9){
			i = i  - 9;
		} else {
			i += increment;
		}
		if(i == 0){
			break;
		}
	}
	int size = write(fd1, newSentence.c_str(), strlen(newSentence.c_str()));
	cout << characters << " naar " << newSentence << endl;
	close(fd);
	close(fd1);
}
