#include <stdio.h>
#include <stdbool.h>
#define LENGTH 5
#define MAX 6
void loadWord(char word[]);
void toLowerCase(char str[]);
bool isLetter(char c);
bool isValid(char guess[]);
bool isCorrect(char guess[],char word[]);
bool inWord(char letter, char word[]);
void printResult(char guess[], char word[]);
void printAll(char guesses[][LENGTH+1], int guessCount, char word[]);
int main(){
	char word[LENGTH+1];
	char guesses[MAX][LENGTH+1];
	char guess[100];
	int guessCount=0;
	bool won = false;
	loadWord(word);
	toLowerCase(word);
	while ((guessCount<MAX)&& !won){
		printf("GUESS %d! Enter your guess: ", guessCount+1);
		scanf("%99s", guess);
		toLowerCase(guess);
		while (!isValid(guess)){
			printf("Your guess must be 5 letters long.\nPlease try again: ");
			scanf("%99s", guess);
			toLowerCase(guess);
		}
		for (int i=0; i<LENGTH+1; i++){
			guesses[guessCount][i]=guess[i];
		}
		guesses[guessCount][LENGTH]='\0';
		guessCount++;
		printf("================================\n");
		printAll(guesses, guessCount, word);
		if (isCorrect(guess, word)){
			won=true;
		}
	}
	if (won){
		printf("================================\n");
		printf("\n                ");
		for (int i=0; i<LENGTH;i++){
			printf("%c", word[i]-32);
		}
		if(guessCount==1){
			printf("\n        You won in %d guess!\n", guessCount);
		}else{
			printf("\n      You won in %d guesses!\n", guessCount);
		}
		if ((guessCount==1)){
			printf("                GOATED!\n");
			} else if ((guessCount=2)||(guessCount=3)){
			printf("                Amazing!\n");
			} else if ((guessCount=4)||(guessCount=5)){
			printf("                Nice!\n");
			} else{}
		} else {
			printf("You lost, better luck next time!");
		}
}
void loadWord(char word[]){
	FILE *answer =fopen("word.txt", "r");
	if (answer==NULL){
		printf("Could not open file");
		return;
	}
	fscanf(answer, "%5s", word);
	fclose(answer);
}
void toLowerCase(char str[]){
	for (int i=0; str[i] != '\0'; i++){
		if ((str[i]>='A')&&(str[i]<='Z')){
			str[i]=str[i]+32;
		}
	}
}
bool isLetter(char c){
	return ((c>='a')&&(c<='z'));
}
bool isValid(char guess[]){
	int length=0;
	while (guess[length]!='\0'){
		if (!isLetter(guess[length])){
			return false;
		}
	length++;
	}
	return length == LENGTH;
}
bool isCorrect(char guess[], char word[]){
	for (int i=0; i<LENGTH; i++){
		if(guess[i]!=word[i]){
			return false;
		}
	}
	return true;
}
bool inWord(char letter, char word[]){
	for (int i=0; i<LENGTH; i++){
		if(word[i]==letter){
		return true;
		}
	}
	return false;
}
void printResult(char guess[], char word[]){
	char display[LENGTH+1];
	char arrows[LENGTH+1];
	for(int i=0; i<LENGTH; i++){
		if(guess[i]==word[i]){
			display[i]=guess[i]-32;
		} else {
			display[i]=guess[i];
		}
		arrows[i]= ' ';
	}
	display[LENGTH]='\0';
	arrows[LENGTH]='\0';
	for (int i=0; i<LENGTH;i++){
		if(guess[i]!= word[i] && (inWord(guess[i], word))){
			bool alreadyCorrect = false;
			for (int j=0; j<LENGTH; j++){
				if ((guess[i]==word[j]) && (guess[j]==word[i])){
					alreadyCorrect = true;
				}
			}
			if (!alreadyCorrect){
				arrows[i]='^';
			}
		}
	}
	printf("%s\n%s\n", display, arrows);
}	
void printAll(char guesses[][LENGTH+1], int guessCount, char word[]){
	for (int i=0; i<guessCount;i++){
		printResult(guesses[i], word);
	}
}
