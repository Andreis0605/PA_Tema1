#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

ifstream in("servere.in");
ofstream out("servere.out");

// function that compares the server voltages in order to sort them
bool comparator_servers(pair<int, int> &a, pair<int, int> &b)
{
    if (b.second < a.second)
        return false;
    return true;
}

// function that calculats the power of the cluster for a certain voltage
double min_pow(int N, vector<pair<int, int>> servers, double current)
{
    double minn = DBL_MAX;
    for (int i = 0; i < N; i++)
    {
        if (((double)servers[i].first - abs((double)servers[i].second - current)) < minn)
            minn = ((double)servers[i].first - abs((double)servers[i].second - current));
    }
    return minn;
}

void bsearch_maximum(double min_val, double max_val, int N, vector<pair<int, int>> servers, double &result)
{
    if (min_val <= max_val)
    {
        double mid = floor(((min_val + max_val) / 2.0) * 2.0) / 2.0;
        double left_pow = min_pow(N, servers, mid - 0.1), rigth_pow = min_pow(N, servers, mid + 0.1);
        if (left_pow == rigth_pow)
        {
            // out << "\n acum returnez " << mid << '\n';
            result = min_pow(N, servers, mid);
        }
        if (left_pow > rigth_pow)
            bsearch_maximum(min_val, mid - 0.1, N, servers, result);
        if (left_pow < rigth_pow)
            bsearch_maximum(mid + 0.1, max_val, N, servers, result);
    }
}

void brute_force(double min_volt, double max_volt, vector<pair<int, int>> servers, int N)
{
    for (double i = min_volt; i <= max_volt; i = i + 0.1)
    {
        out << i << "     " << min_pow(N, servers, i) << '\n';
    }
}

int main()
{

    //reading the size of the problem
    int N;
    in >> N;

    //declaring the 
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
        if (aux > max_nec_voltage)
            max_nec_voltage = aux;
        if (aux < min_nec_voltage)
            min_nec_voltage = aux;
    }

    double result = -1;
    bsearch_maximum(min_nec_voltage, max_nec_voltage, N, servers, result);
    out << fixed << setprecision(1) << result;
    return 0;
}
