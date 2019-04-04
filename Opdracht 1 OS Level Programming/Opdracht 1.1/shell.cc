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
		int pid = fork();
		if(pid == 0){ std::string input;
   		std::cout << "Wat zoek je: ";
   		std::getline(std::cin, input);
   		input= input + "*";
		//std::cout << input << std::endl;
		//execl("/bin/pwd","pwd",(char *) 0);
		execl("/usr/bin/find","find",input.c_str(),(char *) 0);} 
   		else{  wait(NULL); }

}


void python() // ToDo: Implementeer volgens specificatie.
{ int pid;
   pid = fork();
   if(pid==0){
    execl("/usr/bin/python","python",(char *)0); exit(0);}
    else{wait(NULL);}}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
