#include <bits/stdc++.h>

// define the limit for the values
#define LIMIT 1000000007

using namespace std;

// function that calculates the power of a number in logarithmic time
unsigned long long logarithmic_power(unsigned long long base, int exponent) {
    // base case
    if (exponent == 0)
        return 1;

    // limit the value of the base
    base = base % LIMIT;

    // get the new base
    unsigned long long aux_base = (base * base) % LIMIT;

    // make the call for the new base and exponent
    if (exponent % 2 == 0)
        return logarithmic_power(aux_base, exponent / 2) % LIMIT;
    return (base * logarithmic_power(aux_base, (exponent - 1) / 2)) % LIMIT;
}

int main() {
    // open the files for reading and writing
    ifstream in("colorare.in");
    ofstream out("colorare.out");

    // read the number of areas
    int N;
    in >> N;
    in.get();

    unsigned long long combinations = 1;
    int aux_int;
    char aux_char;

    // use flags in order to remember the previous area
    bool first_ever = true, is_V, prev_seq_is_V;

    // reading and processing the rectangles
    for (int i = 0; i < N; i++) {
        // read an area
        in >> aux_int;
        in.get();
        in >> aux_char;
        in.get();

        // mark the type of area
        if (aux_char == 'V')
            is_V = true;
        else
            is_V = false;

        // limit the number of combinations
        combinations = combinations % LIMIT;

        // treat the first area separately
        if (first_ever) {
            if (is_V) {
                // the first area starts with a vertical rectangle
                combinations = (combinations *
                                ((3 *
                                  (logarithmic_power(2, aux_int - 1))) %
                                 LIMIT) %
                                LIMIT);
            } else {
                // the first area starts with a horizontal rectangle
                combinations = (combinations *
                                ((6 *
                                  (logarithmic_power(3, aux_int - 1))) %
                                 LIMIT) %
                                LIMIT);
            }

            // mark that we processed the first area and save it's type
            first_ever = false;
            prev_seq_is_V = is_V;
        } else {
            // processing the other areas(other than the first one)
            if (prev_seq_is_V) {
                // the area before was made of vertical rectangles
                if (is_V) {
                    // this area is made with vertical rectangles
                    combinations = (combinations *
                                    ((logarithmic_power(2, aux_int))
                                     % LIMIT) % LIMIT);
                } else {
                    // this area is made out of horizontal rectangles
                    combinations = (combinations *
                                    ((2 *
                                      (logarithmic_power(3, aux_int - 1))) %
                                     LIMIT) %
                                    LIMIT);
                }
            } else {
                // /the area before was made of horizontal rectangles
                if (is_V) {
                    // this area is made with vertical rectangles
                    combinations = (combinations *
                                    ((logarithmic_power(2, aux_int - 1))
                                     % LIMIT)) % LIMIT;
                } else {
                    // this area is made out of horizontal rectangles
                    combinations = (combinations *
                                    ((logarithmic_power(3, aux_int)) % LIMIT)) %
                                   LIMIT;
                }
            }
        }

        // limit the value of the number of color combinations
        combinations = combinations % LIMIT;

        // save the area type
        prev_seq_is_V = is_V;
    }

    // print the result
    out << combinations;

    // close the files
    in.close();
    out.close();

    return 0;
}
