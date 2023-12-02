#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX_WORD 90
#define MAX_CAD 80
#define N_WORDS 9
#define MAX_ATTEMPTS 10

int main()
{
    srand(time(NULL));

    char username[10], line[MAX_WORD], secretWord[MAX_WORD], word_underscore[MAX_WORD], user_letter;
    int n_lines = 0, i = 0, n_underscore = 0;
    bool correct_word;

    int attempts = MAX_ATTEMPTS;

    printf("\n\t====================================================================");

    printf("\n\t                            HANGMAN GAME  ");

    printf("\n\t====================================================================\n");

    printf("Welcome to Hangman game. What is your name?\n");

    scanf("%s", username);

    FILE *file = fopen("paraules.txt", "r");

    if (file == NULL)
    {
        printf("\n ERROR");
    }

    int num_rand = rand() % (N_WORDS);

    while (fgets(line, sizeof(line), file) != NULL){
        n_lines ++;
    }

    fclose(file);

    file = fopen("paraules.txt", "r");

    for (i = 0; i < n_lines; i++){
        if(i == num_rand){
            fscanf(file, "%s", secretWord);
        }
        fgets(line, sizeof(line), file);
    }

    fclose(file);

    for (n_underscore = 0; secretWord[n_underscore] != '\0'; n_underscore++)
    {
        word_underscore[n_underscore] = '_';
    }

    word_underscore[i] = '\0';

    printf("%s\tYou have %d attempts left. %s, try a new letter.\n", word_underscore, attempts, username);
    while ((attempts != 0) && (n_underscore != 0)){
        fflush (stdin);
        scanf("%c", &user_letter);
        i = 0;
        correct_word = false;
        while (secretWord[i] != '\0'){
            if(secretWord[i] == user_letter){
                word_underscore[i] = user_letter;
                correct_word = true;
                n_underscore --;
            }
            i++;
        }
        if (correct_word){
            printf("%s\tWell done! You have %d attempts left. %s, try a new letter.\n\n", word_underscore, attempts, username);
        }
        else{
            printf("%s\tOh, the letter %c is not in the word. You have %d attempts left. %s, try a new letter.\n\n", word_underscore, user_letter, attempts, username);
        }

        attempts--;
    }
    if (attempts == 0)
    {
        printf("Oh, %s! The word is %s.", username, secretWord);
    }
    else
    {
        printf("Congratulation, %s! You have won this game.", username);
    }

    return 0;
}
