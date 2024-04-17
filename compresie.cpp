#include <bits/stdc++.h>

using namespace std;

ifstream in("compresie.in");
ofstream out("compresie.out");

int main()
{
    int N, M;
    vector<int> x, y;

    int aux_int;
    in >> N;
    for (int i = 0; i < N; i++)
    {
        in >> aux_int;
        x.push_back(aux_int);
    }

    in >> M;
    for (int i = 0; i < M; i++)
    {
        in >> aux_int;
        y.push_back(aux_int);
    }

    /*for (int i = 0; i < N; i++)
    {
        out << x[i] << " " << y[i] << '\n';
    }*/

    // cu ei ma plimb pe vectori
    int i = 0, j = 0;
    unsigned long long sum_x = x[0], sum_y = y[0];
    int count = 0;

    while (i < N && j < M)
    {
        if (sum_x == sum_y)
        {
            count++;
            i++;
            j++;
            sum_x = x[i];
            sum_y = y[j];
        }
        else
        {
            if (sum_x > sum_y)
            {
                j++;
                sum_y += y[j];
            }
            else
            {
                i++;
                sum_x += x[i];
            }
        }
    }

    if (i != N || j != M)
        count = -1;

    out << count;
    return 0;
}