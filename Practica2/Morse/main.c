#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW 36
#define MAX_COLUMN 8
#define MAX_LETTER 15
#define MAX_PHRASE_MORSE 300

void traduction_letter_morse(char dict[MAX_ROW][MAX_COLUMN]){

    char word_code[MAX_LETTER];

    int n_letter, i, j;

    n_letter = 0;

    scanf("%s", word_code);

    for(i = 0; word_code[i] != '\0'; i++)
    {
        n_letter++;
    }

    if(n_letter > MAX_LETTER)
    {
        printf("ERROR");
    }

    else
    {
        for(i = 0; i < MAX_LETTER; i++)
        {
            if(word_code[i] >= 'a' && word_code[i] <= 'z')
            {
                word_code[i] -= 32;
            }
            else
            {
                word_code[i] = word_code[i];
            }
        }
        n_letter = 0;

        for(i = 0; i < MAX_ROW; i++)
        {
            j = 1;

            if(dict[i][0] == word_code[n_letter])
            {
                while (dict[i][j] != '*')
                {
                    j++;

                    if ((dict[i][j] == '.') || (dict[i][j] == '-'))
                    {
                        printf("%c",dict[i][j]);
                    }
                }
                printf(" ");

                n_letter ++;

                i = -1;
            }
        }
    }
}

void traduction_words_file(char dict[MAX_ROW][MAX_COLUMN]){

    FILE *code;

    FILE *original;

    char letter;

    int i, j, k;

    code = fopen ("codificat.txt", "w");

    if( (original = fopen("original.txt","r")) == NULL)
    {
        printf( "ERROR\n");
    }
    else
    {
        fscanf (original, "%c", &letter);

        while (!feof(original))
        {
            if (letter == '\n')
            {
                fprintf(code, "\n");
            }
            else if (letter == ' ')
            {
                for (i = 0; i < 2; i++)
                {
                    fprintf(code, " ");
                }
            }
            else
            {
                for (i = 0; i < MAX_ROW; i++)
                {
                    j = 1;

                    if (letter == dict[i][0])
                    {
                        while (dict[i][j] != '*')
                        {
                            if ((dict[i][j] == '.') || (dict[i][j] =='-'))
                            {
                                fprintf(code, "%c", dict[i][j]);
                            }

                            j++;
                        }
                        for (k = 0; k < 3; k++)
                        {
                            fprintf(code, " ");
                        }
                    }
                }
            }
            fscanf (original, "%c", &letter);
        }
        fprintf(code, "\n");

        fclose(original);

        fclose(code);
    }
}

void traduction_files_morse(char dict[MAX_ROW][MAX_COLUMN]){

    FILE *code;

    FILE *decode;

    int i, j, k, l, space;

    char phrase_morse[MAX_PHRASE_MORSE], letter;

    decode = fopen ("descodificat.txt", "w");

    code = fopen("codificat.txt","r");

    i = 0;

    j = 0;

    l = 0;

    if((code) == NULL)
    {
        printf("ERROR");
    }
    else
    {

        while (!feof(code))
        {
            fscanf(code, "%c", &letter);

            i = 0;

            while ((letter != '\n') && (letter != '\0'))
            {
                phrase_morse[i] = letter;

                i++;

                fscanf(code, "%c", &letter);
            }
            phrase_morse[i] = '\0';

            i = 0;

            l = 0;

            while (phrase_morse[i] != '\0')
            {
                if (phrase_morse[i] != ' ')
                {
                    l = i;

                    space = 0;

                    k = 2;

                    j = 0;

                    while ((phrase_morse[i] != ' ') && (phrase_morse[i] != '\n'))
                    {

                        while ((dict[j][k] != '*') || (phrase_morse[i] != ' '))
                        {

                            if (dict[j][k] == phrase_morse[i])
                            {
                                i++;

                                k++;

                            }
                            else
                            {
                                i = l;

                                j++;

                                k = 2;

                            }
                        }

                    }

                    if (i - l == k - 2)
                    {
                        fprintf(decode, "%c", dict[j][0]);

                        l = i;

                    }
                    else
                    {
                        i = l;
                    }

                }
                else
                {
                    i++;

                    space++;
                }

                if (space == 5)
                {
                    space = 0;

                    fprintf(decode, " ");
                }

            }

            fprintf(decode, "\n");
        }
    }

    fclose(code);

    fclose(decode);
}

int main(){
    printf("\n\t==========================================");

    printf("\n\t                MORSE");

    printf("\n\t==========================================\n\n\n");

    int i = 0, j = 0, option, n_lines = 0;

    char line[100], dict[20][20], morse_letter;

    FILE *fmorse = fopen("morse.txt", "r");

    if(fmorse == NULL){
        printf("ERROR");
    }

    while (fgets(line, sizeof(line), fmorse) != NULL){
        n_lines ++;
    }

    fclose(fmorse);

    fmorse = fopen("morse.txt", "r");

    while ((morse_letter = fgetc(fmorse)) != EOF){
        if (j == 0 && i == 0){
          rewind(fmorse);
        }
        for(i = 0; i < 71; i++){
            for(j = 0; j < 1; j++){
                fscanf(fmorse, "%c", &morse_letter);
                printf("Dict[%d][%d]: %c ", i, j, morse_letter);
                printf("\n");
            }
        }
        dict[i][0] = morse_letter;
        printf("Dict[%d][%d]: %c ", i, j, morse_letter);
        j = 1;
        while (morse_letter != '\n'){
            fscanf(fmorse, "%c", &morse_letter);
            if((morse_letter == '-') || (morse_letter == '*') || (morse_letter == '.')){
                dict[i][j] = morse_letter;
            }
            j++;
        }
        i++;
    }
    while(1){
        printf("\n\nChoose an option\n\n");
        printf("1. Code word\n\n");
        printf("2. Code file\n\n");
        printf("3. Decode file\n\n");
        printf("0. Exit\n\n");
        scanf("%d", &option);
        switch (option){
            case 1:
                    system("cls");
                    printf("Write a word to code\n");
                    traduction_letter_morse(dict[MAX_ROW][MAX_COLUMN]);
                    break;
            case 2:
                    system("cls");
                    traduction_words_file(dict);
                    break;
            case 3:
                    system("cls");
                    traduction_files_morse(dict);
                    break;
             case 0:
                    printf("\nEnd of program\n");
                    exit(0);
                    break;
             default:
                    system("cls");
                    printf("\nPlease, introduce a correct name\n\n");
                    break;
        }
    }
    fclose(fmorse);
    return 0;
}
