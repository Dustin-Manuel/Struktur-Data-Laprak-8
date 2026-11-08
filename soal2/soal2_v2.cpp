#define VERSI_2
#include "soal2.h"

void createBuffer(BufferQueue& Q) {
    Q.head = -1;
    Q.tail = -1;
    Q.next_no_urut = 1;
    Q.count_pergeseran = 0;
}

bool isEmptyBuffer(const BufferQueue& Q) { return Q.head == -1; }
int getCountBuffer(const BufferQueue& Q) { return isEmptyBuffer(Q) ? 0 : (Q.tail - Q.head + 1); }

bool tulisBatch(BufferQueue& Q, int k, const int vals[]) {
    if (k < 1 || k > 6 || (6 - getCountBuffer(Q)) < k) return false;
    for (int i = 0; i < k; i++) if (vals[i] < -1000 || vals[i] > 1000) return false;

    // Geser/Padatkan jika tail sudah di 5 dan butuh ruang di depan
    if (Q.tail + k >= 6) {
        int active_cnt = getCountBuffer(Q);
        for (int i = 0; i < active_cnt; i++) {
            Q.data[i] = Q.data[Q.head + i];
            Q.count_pergeseran++;
        }
        Q.head = 0;
        Q.tail = active_cnt - 1;
    }

    for (int i = 0; i < k; i++) {
        if (isEmptyBuffer(Q)) {
            Q.head = 0;
            Q.tail = 0;
        } else {
            Q.tail++;
        }
        Q.data[Q.tail].no_urut = Q.next_no_urut++;
        Q.data[Q.tail].nilai = vals[i];
    }
    return true;
}

bool ambilBatch(BufferQueue& Q, int k) {
    if (k < 1 || k > getCountBuffer(Q)) return false;
    for (int step = 0; step < k; step++) {
        std::cout << Q.data[Q.head].no_urut << ":" << Q.data[Q.head].nilai << (step == k-1 ? "" : ", ");
        Q.head++;
    }
    if (Q.head > Q.tail) {
        Q.head = -1;
        Q.tail = -1;
    }
    std::cout << "\n";
    return true;
}

void lihatBuffer(const BufferQueue& Q) {
    std::cout << "Urutan FIFO: ";
    if (isEmptyBuffer(Q)) std::cout << "[Kosong]\n";
    else {
        for (int i = Q.head; i <= Q.tail; i++) {
            std::cout << Q.data[i].no_urut << ":" << Q.data[i].nilai << (i == Q.tail ? "" : ", ");
        }
        std::cout << "\n";
    }
    std::cout << "Keadaan Fisik Array (0-5):\n";
    for (int i = 0; i < 6; i++) {
        if (i >= Q.head && i <= Q.tail && !isEmptyBuffer(Q))
            std::cout << "[" << i << "] " << Q.data[i].no_urut << ":" << Q.data[i].nilai << "  ";
        else std::cout << "[" << i << "] KOSONG  ";
    }
    std::cout << "\nPenanda: head=" << Q.head << ", tail=" << Q.tail 
              << ", Total Shift=" << Q.count_pergeseran << "\n";
}

void ringkasBuffer(const BufferQueue& Q) {
    int cnt = getCountBuffer(Q);
    if (cnt == 0) {
        std::cout << "Jumlah: 0, Total: 0, Min: TIDAK ADA, Max: TIDAK ADA, Rata-rata: TIDAK ADA\n";
        return;
    }
    int total = 0, min_val = Q.data[Q.head].nilai, max_val = Q.data[Q.head].nilai;
    for (int i = Q.head; i <= Q.tail; i++) {
        int v = Q.data[i].nilai;
        total += v;
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
    }
    std::cout << "Jumlah: " << cnt << ", Total: " << total << ", Min: " << min_val 
              << ", Max: " << max_val << ", Rata-rata: " << std::fixed << std::setprecision(2) << ((double)total / cnt) << "\n";
}

void kosongkanBuffer(BufferQueue& Q) {
    Q.head = -1;
    Q.tail = -1;
}