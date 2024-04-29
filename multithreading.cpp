#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <ranges>

namespace multithreading {

using namespace std;
typedef unsigned long long ull;

void getEvenSum(ull start, ull end, promise<ull>&& sum) {
    int s = 0;
    for(ull i = start; i < end; ++i) {
        if((i & 1) == 0) {
            s += i;
        }
    }
    sum.set_value(s);
}

void getOddSum(ull start, ull end, promise<ull>&& sum) {
    int s = 0;
    for(ull i = start; i < end; ++i) {
        if((i & 1) != 0) {
            s += i;
        }
    }
    sum.set_value(s);
}

void runEvenOddSums() {
    ull start = 0, end = 1000000000;
    auto startTime = chrono::high_resolution_clock::now();

    promise<ull> evenSum;
    promise<ull> oddSum;

    auto evenSumFuture = evenSum.get_future();
    auto oddSumFuture = oddSum.get_future();

    thread t1(&getEvenSum, start, end, std::move(evenSum));
    thread t2(&getOddSum, start, end, std::move(oddSum));

    t1.join();
    t2.join();

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    cout << "OddSum = " << oddSumFuture.get() << '\n';
    cout << "EvenSum = " << evenSumFuture.get() << '\n';
    cout << "total time: " << duration.count()/1000000 << '\n';
    // no threads: 7s
    // threads: 2s
}

void func(int x, int id) {
    while(x-- > 0) {
        cout << "func" << id << ": " << x << '\n';
    }
}

void runFunc() {
    std::thread t1(func, 10, 1);
    std::thread t2(func, 10, 2);
    t1.detach();
    t2.detach();
}

void runLamdba() {
    auto func = [](int x, int id) {
        while(x-- > 0) {
            cout << "func" << id << ": " << x << '\n';
        }
    };

    thread t(func, 10, 1);
    t.join();
}

struct Base {
    void func(int x, int id) {
        while(x-- > 0) {
            cout << "func" << id << ": " << x << '\n';
        }
    }

    void operator() (int x, int id) {
        func(x, id);
    }
};

void runFunctor() {
    thread t((Base()), 10, 1);
    t.join();
}

void runNonStaticMember() {
    Base b;
    thread t(&Base::func, &b, 10, 1);
    t.join();
}

struct Base1 {
    static void func(int x, int id) {
        while(x-- > 0) {
            cout << "func" << id << ": " << x << '\n';
        }
    }
};

void runStaticMember() {
    thread t(&Base1::func, 10, 1);
    t.join();
}

void printer(int x, int id) {
    while(x-- > 0) {
        cout << id << " Abhi" << '\n';
    }
    this_thread::sleep_for(chrono::seconds(3));
}

void runJoinDetach() {
    thread t1(printer, 3, 1);
    thread t2(printer, 3, 2);

    t1.detach();
    t2.detach();
    cout << "In main()\n";
    if(t1.joinable()) {
        t1.join();
    }
    cout << "t1 joined\n";
    if(t2.joinable()) {
        t2.join();
    }
    cout << "t2 joined\n";
}

namespace mutexLock {

int amt = 0;
std::mutex m;

void add(int x) {
    m.lock();
    amt += x;
    cout << "adding " << x << '\n';
    m.unlock();
}

void runMutex() {
    //vector<thread> threads;
    
    thread t1(add, 1);
    thread t2(add, 2);
    t1.join();
    t2.join();
    cout << "after joins: " << amt << "\n";
}
}

namespace trylock {

int counter = 0;
int count1 = 0;
int count2 = 0;
mutex m;

void countTime(int id) {
    for(int i = 0; i < 100000; ++i) {
        if( m.try_lock() ) {
            if(id == 1) {
                count1++;
            } else {
                count2++;
            }
            ++counter;
            m.unlock();
        }
    }
}

void runTryLock() {
    thread t1(countTime, 1);
    thread t2(countTime, 2);

    t1.join();
    t2.join();

    cout << "id 1 got lock success " << count1 << " times\n";
    cout << "id 2 got lock success " << count2 << " times\n";
    cout << "Counter value: " << counter << '\n';
}

}

namespace ntrylocks {

    // use c++20 to run: g++ *.cpp -std=c++2a; ./a.out

    int X = 0;
    int Y = 0;
    std::mutex m1, m2;

    void doWorkForSecs(int seconds) {
        this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void incrementXY( int& XorY, mutex& m, const char* desc ) {
        for(int _ : ranges::iota_view{0, 5}) {
            //m.lock();
            if( m.try_lock() ) {
                ++XorY;
                cout << desc << XorY << '\n';
                m.unlock();
            }
            doWorkForSecs(1);
        }
    }

    void consumeXY() {
        int useCount = 5;
        int XplusY = 0;
        while(true) {
            int lockResult = try_lock(m1,m2);
            if(lockResult == -1) {
                if(X != 0 && Y != 0) {
                    --useCount;
                    XplusY += X + Y;
                    X = 0;
                    Y = 0;
                    cout << "XplusY " << XplusY << '\n';
                }
                m1.unlock();
                m2.unlock();
                if( useCount == 0 ) break;
            }
        }
    }

    void runNTryLocks() {
        thread t1(incrementXY, ref(X), ref(m1), "X ");
        thread t2(incrementXY, ref(Y), ref(m2), "Y ");
        thread t3(consumeXY);

        t1.join();
        t2.join();
        t3.join();
    }
}

namespace timedMutex {
    int myAmount = 0;
    timed_mutex m;
}
}
