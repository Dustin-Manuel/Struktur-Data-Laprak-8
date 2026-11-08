#include "soal1.h"

void createQueue(Queue& Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(const Queue& Q) {
    return Q.head == nullptr;
}

Node* alokasi(std::string kode, int berat) {
    Node* P = new (std::nothrow) Node;
    if (P != nullptr) {
        P->info.kode = kode;
        P->info.berat = berat;
        P->next = nullptr;
    }
    return P;
}

void dealokasi(Node* P) {
    delete P;
}

void enqueue(Queue& Q, Node* P) {
    if (P == nullptr) return;
    P->next = nullptr;
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

Node* dequeue(Queue& Q) {
    if (isEmptyQueue(Q)) return nullptr;
    Node* P = Q.head;
    Q.head = Q.head->next;
    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }
    P->next = nullptr;
    return P;
}

Node* findElm(const Queue& Q, std::string kode) {
    Node* P = Q.head;
    while (P != nullptr) {
        if (P->info.kode == kode) return P;
        P = P->next;
    }
    return nullptr;
}

Node* fFindElm(const Queue& QA, const Queue& QB, std::string kode, char& lokasi, int& posisi) {
    Node* P = QA.head;
    int idx = 1;
    while (P != nullptr) {
        if (P->info.kode == kode) {
            lokasi = 'A';
            posisi = idx;
            return P;
        }
        P = P->next;
        idx++;
    }
    P = QB.head;
    idx = 1;
    while (P != nullptr) {
        if (P->info.kode == kode) {
            lokasi = 'B';
            posisi = idx;
            return P;
        }
        P = P->next;
        idx++;
    }
    lokasi = '-';
    posisi = -1;
    return nullptr;
}

int nbList(const Queue& Q) {
    int count = 0;
    Node* P = Q.head;
    while (P != nullptr) {
        count++;
        P = P->next;
    }
    return count;
}

int totalBerat(const Queue& Q) {
    int total = 0;
    Node* P = Q.head;
    while (P != nullptr) {
        total += P->info.berat;
        P = P->next;
    }
    return total;
}

void printInfo(const Queue& Q) {
    if (isEmptyQueue(Q)) {
        std::cout << "[Kosong]";
    } else {
        Node* P = Q.head;
        while (P != nullptr) {
            std::cout << P->info.kode << "(" << P->info.berat << "g)";
            if (P->next != nullptr) std::cout << " -> ";
            P = P->next;
        }
    }
    std::cout << "\n";
}

void delAll(Queue& Q) {
    while (!isEmptyQueue(Q)) {
        Node* P = dequeue(Q);
        dealokasi(P);
    }
}

bool masukPaket(Queue& QA, const Queue& QB, std::string kode, int berat) {
    if (kode.length() < 1 || kode.length() > 10 || berat < 1 || berat > 5000) {
        std::cout << "Ditolak: Data tidak valid (Kode 1-10 karakter, Berat 1-5000g).\n";
        return false;
    }
    if (findElm(QA, kode) != nullptr || findElm(QB, kode) != nullptr) {
        std::cout << "Ditolak: Kode '" << kode << "' sudah aktif di sistem.\n";
        return false;
    }
    Node* P = alokasi(kode, berat);
    if (P == nullptr) {
        std::cout << "Ditolak: Alokasi memori gagal.\n";
        return false;
    }
    enqueue(QA, P);
    std::cout << "Berhasil: Paket " << kode << " masuk ke antrean A.\n";
    return true;
}

bool pindahPaket(Queue& QA, Queue& QB, int n) {
    int sizeA = nbList(QA);
    if (n <= 0 || n > sizeA) {
        std::cout << "Ditolak: n harus positif dan <= jumlah paket di A (isi A: " << sizeA << ").\n";
        return false;
    }
    for (int i = 0; i < n; i++) {
        Node* P = dequeue(QA);
        enqueue(QB, P);
    }
    std::cout << "Berhasil memindahkan " << n << " paket dari A ke B.\n";
    return true;
}

bool kirimPaket(Queue& QB, int n, Statistik& stat) {
    int sizeB = nbList(QB);
    if (n <= 0 || n > sizeB) {
        std::cout << "Ditolak: n harus positif dan <= jumlah paket di B (isi B: " << sizeB << ").\n";
        return false;
    }
    for (int i = 0; i < n; i++) {
        Node* P = dequeue(QB);
        std::cout << "  > Terkirim: Paket " << P->info.kode << " (" << P->info.berat << "g)\n";
        stat.total_terkirim_count++;
        stat.total_terkirim_berat += P->info.berat;
        dealokasi(P);
    }
    return true;
}

void cariPaket(const Queue& QA, const Queue& QB, std::string kode) {
    char lokasi;
    int posisi;
    Node* P = fFindElm(QA, QB, kode, lokasi, posisi);
    if (P != nullptr) {
        std::cout << "Hasil Cari: Kode " << kode << " ada di antrean " << lokasi 
                  << ", Posisi: " << posisi << ", Berat: " << P->info.berat << " gram.\n";
    } else {
        std::cout << "Hasil Cari: TIDAK DITEMUKAN.\n";
    }
}

void rekapPaket(const Queue& QA, const Queue& QB, const Statistik& stat) {
    std::cout << "=== REKAP SISTEM ===\n";
    std::cout << "Antrean A : " << nbList(QA) << " paket, Total Berat: " << totalBerat(QA) << " g\n";
    std::cout << "Antrean B : " << nbList(QB) << " paket, Total Berat: " << totalBerat(QB) << " g\n";
    std::cout << "Terkirim  : " << stat.total_terkirim_count << " paket, Total Berat: " << stat.total_terkirim_berat << " g\n";
}

void bersihkanSistem(Queue& QA, Queue& QB) {
    delAll(QA);
    delAll(QB);
    std::cout << "Antrean A dan B telah dibersihkan.\n";
}

void selesaiSistem(Queue& QA, Queue& QB) {
    delAll(QA);
    delAll(QB);
    std::cout << "Memori dibebaskan. Program selesai.\n";
}