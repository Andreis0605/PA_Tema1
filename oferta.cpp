#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

// function that calculates the discount for two products
double two_discount(int product1, int product2)
{
    double sum = (double)product1 + (double)product2;
    sum -= ((double)min(product1, product2)) / 2.0;
    return sum;
}

// function that calculates the discount for three products
double three_discount(int product1, int product2, int product3)
{
    double sum = (double)product1 + (double)product2 + (double)product3;
    sum -= (double)min(min(product1, product2), product3);
    return sum;
}

int main()
{
    // open the files for reading and writing
    ifstream in("oferta.in");
    ofstream out("oferta.out");

    // read the number of products and the k
    int N, K;
    in >> N >> K;

    // test the case in which we don't have enough products for k
    if (N < K)
        out << -1;
    else
    {
        // treat the base cases
        if (N == 1)
        {
            // if we have only one product print it's value
            int aux1;
            in >> aux1;
            out << fixed << setprecision(1) << (double)aux1;
        }
        else if (N == 2)
        {
            // if we have two products, apply the discount and print the value
            int aux1, aux2;
            in >> aux1 >> aux2;
            out << fixed << setprecision(1) << two_discount(aux1, aux2);
        }
        else if (N == 3)
        {
            // if we have three products, decide what discount to apply
            // we can group all three products together
            // or group the first two or the second two
            // and add the value of the remainig one
            int aux1, aux2, aux3;
            in >> aux1 >> aux2 >> aux3;
            out << fixed << setprecision(1);
            out << min((aux1 + two_discount(aux2, aux3)),
                       min((two_discount(aux1, aux2) + aux3),
                           three_discount(aux1, aux2, aux3)));
        }
        else
        {
            // start treating the general case

            // read the first values
            int aux1, aux2, aux3, aux4;
            in >> aux1 >> aux2 >> aux3;

            // initialize the dp vector with the base cases
            vector<double> dp(N + 1, 0);
            dp[1] = aux1;
            dp[2] = two_discount(aux1, aux2);
            dp[3] = min((aux1 + two_discount(aux2, aux3)),
                        min((two_discount(aux1, aux2) + aux3),
                            three_discount(aux1, aux2, aux3)));

            for (int i = 4; i <= N; i++)
            {
                // read a new product
                in >> aux4;

                // calculate the best value for the new product
                dp[i] = min(dp[i - 1] + (double)aux4,
                            min(dp[i - 2] + two_discount(aux3, aux4),
                                dp[i - 3] + three_discount(aux2, aux3, aux4)));
                
                //prepare for a new product
                //(move back the current ones)
                aux1 = aux2;
                aux2 = aux3;
                aux3 = aux4;
            }

            //print the best price of the N products
            out << fixed << setprecision(1) << dp[N];
        }
    }

    //close the files
    in.close();
    out.close();

    return 0;
}