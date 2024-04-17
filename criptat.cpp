#include <bits/stdc++.h>

using namespace std;

typedef struct word
{
    int frq[10];
    int len;
} word;

// function that returns the sum of all the fields in an array
int total_len_freq_array(int *array)
{
    int sum = 0;
    for (int i = 1; i <= 8; i++)
    {
        sum += array[i];
    }
    return sum;
}

// function that checks that a password has a dominant letter
bool has_dominant_letter(int *freq_array, int len, int poz)
{
    return (((double)freq_array[poz]) > (((double)len) / 2.0));
}

int main()
{
    // open the files for reading and writing
    ifstream in("criptat.in");
    ofstream out("criptat.out");

    // read the size of the data
    int N;
    in >> N;

    // create the coification vector
    int *codif = (int *)calloc(300, sizeof(int));
    int key = 0;

    // define the words array
    word *words = (word *)calloc(N, sizeof(struct word));

    // vector for reading the words
    char aux_string[300];

    // vector for total frequency of letters
    int *tot_freq = (int *)calloc(8, sizeof(int));

    // read the words from the file
    in.get();
    for (int i = 0; i < N; i++)
    {
        in >> aux_string;
        in.get();

        // processing the string
        int str_size = strlen(aux_string);
        words[i].len = str_size;
        for (int j = 0; j < str_size; j++)
        {
            if (codif[(int)(aux_string[j] - 'a')] == 0)
            {
                key++;
                codif[(int)(aux_string[j] - 'a')] = key;
            }
            words[i].frq[codif[(int)(aux_string[j] - 'a')]]++;
            tot_freq[codif[(int)(aux_string[j] - 'a')]]++;
        }
    }

    // maxium length of a password
    int max_len_psswd = total_len_freq_array(tot_freq);

    // calculate all possible lengths of the password
    vector<bool> pos_lens(max_len_psswd + 1, false);
    pos_lens[0] = true;

    for (int i = 0; i < N; i++)
    {
        for (int j = max_len_psswd; j >= words[i].len; j--)
        {
            if (pos_lens[j - words[i].len])
                pos_lens[j] = true;
        }
    }

    // initiate the max length of the best password
    int max_len = -1;

    // for each letter, try to find a password
    for (int k = 1; k <= key; k++)
    {
        vector<int> dp(max_len_psswd + 1, 0);

        for (int i = 0; i < N; i++)
        {
            for (int j = max_len_psswd; j >= words[i].len; j--)
            {
                dp[j] = pos_lens[j - words[i].len]
                            ? max(dp[j], dp[j - words[i].len] + words[i].frq[k])
                            : dp[j];
            }
        }

        for (int j = max_len_psswd; j >= 0; j--)
        {
            if (dp[j] != 0 && pos_lens[j])
            {
                max_len = ((((double)j / (double)dp[j]) < 2))
                              ? max(max_len, j)
                              : max_len;
            }
        }
    }

    out << max_len;

    return 0;
}