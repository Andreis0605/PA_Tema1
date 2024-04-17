#include <bits/stdc++.h>

using namespace std;

ifstream in("criptat.in");
ofstream out("criptat.out");

typedef struct word
{
    int freq[10];
    int len;
} word;

/*typedef struct psswd
{
    int freq[10];
    int len;
    bool composition[1001];
    int last_added;
} psswd;*/

// function that copies a frequency array in another
void copy_freq_array(int *dest, int *src)
{
    for (int i = 1; i <= 8; i++)
    {
        dest[i] = src[i];
    }
}

// function that substracts a frequency array from another
void subtract_freq_array(int *minuend, int *subtrahend)
{
    for (int i = 1; i <= 8; i++)
    {
        minuend[i] -= subtrahend[i];
    }
}

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
            words[i].freq[codif[(int)(aux_string[j] - 'a')]]++;
            tot_freq[codif[(int)(aux_string[j] - 'a')]]++;
        }
    }

    /*for(int i=1;i<=8;i++)
    {
        out<< i << " " << tot_freq[i]<<'\n';
    }*/

    // initialize all the variables for the search
    /*int max_len = -1;
    int *aux_freq = (int *)calloc(10, sizeof(int));
    int len_total_words = total_len_freq_array(tot_freq);

    // sort the words by the freqency of each letter
    for (int k = 1; k <= key; k++)
    {
        // out << "--------------------------------\n"
        //    << "Sunt pe cheia: " << k << "\n";
        sort(words, words + N, [k](word a, word b) { // if(a.freq[k] == b.freq[k]) return a.len > b.len;
            // else return(a.freq[k] < b.freq[k]);
            if (((double)((double)a.len / (double)a.freq[k]) == (double)(((double)b.len / (double)b.freq[k]))))
                return a.len > b.len;
            else
                return ((double)((double)a.len / (double)a.freq[k]) > (double)(((double)b.len / (double)b.freq[k])));
        });

        /*for (int i = 0; i < N; i++)
        {
            out << "Cuvantul " << i << '\n';
            for (int j = 1; j <= 8; j++)
            {
                out << j << ' ' << words[i].freq[j] << '\n';
            }
            out << "Lungime " << words[i].len << "\n\n";
        }

        // prepare for iterating through the wor
        int letter_len = len_total_words;

        copy_freq_array(aux_freq, tot_freq);

        for (int i = 0; i < N; i++)
        {
            if (has_dominant_letter(aux_freq, letter_len, k))
            {
                if (letter_len > max_len)
                {
                    // out << "Am gasit ceva mai bun scazand cuvantul: " << i << "\n";
                    max_len = letter_len;
                    // out << "Lungimea maxima este " << max_len << '\n';
                }
            }
            subtract_freq_array(aux_freq, words[i].freq);
            letter_len -= words[i].len;
        }
    }*/

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

    /*for (int i = 0; i <= max_len; i++)
    {
        out << pos_lens[i] << " ";
    }*/

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
                dp[j] = pos_lens[j - words[i].len] ? max(dp[j], dp[j - words[i].len] + words[i].freq[k]) : dp[j];
            }
        }

        /*out << '\n';
        for (int i = 0; i <= max_len_psswd; i++)
        {
            out << pos_lens[i] << " ";
        }

        out << '\n';
        for (int i = 0; i <= max_len_psswd; i++)
        {
            out << dp[i] << " ";
        }
        out << "\n\n";*/

        for (int j = max_len_psswd; j >= 0; j--)
        {
            if (dp[j] != 0 && pos_lens[j]){//out<<"Intru in if";
                max_len = ((((double)j / (double)dp[j]) < 2)) ? max(max_len, j) : max_len;}
            //out << "La litera " << k << " am gasit maxim " << max_len << '\n';
        }
    }

    out << max_len;

    return 0;
}