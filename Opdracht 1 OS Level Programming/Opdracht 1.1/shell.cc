#include "shell.hh"

int main()
{ std::string input;

  int fd, sz;
  char *c = (char *) calloc(100, sizeof(char));
  fd = open("config.txt", O_RDONLY);
  sz = read(fd, c, 10);
  c[sz] = '\0';
  std::string prompt = c;

  while(true)
  { std::cout << prompt;                   // Print het prompt
    std::getline(std::cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "python") python();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (std::cin.eof()) return 0; } }      // EOF is een exit

void new_file() // ToDo: Implementeer volgens specificatie.
{ std::string input;
  std::cout << "Geef een naam: ";
  std::getline(std::cin, input);
  input += ".txt";
  int fd = open(input.c_str(), O_WRONLY| O_CREAT); 
  std::string tekst;
  std::cout << "Inhoud: ";
  std::getline(std::cin, tekst); 
  int sz = write(fd, tekst.c_str(), 100);

  close(fd);
 }

void list() // ToDo: Implementeer volgens specificatie.
{  int pid = fork();
   if(pid == 0){ execl("/bin/ls", "ls", "-la", (char *) 0); exit(0);} 
   else{  wait(NULL); }
 }

void find() // ToDo: Implementeer volgens specificatie.
{
    cout << "Te zoeken: ";
    string search;
    getline(cin, search);
    const char* searchString = search.c_str();
    int fd[2];
    int pid = fork();
    if(pid == 0){
        int fd[2];
        pipe(fd);
        int cid = fork();
        if(cid > 0){
            close(fd[0]);
            close(STDOUT_FILENO);
            dup(fd[1]);
            close(fd[1]);
            char *args[] = {(char*) "/usr/bin/find", (char*) ".", (char*) 0};
            execv("/usr/bin/find",args);
        } else {
            close(fd[1]);
            close(STDIN_FILENO);
            dup(fd[0]);
            close(fd[0]);
            char *args[] = {(char*) "/bin/grep", (char*) searchString, (char*) 0};
            execv("/bin/grep",args);
        }
    } else {
        int exit_status;
        wait(&exit_status);
    }
    sleep(1);
    cout << prompt;

}


void python() // ToDo: Implementeer volgens specificatie.
{ int pid;
   pid = fork();
   if(pid==0){
    execl("/usr/bin/python","python",(char *)0); exit(0);}
    else{wait(NULL);}}
