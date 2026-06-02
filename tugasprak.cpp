#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>
using namespace std;

class TokoElektronik {
    private:
    array<string, 3> barang;
    public:
    TokoElektronik() {
        barang[0] = "Laptop";
        barang[1] = "Smartphone";
        barang[2] = "Printer";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return barang.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
                );
        }
    }
};

void tampilkanBarang() {
    ifstream file("gudang.txt");

    cout << "\n===== DATA BARANG DI GUDANG =====" << endl;

    if (!file) {
        cout << "File belum tersedia." << endl;
        return;
    }

    string barang;
    int no = 1;

    while (getline(file, barang)) {
        cout << no++ << ". " << barang << endl;
    }

    if (no == 1) {
        cout << "Gudang masih kosong." << endl;
    }

    file.close();
}

void tambahBarang() {
    ofstream file("gudang.txt", ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Barang berhasil ditambahkan." << endl;
}

void updateBarang() {
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong." << endl;
        return;
    }
    tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid." << endl;
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru: ";
    getline(cin, data[nomor - 1]);

    ofstream out("gudang.txt");

    for (string item : data) {
        out << item << endl;
    }

    out.close();

    cout << "Data berhasil diperbarui." << endl;
}

void hapusBarang() {
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong." << endl;
        return;
    }

     tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang ingin dihapus: " << endl;
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid." << endl;
        return;
    }

    data.erase(data.begin() + (nomor - 1));

    ofstream out("gudang.txt");

    for (string item : data) {
        out << item << endl;
    }

    out.close();

    cout << "Barang berhasil dihapus." << endl;
}

void simulasiEtalase() {
    TokoElektronik toko;

    cout << "===== SIMULASI ETALASE =====" << endl;

    try {
        cout << "Skenario 1 (Rak 1)" << endl;
        cout << "Barang ditemukan: "
            << toko.ambilProduk(1)
            << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    try {
        cout << "Skenario 2 (Rak 5)" << endl;
        cout << "Barang ditemukan: "
            << toko.ambilProduk(5)
            << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n====================================";
        cout << "\n SISTEM TOKO ELEKTRONIK GIBRAN JAYA";
        cout << "\n====================================";

        tampilkanBarang();

        cout << "\n\nMENU";
        cout << "\n1. Tambah Barang (Create)";
        cout << "\n2. Lihat Barang (Read)";
        cout << "\n3. Update Barang";
        cout << "\n4. Hapus Barang (Delete)";
        cout << "\n5. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan : ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            tampilkanBarang();
            break;

        case 3:
            updateBarang();
            break;

        case 4:
            hapusBarang();
            break;

        case 5:
            simulasiEtalase();
            break;

        case 0:
            cout << "Terima kasih telah menggunakan sistem.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);
    return 0;
}