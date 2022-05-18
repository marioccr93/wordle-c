#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char arrayOfWords[12669][10];
char *building_word;
char twoDWords[6][5] = {
    {'-','-','-','-','-',},
    {'-','-','-','-','-',},
    {'-','-','-','-','-',},
    {'-','-','-','-','-',},
    {'-','-','-','-','-',},
    {'-','-','-','-','-',}
};
char notExisting[27];
int countExistingChars = 0;

int checkPunctuation(char *word){
    char punctuations[]="áéíóú";
    int i, j;
    int boolean = 0;
        for (i=0;word[i]!='\0';i++){
            for(j=0;j<5; j++){
                if (punctuations[j]==word[i]){
                    boolean = 1;
                }
            }
        }
    return boolean;
}
int getSizeOfarray(){
    int size = 0;
    int i;
    for (i=0; i<=10000; i++){
        if(strlen(arrayOfWords[i]) > 0){
            size++;
        }else{
            break;
        }
    }
    return size;
}
int alreadyExists(char * token){
    int size = getSizeOfarray();
    int i;
    int boolean = 0;
    for (i=0; i<=size; i++){
        if(strcmp(token, arrayOfWords[i]) ==0 ){
            printf("STRING %s ya existe en el array", token);
            boolean = 1;
        }
    }
   
    return boolean;
}
char *getMayus(char *token);
char* getRandomWord(){
    // Open file to read
    FILE *fpointer;
    fpointer = fopen("usual.txt", "r");
    if (fpointer == NULL)
    {
        printf("Cannot open file raw.txt \n");
        exit(0);
    }
    char line[255];
    int counter = 0;
    //Para cada línea de texto copiamos la palabra en array de palabras
    while(fgets(line, 255, fpointer))
    {   
            //Dividimos cada línea separando por espacio para obtener palabras
            char * token = strtok(line, " ");
            //Si existe la palabra
            while( token != NULL ) {

                if(checkPunctuation(token) == 0){
                    if(alreadyExists(token) == 0){
                        char *mayus = getMayus(token);
                        for (int i = 0; i <5; i++){
                        arrayOfWords[counter][i] = mayus[i];
                        }
                        counter+=1;
                    }
                    
                }
                token = strtok(NULL, " ");
            }
            
    }
    //7868 palabras sin tilde
    int n;
    srand(time(NULL));
    n = rand() % counter;
    char * randomWord = arrayOfWords[n];
    return randomWord;
}
int checkIfMayus(char character){
    // Devuelve 1 si la el carácter es una mayúscula y 0 si no lo es
    char mayus[30] = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";    
    int boolean = 0;
    int i;
    for(i=0; i<27; i++){
        if(character == mayus[i]){
            boolean = 1;
        }
    }
    return boolean;

}
int checkIfMinus(char character){
    // Devuelve 1 si la el carácter es una minúscula y 0 si no lo es
    char minus[30] = "abcdefghijklmnñopqrstuvwxyz";    
    int boolean = 0;
    int i;
    for(i=0; i<27; i++){
        if(character == minus[i]){
            boolean = 1;
        }
    }
    return boolean;

}

//Devuelve la palabra en mayúscula
char *getMayus(char *token){
        char mayusWord[5];
        int i;
        for(i=0; i<5; i++){
            mayusWord[i] = toupper(token[i]);
        }
        char *pointer = malloc(30);
        int j;
        for(j=0; j<5; j++){
        pointer[j] = mayusWord[j];
        }
        return pointer;
}

//Comprueba si la palabra introducida es la que buscamos
int checkWord(char *word, char *try){
    int matches = 0;
    if(strcmp(try, word) == 0){
        matches = 1;
    }
    return matches;
}

//Devuelve el número de veces que un carácter se encuentra en una palabra
int getCountOfCharacterInWord(char * word, char character){

    int count = 0;
    int i;
    for(i=0; i<5; i++){
        if(word[i] == character){
            count++;
        }
    }
    return count;
}
int alreadyExistsNotInWord(char ch){
    int i;
    int alreadyInArray = 0;
    for(i=0; i<27; i++){
        if(notExisting[i] == ch){
            alreadyInArray = 1;
        }
    }
    return alreadyInArray;
}

int storeInArray(char ch){

    notExisting[countExistingChars] = ch;
    countExistingChars++;
    
    return 0;
}

int isCharacter(char ch){

    int i;
    int founded = 0;

    char  arrayCharacters[56] = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz";
    for (i=0; i<56; i++){
        if(ch == arrayCharacters[i]){
            founded = 1;
        }
    }
    return founded;
}

int showNotExisting(){
    printf("\nLetras que no existen en la palabra => ");
    int i;
    for(i=0; i<27; i++){
        if(isCharacter(notExisting[i]) == 1){
            printf(" %c ", toupper(notExisting[i]));
        }
    }
    printf("\n\n");
    return 0;
}

int storeNotCoincident(char * word, char* try){
    int i;
    int founded = 0;
    for(i=0; i<5; i++){
        if(getCountOfCharacterInWord(word, try[i]) == 0){
            if(alreadyExistsNotInWord(try[i]) == 0){
                storeInArray(try[i]);
            }
        }
    }
    return 0;
}
//Comprueba letras que hemos puesto pero no en la posición adecuada
char * checkCharactersInWord(char * word, char * try, int tries){
    int i;
    int j;
    char building[5];
    char wordle[5];
    wordle[0] =twoDWords[tries][0];
    wordle[1] =twoDWords[tries][1];
    wordle[2] =twoDWords[tries][2];
    wordle[3] =twoDWords[tries][3];
    wordle[4] =twoDWords[tries][4];

    // printf("PALABRA INTENTADA => %s\n", try);
    // printf("PALABRA CORRECTA => %s\n", word);
    // printf("TRIES => %d\n", tries);
    for(i=0; i<5; i++){
        building[i] = '-';
    }
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (word[i] == try[j]){
                // printf("COINCIDEN => %c y %c en POSICIÓN de try => %d\n", word[i], try[j], j);
                char minus;
                minus = tolower(try[j]);
                //Si la palabra en formación sigue teniendo vacía la letra que se ha encontrado,
                //La escribimos en la posición del try pero como minúscula
                //Si la letra no está ya en su posición del resultado y aparece una vez en la palabra final y una vez en el try, se pone normal
                if(wordle[i] == '-' && getCountOfCharacterInWord(word, try[j]) == 1 && getCountOfCharacterInWord(try, try[j]) == 1){
                    if(getCountOfCharacterInWord(building, try[j]) < 1){
                        building[j] = minus;
                    }
                }else if(getCountOfCharacterInWord(word, try[j]) == 2 && wordle[i] == '-' && getCountOfCharacterInWord(try, try[j]) == 2 ){
                    if(getCountOfCharacterInWord(building, try[j]) < 2){
                        building[j] = minus;
                    }
                }else if(getCountOfCharacterInWord(word, try[j]) == 3 && wordle[i] == '-' && getCountOfCharacterInWord(try, try[j]) == 3 ){
                    if(getCountOfCharacterInWord(building, try[j]) < 3){
                        building[j] = minus;
                    }
                }
            }
        }
    }
    char *pointer = malloc(30);
    for(j=0; j<5; j++){
    pointer[j] = building[j];
    }
    return pointer;
}
//Comprueba caracteres en posición correcta
char *checkCharacters(char * word, char * try){

    int i;
    char building[5];
    //Si en algún momento una letra de la palabra try se encuentra en la word, 
    for(i=0; i<5; i++){
        building[i] = '-';
        if(try[i]==word[i]){
            building[i] = word[i];
        }
    }
    char *pointer = malloc(30);
    int j;
    for(j=0; j<5; j++){
    pointer[j] = building[j];
    }
    return pointer;
}
//Asigna caracteres al array 2D final - Lógica de jerarquía
int assignCharacters(char * building, int tries){
    //Si la letra final no es mayúscula ya (correcta) ->
    //Si nos llega una mayúscula se asigna directamente por prioridad sobre lo que hubiese (minúscula o '-')
    //Si nos llega una minúscula y antes había '-' se asigna por prioridad la minúscula
    // printf("BUILDING QUE LLEGA ES => %s\n", building);
    if(checkIfMayus(twoDWords[tries][0]) == 0){
        if(checkIfMayus(building[0]) == 1){
            twoDWords[tries][0] = building[0];
        }else if(twoDWords[tries][0] == '-' && checkIfMinus(building[0])  == 1){
            twoDWords[tries][0] = building[0];
        }
    }
    if(checkIfMayus(twoDWords[tries][1]) == 0){
        if(checkIfMayus(building[1]) == 1){
            twoDWords[tries][1] = building[1];
        }else if(twoDWords[tries][1] == '-' && checkIfMinus(building[1]) == 1){
            twoDWords[tries][1] = building[1];
        }
    }
    if(checkIfMayus(twoDWords[tries][2]) == 0){
        if(checkIfMayus(building[2]) == 1){
            twoDWords[tries][2] = building[2];
        }else if(twoDWords[tries][2] == '-' && checkIfMinus(building[2]) == 1){
            twoDWords[tries][2] = building[2];
        }
    }
    if(checkIfMayus(twoDWords[tries][3]) == 0){
        if(checkIfMayus(building[3]) == 1){
            twoDWords[tries][3] = building[3];
        }else if(twoDWords[tries][3] == '-' && checkIfMinus(building[3]) == 1){
            twoDWords[tries][3] = building[3];
        }
    }
    if(checkIfMayus(twoDWords[tries][4]) == 0){
        if(checkIfMayus(building[4]) == 1){
            twoDWords[tries][4] = building[4];
        }else if(twoDWords[tries][4] == '-' && checkIfMinus(building[4]) == 1){
            twoDWords[tries][4] = building[4];
        }
    }
    
    return 0;
}
char *try;
char *buildingWord;
char *building_word;
char *building_word_2;

int play(char * word, int tries){
    char tryWord[5];
    printf("Prueba con palabra de 5 letras: ");
    scanf("%s", tryWord);
    while(strlen(tryWord) != 5){
        printf("La palabra NO tiene 5 letras, esto puede dar un error, por favor introduzca una de cinco letras: ");
        scanf("%s", tryWord);
    }
    int i = 1;
    try = getMayus(tryWord);
    //Número del intento, se corresponde con la fila en el array
    if(checkWord(word, try) == 0){
        storeNotCoincident(word, try);
        building_word = checkCharacters(word, try);
        assignCharacters(building_word, tries);
        building_word_2 = checkCharactersInWord(word, try, tries);
        // printf("Building word 2 minus=> %s\n", building_word_2);
        assignCharacters(building_word_2, tries);
        showNotExisting();
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[0][0], twoDWords[0][1], twoDWords[0][2], twoDWords[0][3], twoDWords[0][4]);
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[1][0], twoDWords[1][1], twoDWords[1][2], twoDWords[1][3], twoDWords[1][4]);
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[2][0], twoDWords[2][1], twoDWords[2][2], twoDWords[2][3], twoDWords[2][4]);
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[3][0], twoDWords[3][1], twoDWords[3][2], twoDWords[3][3], twoDWords[3][4]);
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[4][0], twoDWords[4][1], twoDWords[4][2], twoDWords[4][3], twoDWords[4][4]);
        printf("|%c|%c|%c|%c|%c|\n", twoDWords[5][0], twoDWords[5][1], twoDWords[5][2], twoDWords[5][3], twoDWords[5][4]);

    }
    else
    {
        printf("¡ENHORABUENA!\n");
        printf("\nHas acertado, la palabra es efectivamente %s\n", word);
        exit(0);
    }

    return 0;

}

int checkResult(int tries){
    //Devuelve 1 si la palabra está completa y 0 si no lo está
    char arrayFinal[5];
    arrayFinal[0] = twoDWords[tries][0];
    arrayFinal[1] = twoDWords[tries][1];
    arrayFinal[2] = twoDWords[tries][2];
    arrayFinal[3] = twoDWords[tries][3];
    arrayFinal[4] = twoDWords[tries][4];
    int i;
    int result = 1;
    for (i=0; i<5; i++){
        if(checkIfMayus(arrayFinal[i]) == 0){
            result = 0;
        }
    }
    return result;

}
int welcome(){
    printf("***Bienvenido al juego wordle hecho en C***\n");
    printf("REGLAS=>\n");
    printf("+Si aciertas la localización exacta de una letra esta se mostrará en MAYÚSCULA\n");
    printf("+Si existe una letra introducida pero no en el lugar indicado, se mostrará en minúscula\n");
    printf("+Dispones de 6 intentos para acertar la palabra, buena suerte!\n\n");

    return 0;
}
int main(){
    welcome();
    char *word;
    word = getRandomWord();
    // printf("WORD => %s\n",word);
    int tries = 0;
    play(word, tries);
    while(checkResult(tries) == 0 && tries <= 4){
        tries++;
        play(word, tries);
        int triesLeft = 5 -tries;
        printf("Te quedan %d intentos\n", triesLeft);
        
    }
    printf("Se ha acabado el número de intentos. La palabra buscada era=> %s\n", word);
    return 0;
}