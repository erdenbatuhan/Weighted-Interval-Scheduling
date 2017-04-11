//
//  main.cpp
//  WeightedIntervalScheduling
//
//  Created by Batuhan Erden on 30/03/2017.
//  Copyright © 2017 Batuhan Erden. All rights reserved.
//

#include <iostream>
#include <algorithm>
#define MAX_N   101

using namespace std;

struct Job {
    int startingTime, finishingTime, weight;
};

struct JobComparator {
    bool operator() (const Job &a, const Job &b) {
        return a.finishingTime < b.finishingTime;
    }
};

bool isCompatible(const Job &a, const Job &b) {
    return a.finishingTime <= b.startingTime;
}

int binarySearch(Job jobs[], int current, int left, int right) {
    if (left > right)
        return 0;
    
    int mid = (left + right) / 2;
    
    if (isCompatible(jobs[mid], jobs[current]))
        if (isCompatible(jobs[mid + 1], jobs[current]))
            return binarySearch(jobs, current, mid + 1, right);
        else
            return mid;
    else
        return binarySearch(jobs, current, left, mid - 1);
}

int getLatestAvailableJob(Job jobs[], int current) {
    return binarySearch(jobs, current, 0, current - 1);
}

void computeP(int n, Job jobs[], int p[]) {
    for (int i = 1; i <= n; i++)
        p[i] = getLatestAvailableJob(jobs, i);
}

int WeightedIntervalScheduling(int n, Job jobs[]) {
    sort(jobs, jobs + n + 1, JobComparator());
    
    int p[n + 1];
    computeP(n, jobs, p);
    
    int M[n + 1];
    M[0] = 0;
    
    for (int i = 1; i <= n; i++)
        M[i] = max(jobs[i].weight + M[p[i]], M[i - 1]);
    
    return M[n];
}

void readInput(int &n, Job jobs[]) {
    freopen("/Users/batuhan/Documents/Xcode Workspace/WeightedIntervalScheduling/jobs", "r", stdin);
    while (scanf("%d%d%d", &jobs[n].startingTime, &jobs[n].finishingTime, &jobs[n].weight) == 3)
        n++;
    n--;
}

int main(int argc, const char *argv[]) {
    int n = 1;
    Job jobs[MAX_N];
    
    readInput(n, jobs);
    
    printf("Optimal Weight: %d\n", WeightedIntervalScheduling(n, jobs));
    return 0;
}

/*
 Sample jobs file
 ----------------
    1 4 30
    3 5 20
    0 6 60
    4 7 30
    3 8 50
    5 9 40
 ----------------
*/
