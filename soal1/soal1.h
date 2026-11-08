#ifndef SOAL1_H
#define SOAL1_H

#include <iostream>
#include <string>

struct Paket {
    std::string kode;
    int berat;
};

struct Node {
    Paket info;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

struct Statistik {
    int total_terkirim_count;
    int total_terkirim_berat;
};

// Prototipe Fungsi ADT Queue Paket
void createQueue(Queue& Q);
bool isEmptyQueue(const Queue& Q);
Node* alokasi(std::string kode, int berat);
void dealokasi(Node* P);
void enqueue(Queue& Q, Node* P);
Node* dequeue(Queue& Q);

Node* findElm(const Queue& Q, std::string kode);
Node* fFindElm(const Queue& QA, const Queue& QB, std::string kode, char& lokasi, int& posisi);

int nbList(const Queue& Q);
int totalBerat(const Queue& Q);
void printInfo(const Queue& Q);
void delAll(Queue& Q);

// Operasi Transaksi
bool masukPaket(Queue& QA, const Queue& QB, std::string kode, int berat);
bool pindahPaket(Queue& QA, Queue& QB, int n);
bool kirimPaket(Queue& QB, int n, Statistik& stat);
void cariPaket(const Queue& QA, const Queue& QB, std::string kode);
void rekapPaket(const Queue& QA, const Queue& QB, const Statistik& stat);
void bersihkanSistem(Queue& QA, Queue& QB);
void selesaiSistem(Queue& QA, Queue& QB);

#endif