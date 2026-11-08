#define VERSI_3
#include "soal2.h"

void createBuffer(BufferQueue& Q) {
    Q.head = 0;
    Q.count = 0;
    Q.next_no_urut = 1;
    Q.count_pergeseran = 0;
}

bool isEmptyBuffer(const BufferQueue& Q) { return Q.count == 0; }
int getCountBuffer(const BufferQueue& Q) { return Q.count; }

bool tulisBatch(BufferQueue& Q, int k, const int vals[]) {
    if (k < 1 || k > 6 || (6 - Q.count) < k) return false;
    for (int i = 0; i < k; i++) if (vals[i] < -1000 || vals[i] > 1000) return false;

    for (int i = 0; i < k; i++) {
        int idx_tulis = (Q.head + Q.count) % 6;
        Q.data[idx_tulis].no_urut = Q.next_no_urut++;
        Q.data[idx_tulis].nilai = vals[i];
        Q.count++;
    }
    return true;
}

bool ambilBatch(BufferQueue& Q, int k) {
    if (k < 1 || k > Q.count) return false;
    for (int step = 0; step < k; step++) {
        std::cout << Q.data[Q.head].no_urut << ":" << Q.data[Q.head].nilai << (step == k-1 ? "" : ", ");
        Q.head = (Q.head + 1) % 6;
        Q.count--;
    }
    std::cout << "\n";
    return true;
}

void lihatBuffer(const BufferQueue& Q) {
    std::cout << "Urutan FIFO: ";
    if (isEmptyBuffer(Q)) std::cout << "[Kosong]\n";
    else {
        for (int i = 0; i < Q.count; i++) {
            int idx = (Q.head + i) % 6;
            std::cout << Q.data[idx].no_urut << ":" << Q.data[idx].nilai << (i == Q.count - 1 ? "" : ", ");
        }
        std::cout << "\n";
    }
    std::cout << "Keadaan Fisik Array (0-5):\n";
    for (int i = 0; i < 6; i++) {
        bool in_use = false;
        for (int j = 0; j < Q.count; j++) {
            if ((Q.head + j) % 6 == i) in_use = true;
        }
        if (in_use)
            std::cout << "[" << i << "] " << Q.data[i].no_urut << ":" << Q.data[i].nilai << "  ";
        else std::cout << "[" << i << "] KOSONG  ";
    }
    std::cout << "\nPenanda: head=" << Q.head << ", count=" << Q.count 
              << ", Total Shift=" << Q.count_pergeseran << "\n";
}

void ringkasBuffer(const BufferQueue& Q) {
    if (isEmptyBuffer(Q)) {
        std::cout << "Jumlah: 0, Total: 0, Min: TIDAK ADA, Max: TIDAK ADA, Rata-rata: TIDAK ADA\n";
        return;
    }
    int total = 0, min_val = Q.data[Q.head].nilai, max_val = Q.data[Q.head].nilai;
    for (int i = 0; i < Q.count; i++) {
        int idx = (Q.head + i) % 6;
        int v = Q.data[idx].nilai;
        total += v;
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }
    std::cout << "Jumlah: " << Q.count << ", Total: " << total << ", Min: " << min_val 
              << ", Max: " << max_val << ", Rata-rata: " << std::fixed << std::setprecision(2) << ((double)total / Q.count) << "\n";
}

void kosongkanBuffer(BufferQueue& Q) {
    Q.head = 0;
    Q.count = 0;
}