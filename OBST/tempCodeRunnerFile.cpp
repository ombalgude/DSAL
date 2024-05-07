#include <iostream>
#include <iomanip>
#define max 20
#define inf 999

using namespace std;

int i, j, k, n, min, r[max][max];
float p[max], q[max], w[max][max], c[max][max];

void OBST();
void print_tab();

int main()
{
    cout << "Enter no. of nodes: ";
    cin >> n;
    cout << "Enter successful search probability: ";
    for (i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    cout << "Enter unsuccessful search probability: ";
    for (i = 0; i <= n; i++)
    {
        cin >> q[i];
    }
    OBST();

    print_tab();

    return 0;
}
void OBST()
{
    int x;
    for (i = 0; i <= n; i++) //Calculate values for the first row
    {
        r[i][i] = 0;
        c[i][i] = 0;
        w[i][i] = q[i];
    }
    for (i = 0; i < n; i++) //calculate values for the second row
    {
        j = i + 1;
        w[i][j] = w[i][i] + p[j] + q[j];
        c[i][j] = w[i][j];
        r[i][j] = j;
    }

    //calculate values for third row onwards
    for (j = 2; j <= n; j++)
    {
        for (i = 0; i <= n - j; i++)
        {
            x = i + j;
            w[i][x] = w[i][x - 1] + p[x] + q[x];
            c[i][x] = inf;
            for (k = i + 1; k <= x; k++)
            {
                if (c[i][x] > c[i][k - 1] + c[k][x])
                {
                    c[i][x] = c[i][k - 1] + c[k][x];
                    r[i][x] = k;
                }
            }
            c[i][x] = c[i][x] + w[i][x];
        }
    }
}
void print_tab()
{
    cout << endl
         << "----OBST TABLE----" << endl;
    k = 0;
    while (k <= n) //print rows from 0 to n
    {
        for (i = 0, j = i + k; i < n && j <= n; i++, j++) //print weight
            cout << "w" << i << j << "=" << setw(4) << w[i][j] << "\t";
        cout << endl;
        for (i = 0, j = i + k; i < n && j <= n; i++, j++) //print cost
            cout << "c" << i << j << "=" << setw(4) << c[i][j] << "\t";
        cout << endl;
        for (i = 0, j = i + k; i < n && j <= n; i++, j++) //print root
            cout << "r" << i << j << "=" << setw(4) << r[i][j] << "\t";
        cout << endl
             << endl;
        k++;
    }
}
