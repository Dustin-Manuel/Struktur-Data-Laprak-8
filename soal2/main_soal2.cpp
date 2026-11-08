#include <iostream>
#include "soal2.h"

int main() {
    BufferQueue Q;
    createBuffer(Q);

    std::cout << "=== HARUS BERJALAN SAMA DI KETIGA VERSI ===\n";

    int batch1[] = {12, -4, 7, 0, 15, 6};
    std::cout << "\n1. TULIS 6 (12 -4 7 0 15 6)\n";
    if (tulisBatch(Q, 6, batch1)) std::cout << "Berhasil Tulis 6 paket.\n";

    std::cout << "\n2. AMBIL 2\n";
    ambilBatch(Q, 2);

    int batch2[] = {9, 11, -2};
    std::cout << "\n3. TULIS 3 (9 11 -2) [Harus Ditolak]\n";
    if (!tulisBatch(Q, 3, batch2)) std::cout << "Ditolak seluruhnya: Ruang kosong tidak cukup.\n";

    int batch3[] = {9, -2};
    std::cout << "\n4. TULIS 2 (9 -2)\n";
    if (tulisBatch(Q, 2, batch3)) std::cout << "Berhasil Tulis 2 paket.\n";

    std::cout << "\n5. RINGKAS\n";
    ringkasBuffer(Q);

    std::cout << "\n6. LIHAT DETAIL PERGESERAN & FISIK\n";
    lihatBuffer(Q);

    std::cout << "\n=== UJI TAMBAHAN ===\n";
    std::cout << "Coba AMBIL 7 (Harus Ditolak): " << (ambilBatch(Q, 7) ? "Berhasil" : "Ditolak") << "\n";
    std::cout << "AMBIL 6:\n";
    ambilBatch(Q, 6);
    std::cout << "AMBIL 1 (Harus Ditolak): " << (ambilBatch(Q, 1) ? "Berhasil" : "Ditolak") << "\n";

    int invalid_batch[] = {4, 1001};
    std::cout << "TULIS 2 4 1001 (Harus Ditolak): " << (tulisBatch(Q, 2, invalid_batch) ? "Berhasil" : "Ditolak") << "\n";

    int valid_single[] = {-1};
    tulisBatch(Q, 1, valid_single);
    std::cout << "Isi setelah TULIS 1 -1 (Rekaman ke-9):\n";
    lihatBuffer(Q);

    kosongkanBuffer(Q);
    std::cout << "Setelah KOSONGKAN:\n";
    lihatBuffer(Q);

    return 0;
}