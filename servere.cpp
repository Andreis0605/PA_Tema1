#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

// function that calculats the power of the cluster for a certain voltage
double min_pow(int N, vector<pair<int, int>> servers, double current)
{
    double minn = DBL_MAX;

    // iterate through the server list
    for (int i = 0; i < N; i++)
    {
        // find the serverver with the minimum power
        if (((double)servers[i].first -
             abs((double)servers[i].second - current)) < minn)
            minn = ((double)servers[i].first -
                    abs((double)servers[i].second - current));
    }

    return minn;
}

// function that uses binary search in order to find the best voltage
// try to find the global maximum of the function
// that represents the power of the server cluster
void bsearch_maximum(double min_val, double max_val, int N,
                     vector<pair<int, int>> servers, double &result)
{

    if (min_val <= max_val)
    {
        // get the middle of the interval
        // and the values of the powers next to the middle
        double mid = floor(((min_val + max_val) / 10.0) * 10.0) / 2.0;
        double left_pow = min_pow(N, servers, mid - 0.1);
        double rigth_pow = min_pow(N, servers, mid + 0.1);

        // if the powers next to the middle are equal, we found the maximum
        if (left_pow == rigth_pow)
        {
            result = min_pow(N, servers, mid);
        }

        // if not, look at the slope and go to the left or rigth
        if (left_pow > rigth_pow)
            bsearch_maximum(min_val, mid - 0.1, N, servers, result);
        if (left_pow < rigth_pow)
            bsearch_maximum(mid + 0.1, max_val, N, servers, result);
    }
}

int main()
{

    // open the files for reading and writing
    ifstream in("servere.in");
    ofstream out("servere.out");

    // reading the size of the problem
    int N;
    in >> N;

    // read the data for the servers
    int min_nec_voltage = INT_MAX, max_nec_voltage = INT_MIN;
    int aux;
    vector<pair<int, int>> servers(N);
    for (int i = 0; i < N; i++)
    {
        in >> aux;
        servers[i].first = aux;
    }
    for (int i = 0; i < N; i++)
    {
        in >> aux;
        servers[i].second = aux;

        // get the maximum and minimum voltage for the server cluster
        if (aux > max_nec_voltage)
            max_nec_voltage = aux;
        if (aux < min_nec_voltage)
            min_nec_voltage = aux;
    }

    // start the binary search
    // use the maximum and minimum determined earlier
    // as the interval for the search
    double result = -1;
    bsearch_maximum(min_nec_voltage, max_nec_voltage, N, servers, result);

    // print the result
    out << fixed << setprecision(1) << result;

    // close the files
    in.close();
    out.close();

    return 0;
}
