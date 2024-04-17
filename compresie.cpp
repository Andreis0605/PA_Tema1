#include <bits/stdc++.h>

using namespace std;

int main()
{
    // open the files for reading and writing
    ifstream in("compresie.in");
    ofstream out("compresie.out");

    //declare and read the two vectors
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

    // declare the indexes and sums for the traversal of the vectors
    int i = 0, j = 0;
    unsigned long long sum_x = x[0], sum_y = y[0];

    //initilaize the counter for the number of elements after the compression
    int count = 0;

    //iterate through the vectors
    while (i < N && j < M)
    {

        if (sum_x == sum_y)
        {
            //if the two sums are equal, we found an area that we can compress
            //or we have two identical elements in both vectors
            count++;
            i++;
            j++;
            sum_x = x[i];
            sum_y = y[j];
        }
        else
        {
            // add the next element of the coresponding vector to the lower sum
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

    //check if we finished both vectors
    //if not, the compression is not possible
    if (i != N || j != M)
        count = -1;

    //print the result
    out << count;

    //close the files
    in.close();
    out.close();

    return 0;
}
