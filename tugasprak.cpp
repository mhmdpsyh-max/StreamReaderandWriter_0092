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
        