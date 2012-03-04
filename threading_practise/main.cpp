#include <iostream>
#include <boost/thread.hpp>
#include <vector>

/*
This is a simple multithreading practise
It does nothing of use

Run time:
8 threads: 15 362ms
4 threads: 18 081ms
3 threads: 22 387ms
2 threads: 31 310ms
1 threads: 57 408ms 
*/

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

boost::mutex mutex_lock;
int threads_ready = 0;

// Returns a two dimensional array of floats
float** giveFloatArray2D(int sizeX, int sizeY)
{
    float** out;
    out = new float*[sizeX];
    for (int i = 0; i < sizeX; i++)
    {
        out[i]= new float[sizeY];
    }

    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
            out[i][j] = 0.0f;
    }
    return out;
}

// Calculates some redundant big calculations
float doBigCalculation(int x, int y)
{
    float out = 0.0f;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                out = out - i*j + k * 0.000005 * x - y;
            }
        }
    }
    return out;
}


void reportReady()
{
    mutex_lock.lock();
    fprintf(stderr, "Thread is locking thread_ready: %d\n", threads_ready);
    threads_ready++;
    mutex_lock.unlock();
}

// Sets elements from start to stop to some value for array arr
void setElements(float** arr, int start_x, int stop_x, int start_y, int stop_y)
{
    for (int i = start_x; i < stop_x; i++)
    {
        for (int j = start_y; j < stop_y; j++)
        {
            arr[i][j] = doBigCalculation(i,j);
        }
    }
    reportReady();
}

int main()
{
    float** bigArray = giveFloatArray2D(1024, 1024);
    int numberOfThreads = 1;
    std::vector<boost::thread*> threadContainer;

    fprintf(stderr, "Start\n");
#ifdef WIN32
    unsigned long start = GetTickCount(); // For sort time calculation
#else
    timeval startTime;
    timeval endTime;
    gettimeofday(&startTime, 0);
#endif

    // Split the work based on numberOfThreads
    int workPerThread = floor(1024.0 / float(numberOfThreads));

    // Create threads and give them some work
    for (int i = 0; i < numberOfThreads; i++)
    {
        boost::thread coolThread(setElements, bigArray, i*workPerThread, (i+1)*workPerThread, 0, 1024);
        boost::thread* threadPtr = &coolThread;
        threadContainer.push_back(threadPtr);
    }

    fprintf(stderr, "Main is waiting for threads\n");
    
    while (threads_ready < numberOfThreads)
    {
    }

    // Join the threads
    std::vector<boost::thread*>::iterator iter;
    for (iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
    {
        (*iter)->join();
    }

#ifdef WIN32
    unsigned long end = GetTickCount();
    fprintf(stderr, "Compute time: %dms\n", end-start);
#else
    gettimeofday(&endTime, 0);
    fprintf(stderr, "Time used for computing: %ld.%ld\n", endTime.tv_sec - startTime.tv_sec, endTime.tv_usec - startTime.tv_usec);
#endif
    while (1);
    return 0;
}