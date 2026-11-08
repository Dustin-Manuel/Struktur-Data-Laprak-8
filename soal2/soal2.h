#ifndef SOAL2_H
#define SOAL2_H

#include <iostream>
#include <iomanip>

struct Rekaman {
    int no_urut;
    int nilai;
};

// Deklarasi Struktur Data per Versi
#if defined(VERSI_1) // Array Geser
struct BufferQueue {
    Rekaman data[6];
    int head;
    int tail;
    int next_no_urut;
    int count_pergeseran;
};
#elif defined(VERSI_2) // Array Pemadatan
struct BufferQueue {
    Rekaman data[6];
    int head;
    int tail;
    int next_no_urut;
    int count_pergeseran;
};
#else // VERSI_3: Circular Queue (head & count)
struct BufferQueue {
    Rekaman data[6];
    int head;
    int count;
    int next_no_urut;
    int count_pergeseran;
};
#endif

void createBuffer(BufferQueue& Q);
bool isFullBuffer(const BufferQueue& Q);
bool isEmptyBuffer(const BufferQueue& Q);
int getCountBuffer(const BufferQueue& Q);

bool tulisBatch(BufferQueue& Q, int k, const int vals[]);
bool ambilBatch(BufferQueue& Q, int k);
void lihatBuffer(const BufferQueue& Q);
void ringkasBuffer(const BufferQueue& Q);
void kosongkanBuffer(BufferQueue& Q);

#endif