#include <iostream>
#include "soal1.h"

int main() {
    Queue A, B;
    createQueue(A);
    createQueue(B);
    Statistik stat = {0, 0};

    std::cout << "=== URUTAN UJI UTAMA SOAL 1 ===\n";
    masukPaket(A, B, "P17", 450);
    masukPaket(A, B, "P28", 700);
    masukPaket(A, B, "P36", 550);

    std::cout << "\n1. PINDAH 2\n";
    pindahPaket(A, B, 2);

    std::cout << "\n2. MASUK P42 600\n";
    masukPaket(A, B, "P42", 600);

    std::cout << "\n3. PINDAH 3\n";
    pindahPaket(A, B, 3);

    std::cout << "\n4. PINDAH 1\n";
    pindahPaket(A, B, 1);

    std::cout << "\n5. KIRIM 2\n";
    kirimPaket(B, 2, stat);

    std::cout << "\n6. CARI P36\n";
    cariPaket(A, B, "P36");

    std::cout << "\n7. KIRIM 2\n";
    kirimPaket(B, 2, stat);

    std::cout << "\n8. PINDAH 1\n";
    pindahPaket(A, B, 1);

    std::cout << "\n9. KIRIM 2\n";
    kirimPaket(B, 2, stat);

    std::cout << "\n=== UJI TAMBAHAN ===\n";
    masukPaket(A, B, "P36", 0);            // Berat invalid
    masukPaket(A, B, "P55", 800);
    masukPaket(A, B, "P55", 300);          // Duplikat A
    pindahPaket(A, B, 1);
    masukPaket(A, B, "P55", 300);          // Duplikat B
    pindahPaket(A, B, 0);                  // n = 0 invalid
    cariPaket(A, B, "XYZ");                // Kode tidak ada

    std::cout << "\n--- BERSIHKAN --- \n";
    bersihkanSistem(A, B);
    rekapPaket(A, B, stat);

    std::cout << "\n--- ISI KEMBALI SETELAH BERSIHKAN --- \n";
    masukPaket(A, B, "NEW1", 100);
    pindahPaket(A, B, 1);
    kirimPaket(B, 1, stat);
    rekapPaket(A, B, stat);

    selesaiSistem(A, B);
    return 0;
}