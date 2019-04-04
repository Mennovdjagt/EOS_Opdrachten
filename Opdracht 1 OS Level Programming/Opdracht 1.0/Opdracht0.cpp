#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

//vertaalt de string naar een niet leesbaar iets
string translate(string input, string variabele){
    int schuiving = variabele[0] - '0'; //geeft aan hoeveel de chars verschoven moeten worden
    string result;  //geeft het eindresultaat
    char tmp;       //slaat tijdelijk de nieuwe char op

    for (unsigned int i = 0; i < input.size(); ++i) {
        tmp = input[i] + schuiving;
        result += tmp;
    }

    return result;
}

int main(int argc, char *argv[]){
    string s;

    if(argc != 3){
        cerr << "Deze functie heeft 2 argument nodig";
        return -1;
    }

    cout << translate(argv[1], argv[2]) << endl;

    return 0;
}
