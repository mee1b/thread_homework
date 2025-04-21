#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

static void sum_vec(std::vector<int> v1, std::vector<int> v2, std::vector<int> resoult, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        resoult.push_back(v1[i] + v2[i]);
    }
}

static void valueInVector(std::vector<int>& v1, std::vector<int>& v2, int size)
{
    for (int i = 0; i < size; ++i)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
    }
}


int main()
{
    std::cout << "Number of hardware cores - " << std::thread::hardware_concurrency() << std::endl;

    std::cout << "\t\t1'000" << "\t10'000" << "\t100'000" << "\t1'000'000" << std::endl;

    std::vector<int> Threads{1, 2, 4, 8, 16};
    std::vector<int> Size_v{1'000, 10'000, 100'000, 1'000'000};

    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> start_stop;
    std::vector<int> resoult;

    for(auto& c_Thread : Threads)
    {
        if(c_Thread == 1) std::cout << c_Thread << " stream " << '\t';
        else std::cout << c_Thread << " streams ";

        for (auto& c_Vector : Size_v)
        {
            valueInVector(v1, v2, c_Vector);

            int size_Threads = static_cast<int> (c_Vector / c_Thread);
            for (int i = 0; i <= c_Thread - 1; ++i)
            {
                start_stop.push_back(i * size_Threads);
            }
            start_stop.push_back(c_Vector - 1);

            std::vector<std::thread> th;

            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < c_Thread; i++)
            {
                th.push_back(std::thread(sum_vec, v1, v2, resoult, start_stop[i], start_stop[i + 1] - 1));
            }

            for (auto& it : th)
            {
                it.join();
            }

            auto stop = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> time = stop - start;
            std::cout << "\t" << time.count() << "ms";
        }
        std::cout << std::endl;
    }
}
