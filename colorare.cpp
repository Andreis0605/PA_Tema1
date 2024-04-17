#include <bits/stdc++.h>

#define LIMIT 1000000007

using namespace std;

ifstream in("colorare.in");
ofstream out("colorare.out");

unsigned long long logarithmic_power(unsigned long long base, int exponent)
{
    //out << "base is: " << base<< '\n';
    if (exponent == 0)
        return 1;
    base = base % LIMIT;
    unsigned long long aux_base = (base * base) % LIMIT;
    if (exponent % 2 == 0)
        return logarithmic_power(aux_base, exponent / 2) % LIMIT;
    return (base * logarithmic_power(aux_base, (exponent - 1) / 2)) % LIMIT;
}

int main()
{

    int N;
    unsigned long long combinations = 1;
    int aux_int;
    char aux_char;

    // use flags in order to decide how much to multiply with
    bool first_ever = true, is_V, prev_seq_is_V;

    // read the number of areas
    in >> N;
    in.get();

    // reading and processing the rectangles
    for (int i = 0; i < N; i++)
    {
        // read an area
        in >> aux_int;
        // out << aux_int << " ";
        in.get();
        in >> aux_char;
        // out << aux_char << '\n';
        in.get();

        if (aux_char == 'V')
            is_V = true;
        else
            is_V = false;

        combinations = combinations % LIMIT;

        if (first_ever)
        {
            if (is_V)
            {
                combinations = (combinations * ((3 * (logarithmic_power(2, aux_int - 1))) % LIMIT) % LIMIT);
            }
            else
                combinations = (combinations * ((6 * (logarithmic_power(3, aux_int - 1))) % LIMIT) % LIMIT);
            first_ever = false;
            prev_seq_is_V = is_V;
        }
        else
        {
            if (prev_seq_is_V)
            {
                if (is_V)
                {
                    combinations = (combinations * ((logarithmic_power(2, aux_int)) % LIMIT) % LIMIT);
                }
                else
                    combinations = (combinations * ((2 * (logarithmic_power(3, aux_int - 1))) % LIMIT) % LIMIT);
            }
            else
            {
                if (is_V)
                {
                    combinations = (combinations * ((logarithmic_power(2, aux_int - 1)) % LIMIT)) % LIMIT;
                }
                else
                    combinations = (combinations * ((logarithmic_power(3, aux_int)) % LIMIT)) % LIMIT;
            }
        }
        combinations = combinations % LIMIT;
        prev_seq_is_V = is_V;
    }

    out << combinations;
    return 0;
}
