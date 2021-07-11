#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <vector>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

int estado = 0;

enum Error{
  ERR_OPTION,
  ERR_FILE,
  ERR_WORD,
};

void error(Error n){
  	switch(n){
    case ERR_OPTION:
     	 cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_FILE:
    	 cout << "ERROR: couldn't open file" << endl;
      break;
	case ERR_WORD:
		 cout << "Palabra errónea" << endl;
	  break;			
 	 }
}

void carga(){
	int i = rand() % 3 + 1;
	for(i; i > 0; i--){
		Sleep(500);
		system("CLS");
		cout << "\\ Cargando" << flush;
	    Sleep(500);
	    system("CLS");
		cout << "| Cargando." << flush;
		Sleep(500);
		system("CLS");
		cout << "/ Cargando.." << flush;
		Sleep(500);
		system("CLS");
		cout << "- Cargando..." << flush;
	}	
}

void elegirPalabra(string &palabra){
	vector<string> palabras;
 	int numWords;
	
	ifstream fl("palabras.txt");
	if(fl.is_open()){
		while(!fl.eof()){
			fl >> palabra;
			palabras.push_back(palabra);
		}
	fl.close();
	}
	else {
		error(ERR_FILE);
	}
	numWords = palabras.size();
	palabra = palabras[rand() % numWords];
}

void endGame(int jugador, string palabra){
	system("CLS");
	cout << "#############################\n\n";
	cout << "El ganador es el jugador " << jugador << "\n\n\n";
	cout << "La palabra escondida era " << palabra << "\n\n#############################";
	exit(0);
}

void figura(){
	switch(estado){
	case 0:
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |      \\|/" << endl;
	   cout << " |       | " << endl;
	   cout << " |      / \\ " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 1:
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |      \\|/" << endl;
	   cout << " |       | " << endl;
	   cout << " |      /  " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 2:
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |      \\|/" << endl;
	   cout << " |       | " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 3:
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |      \\|/" << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 4:   
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |      \\| " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 5:	   
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |       | " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 6:  
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |      (_)" << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	case 7:	   
	   cout << " ________  " << endl;
	   cout << " |/      | " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << " |         " << endl;
	   cout << "_|___      " << endl;
	   break;
	}
}

void letrasUsadas(vector<char> &letrasUsadas){
	if(letrasUsadas.size() == 0){
		cout << "--- Letras usadas ---\n";
		cout << "[-]";
	}
	else {
		cout << "--- Letras usadas ---\n[";
		for(int i = 0; i < letrasUsadas.size(); i++){
			cout << letrasUsadas[i];
			if(i < letrasUsadas.size() - 1){
				cout << ", ";
			}
		}
		cout << "]";
	}
}

void comprobarSimilitud(string &inputUsuario, string &palabraAux, string &palabra, int jugador, vector<char> &letrasUsadas){
	int iguales = 0;
	
	if(inputUsuario.size() == palabra.size()){ //Adivinar palabra
		for(int i = palabra.size(); i >= 0; i--){
			if(palabra[i] == inputUsuario[i]){
				iguales++;
			}
		}
		if((iguales - 1) == palabra.size()){
			endGame(jugador, palabra);
		}
		else {
			estado++;
			error(ERR_WORD);
		}
	}
	else if(inputUsuario.size() == 1 && !isdigit(inputUsuario[0]) && inputUsuario[0] != ' '){ //Adivinar letra
		for(int i = palabra.size(); i >= 0; i--){
			if(palabra[i] == inputUsuario[0]){
				palabraAux[i] = inputUsuario[0];
				iguales++;
			}
		}
		if(iguales == 0){
			estado++;
		}
		letrasUsadas.push_back(inputUsuario[0]);
	}
	else {
		error(ERR_WORD);
		if(!isdigit(inputUsuario[0]) && inputUsuario[0] != '\0' && inputUsuario[0] != ' ')	
			estado++;
	}
	
}

void mainGame(){
	estado = 0;
	char customWord;
	int numPlayers;
	int playersAux;
	int numRondas = 1;
	bool finPartida = false;
	string word; //Palabra a adivinar
	string wordCopy; //Palabra oculta a mostrar
	string input; //Entrada usuario
	vector<char> letras;
	
	carga();
	do{
		system("CLS");
		cout << "¿Quieres establecer una palabra custom?[Y/N]: ";
		cin >> customWord;
		cin.get();
		customWord = tolower(customWord);
		if(customWord == 'y'){
			cout << "Introduce la palabra: ";
			getline(cin, word);
			wordCopy = word;
			for(int i = wordCopy.size(); i >= 0; i--){
				wordCopy[i] = '_';
			}
		}
		else if(customWord == 'n'){
			elegirPalabra(word);
			wordCopy = word;
			for(int i = wordCopy.size(); i >= 0; i--){
				wordCopy[i] = '_';
			}
		}
		else{
			error(ERR_OPTION);
			Sleep(1000);
		}
	}while((customWord != 'y') && (customWord != 'n'));
	
	system("CLS");
	cout << "Elige el número de jugadores: ";
	cin >> numPlayers;
	cin.ignore();
	do{
		playersAux = 1;
		system("CLS");
		do{
			cout << "<<Ronda " << numRondas << ">>" << endl;
			figura();
			letrasUsadas(letras);
			cout << "\n\n      " << wordCopy << "      \n\n";
			cout << " - " << "Turno para el jugador " << playersAux << endl << "> ";
			getline(cin, input);
			comprobarSimilitud(input, wordCopy, word, playersAux, letras);
			playersAux++;
			Sleep(600);
			if(estado == 7){
				finPartida = true;
			}
			if(word == wordCopy){
				endGame(playersAux, word);
			}
			system("CLS");
		}while(playersAux <= numPlayers);
		numRondas++;
	}while(finPartida != true);
	cout << "###### HAS PERDIDO ######\n";
	cout << "La palabra era " << word;
	Sleep(5000);
}

void reglas(){
	system("CLS");
	ifstream fl("reglas.txt");
	if(fl.is_open()){
		string x;
		while(!fl.eof()){
			getline(fl, x);
			cout << x << endl;
		}
		fl.close();
		getch();
	}
	else{
		error(ERR_FILE);
		Sleep(1000);
	}
}

void mainMenu(){
	system("CLS");
	cout << "================ AHORCADO ================" << endl;
	cout << "|                                        |" << endl;
	cout << "|     [1] - Empezar juego     |/|        |" << endl;
	cout << "|     [2] - Reglas            | |        |" << endl;
	cout << "|     [q] - Salir             |/|        |" << endl;
	cout << "|                             | |        |" << endl;
	cout << "|                             |/|        |" << endl;
	cout << "|                            (___)       |" << endl;
	cout << "|                            (___)       |" << endl;
	cout << "|                            (___)       |" << endl;
	cout << "|                            (___)       |" << endl;
	cout << "|                            (___)       |" << endl;
	cout << "|                            // \\\\       |" << endl;
	cout << "|                           //   \\\\      |" << endl;
	cout << "|                          ||     ||     |" << endl;
	cout << "|                          ||     ||     |" << endl;
	cout << "|                          ||     ||     |" << endl;
	cout << "|                           \\\\___//      |" << endl;
	cout << "|                            -----       |" << endl;
	cout << "|                                        |" << endl;
	cout << "|                                        |" << endl;
	cout << "| v1.0.0                                 |" << endl;
	cout << "==========================================\n";
}

int main(){
srand(time(NULL));
setlocale(LC_ALL, "");
char option;


do{
	mainMenu();
	cin >> option;
	cin.get();
	switch(option){
		case '1':
			mainGame();
			break;
		case '2':
			reglas();
			break;
		case 'q':
			break;
		default:
			error(ERR_OPTION);
			break;
	}
}while(option != 'q');

system("pause");
return 0;
}
