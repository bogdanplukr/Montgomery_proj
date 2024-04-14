#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;

bool isPrime(long long int n) {
    if (n == 1 || n == 0)
        return false;
    for (long long int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
vector< long long int> random_vec(long long int length)
{
    vector< long long int> rez;
    while (rez.size() <= length)
    {
        long long int rnd = rand()%100;
        if (isPrime(rnd)&& find(rez.begin(), rez.end(), rnd) == rez.end()) rez.push_back(rnd);
    }
        
    return rez;
}
vector< long long int> random_vec_var(long long int var, vector< long long int> vec_of_random_moduls)
{
    vector< long long int> rez = vec_of_random_moduls;
    long long int  j = 0;
    for (auto i : rez)
        rez[j++] = var % i;
    return rez;
}
vector< long long int> vec_rez(vector< long long int> vec_of_random_moduls, vector< long long int> vec_of_x_moduls, vector< long long int> vec_of_y_moduls)
{
    vector< long long int> rez(vec_of_random_moduls.size());
    for (int i = 0; i < vec_of_random_moduls.size(); i++)
        rez[i] = (vec_of_x_moduls[i] * vec_of_y_moduls[i]) % vec_of_random_moduls[i];
    return rez;
}
long long int funk_eqw(long long int M, long long int mi)
{
    for (int i = 1; i <= mi; i++)
        if ((M / mi)*i % mi == 1)
            return i;
    return 1;
}
long long int chinies_metod(vector< long long int> rez, vector< long long int> vec_of_random_moduls)
{
    long long int M = 1;
    for (auto i : vec_of_random_moduls)
        M *= i;
    long long int rezultat = 0;
    for (int i = 0; i < vec_of_random_moduls.size(); i++)
    {
        rezultat += (M / vec_of_random_moduls[i]) * rez[i] * funk_eqw(M, vec_of_random_moduls[i]);
    }

    return rezultat%M;
}
long long int rezultat_classic(const vector<long long int> vec_of_random_moduls, long long int x, long long int y) {
    vector<long long int> rez;
    for (auto mod : vec_of_random_moduls)
        rez.push_back((x * y) % mod);
    long long int result = chinies_metod(rez, vec_of_random_moduls);

    return result;
}

int main()
{
    ofstream outputFile("result.txt");
    int rate = 0;
    int repit = 1000000;
    for (int lp = 0; lp < repit; lp++) {
        long long int length = 10;
        vector< long long int> vec_of_random_moduls = random_vec(length);
        //for (auto i : vec_of_random_moduls)
        //    cout << i<<"\n";
        //cout << "\n\n\n\n\n";
        long long int x = 123456789;
        long long int y = 456465876;

        vector< long long int> vec_of_x_moduls = random_vec_var(x, vec_of_random_moduls);
        vector< long long int> vec_of_y_moduls = random_vec_var(y, vec_of_random_moduls);
        auto start0 = std::chrono::system_clock::now();
        long long int rezult_pryk = rezultat_classic(vec_of_random_moduls, x, y);
        auto end0 = std::chrono::system_clock::now();

        //std::cout << "finished computation in classic " << std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count() << " nanoseconds\n";
        outputFile<< "finished computation in classic " << std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count() << " nanoseconds\n";

        auto start = std::chrono::system_clock::now();
        long long int final_rez = chinies_metod(vec_rez(vec_of_random_moduls, vec_of_x_moduls, vec_of_y_moduls), vec_of_random_moduls);
        auto end = std::chrono::system_clock::now();

        //std::cout << "finished computation in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds\n";
        outputFile << "finished computation in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds\n";
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count()) rate++;
    }
    cout << rate / (repit / 100);
    outputFile <<  "Rate "<< rate / (repit / 100);
    outputFile.close();
}

