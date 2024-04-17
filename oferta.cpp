#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

ifstream in("oferta.in");
ofstream out("oferta.out");

// function that calculates the discount of two products
double two_discount(int product1, int product2)
{
    double sum = (double)product1 + (double)product2;
    sum -= ((double)min(product1, product2)) / 2.0;
    return sum;
}

// function that calculates the discount of three products
double three_discount(int product1, int product2, int product3)
{
    double sum = (double)product1 + (double)product2 + (double)product3;
    sum -= (double)min(min(product1, product2), product3);
    return sum;
}

int main()
{
    // reading the size of the problem
    int N, K;
    in >> N >> K;

    // test the case in which we don't have enough numbers for k
    if (N < K)
        out << -1;
    else
    {

        if (N == 1)
        {
            int aux1;
            in >> aux1;
            // out<<aux1;
            out << fixed << setprecision(1) << (double)aux1;
        }
        else if (N == 2)
        {
            int aux1, aux2;
            in >> aux1 >> aux2;
            out << fixed << setprecision(1) << two_discount(aux1, aux2);
        }
        else if (N == 3)
        {
            int aux1, aux2, aux3;
            in >> aux1 >> aux2 >> aux3;
            out << fixed << setprecision(1) << min((aux1 + two_discount(aux2, aux3)), min((two_discount(aux1, aux2) + aux3), three_discount(aux1, aux2, aux3)));
        }
        else
        {
            int aux1, aux2, aux3, aux4;
            in >> aux1 >> aux2 >> aux3;

            // initialize the dp vector and test the base cases
            vector<double> dp(N + 1, 0);

            dp[1] = aux1;
            dp[2] = two_discount(aux1, aux2);
            dp[3] = min((aux1 + two_discount(aux2, aux3)), min((two_discount(aux1, aux2) + aux3), three_discount(aux1, aux2, aux3)));

            for (int i = 4; i <= N; i++)
            {
                in >> aux4;
                dp[i] = min(dp[i - 1] + (double)aux4, min(dp[i - 2] + two_discount(aux3, aux4), dp[i - 3] + three_discount(aux2, aux3, aux4)));
                aux1 = aux2;
                aux2 = aux3;
                aux3 = aux4;
            }
            out << fixed << setprecision(1) << dp[N];
        }
    }

    return 0;
}