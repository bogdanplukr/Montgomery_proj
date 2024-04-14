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
vector<unsigned long long int> random_vec(unsigned long long int length)
{
    vector<unsigned long long int> rez;
    while (rez.size() <= length)
    {
        long long int rnd = rand() % 50;
        if (isPrime(rnd) && find(rez.begin(), rez.end(), rnd) == rez.end()) rez.push_back(rnd);
    }

    return rez;
}
vector<unsigned long long int> random_vec_var(unsigned long long int var, vector<unsigned long long int> vec_of_random_moduls)
{
    vector<unsigned long long int> rez = vec_of_random_moduls;
    long long int  j = 0;
    for (auto i : rez)
        rez[j++] = var % i;
    return rez;
}
vector<unsigned long long int> vec_rez(vector<unsigned long long int> vec_of_random_moduls, vector<unsigned long long int> vec_of_x_moduls, vector<unsigned long long int> vec_of_y_moduls)
{
    vector<unsigned long long int> rez(vec_of_random_moduls.size());
    for (int i = 0; i < vec_of_random_moduls.size(); i++)
        rez[i] = (vec_of_x_moduls[i] * vec_of_y_moduls[i]) % vec_of_random_moduls[i];
    return rez;
}
unsigned long long int funk_eqw(unsigned long long int M, unsigned long long int mi)
{
    for (int i = 1; i <= mi; i++)
        if ((M / mi) * i % mi == 1)
            return i;
    return 1;
}
unsigned long long int chinies_metod(vector<unsigned long long int> rez, vector<unsigned long long int> vec_of_random_moduls)
{
    unsigned long long int M = 1;
    for (auto i : vec_of_random_moduls)
        M *= i;
    unsigned long long int rezultat = 0;
    for (int i = 0; i < vec_of_random_moduls.size(); i++)
    {
        rezultat += (M / vec_of_random_moduls[i]) * rez[i] * funk_eqw(M, vec_of_random_moduls[i]);
    }

    return rezultat % M;
}
unsigned long long int rezultat_classic(const vector<unsigned long long int> vec_of_random_moduls, unsigned long long int x, unsigned long long int y) {
    vector<unsigned long long int> rez;
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
        unsigned long long int length = 11;
        vector< unsigned long long int> vec_of_random_moduls = random_vec(length);
        //for (auto i : vec_of_random_moduls)
        //    cout << i<<"\n";
        //cout << "\n\n\n\n\n";
        unsigned long long int x = 73000000;
        unsigned long long int y = 100000;

        vector< unsigned long long int> vec_of_x_moduls = random_vec_var(x, vec_of_random_moduls);
        vector< unsigned long long int> vec_of_y_moduls = random_vec_var(y, vec_of_random_moduls);
        auto start0 = std::chrono::system_clock::now();
        unsigned long long int rezult_pryk = rezultat_classic(vec_of_random_moduls, x, y);
        auto end0 = std::chrono::system_clock::now();

        //std::cout << "finished computation in classic " << std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count() << " nanoseconds\n";
        outputFile << "finished computation in classic " << std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count() << " nanoseconds\n";

        auto start = std::chrono::system_clock::now();
        unsigned long long int final_rez = chinies_metod(vec_rez(vec_of_random_moduls, vec_of_x_moduls, vec_of_y_moduls), vec_of_random_moduls);
        auto end = std::chrono::system_clock::now();
        cout << final_rez<<"\n";
        //std::cout << "finished computation in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds\n";
        outputFile << "finished computation in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds\n";
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - start0).count()) rate++;
    }
    cout << rate / (repit / 100);
    outputFile << "Rate " << rate / (repit / 100);
    outputFile.close();
}

