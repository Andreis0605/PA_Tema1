#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

// structure for storing the words in memory
typedef struct word {
    int frq[10];
    int len;
} word;

int main() {
    // open the files for reading and writing
    FILE *in = fopen("criptat.in", "r");
    FILE *out = fopen("criptat.out", "w");

    // read the size of the data
    int N;
    fscanf(in, "%d", &N);

    // create the coification vector
    int *codif = (int *)calloc(300, sizeof(int));
    int key = 0;

    // define the words array
    word *words = (word *)calloc(N, sizeof(struct word));

    // vector for reading the words
    char aux_string[300];

    // maximum length of a possible password
    int max_len_pos_psswd = 0;

    // read the words from the file
    fgetc(in);
    for (int i = 0; i < N; i++) {
        fscanf(in, "%s", aux_string);
        fgetc(in);

        // processing the string
        int str_size = strlen(aux_string);
        words[i].len = str_size;

        for (int j = 0; j < str_size; j++) {
            // for each letter check if is in the codification array
            if (codif[(int)(aux_string[j] - 'a')] == 0) {
                // if not, add it in the codification array
                key++;
                codif[(int)(aux_string[j] - 'a')] = key;
            }

            // mark the letter in the word's frequency array
            words[i].frq[codif[(int)(aux_string[j] - 'a')]]++;

            // mark the letter in the general frequency array
            max_len_pos_psswd++;
        }
    }

    // calculate all possible lengths of the password
    int *pos_lens = (int *)calloc(max_len_pos_psswd + 1, sizeof(int));

    // base case, length = 0 ia always possible
    pos_lens[0] = 1;

    // for each word, mark all the possible lengths
    for (int i = 0; i < N; i++) {
        for (int j = max_len_pos_psswd; j >= words[i].len; j--) {
            if (pos_lens[j - words[i].len])
                pos_lens[j] = 1;
        }
    }

    // initiate the max length of the best password
    int max_len = -1;

    // for each letter, try to find a password
    for (int k = 1; k <= key; k++) {
        // declaration of the dp vector, which will store
        // the number of apparitions of the current letter
        // for a password that has length = j
        int *dp = (int *)calloc(max_len_pos_psswd + 1, sizeof(int));

        for (int i = 0; i < N; i++) {
            for (int j = max_len_pos_psswd; j >= words[i].len; j--) {
                // if a password of length = j - words[i].len is possible
                // dp[j] will take the maximum value between it's previous value
                // and the value of the previous password + number of aparitions
                // of the letter in the current word
                dp[j] = pos_lens[j - words[i].len]
                            ? max(dp[j], dp[j - words[i].len] + words[i].frq[k])
                            : dp[j];
            }
        }

        // find the longest password for the given letter
        //  that has a dominant letter
        for (int j = max_len_pos_psswd; j >= 0; j--) {
            // check if the current length is possible
            // and it has at least one aparition of the current letter
            if (dp[j] != 0 && pos_lens[j] &&
                (((double)j / (double)dp[j]) < 2.0) && j > max_len) {
                // if the password has a dominant letter,
                // check if it is the longest password ever
                // if yes, save it and go to the next letter
                max_len = j;
                break;
            }
        }
        free(dp);
    }

    // print the result
    fprintf(out, "%d", max_len);

    // eliberarea memoriei
    free(codif);
    free(words);
    free(pos_lens);

    // close the files
    fclose(in);
    fclose(out);

    return 0;
}
