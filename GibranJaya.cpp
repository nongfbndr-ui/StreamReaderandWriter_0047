#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

class TokoElektronik
{
private:
    array<string, 3> etalase;

public:
    TokoElektronik()
    {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "TV";
    }

    string ambilProduk(size_t nomorRak)
    {
        try
        {
            return etalase.at(nomorRak);
        }
        catch (out_of_range&)
        {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

void readData()
{
    ifstream file("gudang.txt");

    string barang;
    int no = 1;

    cout << "\n===== DATA GUDANG =====\n";

    while (getline(file, barang))
    {
        cout << no++ << ". " << barang << endl;
    }

    if (no == 1)
    {
        cout << "Data masih kosong\n";
    }

    file.close();
}

void createData()
{
    ofstream file("gudang.txt", ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang : ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Data berhasil ditambahkan\n";
}

void updateData()
{
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.size() == 0)
    {
        cout << "Data kosong\n";
        return;
    }

    readData();

    int nomor;
    cout << "Pilih nomor barang yang ingin diubah : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid\n";
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru : ";
    getline(cin, data[nomor - 1]);

    ofstream tulis("gudang.txt");

    for (int i = 0; i < data.size(); i++)
    {
        tulis << data[i] << endl;
    }

    tulis.close();

    cout << "Data berhasil diupdate\n";
}

void deleteData()
{
    ifstream file("gudang.txt");

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.size() == 0)
    {
        cout << "Data kosong\n";
        return;
    }

    readData();

    int nomor;
    cout << "Pilih nomor barang yang ingin dihapus : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid\n";
        return;
    }

    data.erase(data.begin() + nomor - 1);

    ofstream tulis("gudang.txt");

    for (int i = 0; i < data.size(); i++)
    {
        tulis << data[i] << endl;
    }

    tulis.close();

    cout << "Data berhasil dihapus\n";
}

void simulasiEtalase()
{
    TokoElektronik toko;

    cout << "\n=== SIMULASI ETALASE ===\n";

    try
    {
        cout << "Rak 1 : "
             << toko.ambilProduk(1) << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }

    try
    {
        cout << "Rak 5 : "
             << toko.ambilProduk(5) << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }
}

int main()
{
    int pilih;

    do
    {
        cout << "\n============================\n";
        cout << "TOKO ELEKTRONIK GIBRAN JAYA\n";
        cout << "============================\n";

        readData();

        cout << "\n1. Tambah Barang";
        cout << "\n2. Update Barang";
        cout << "\n3. Hapus Barang";
        cout << "\n4. Simulasi Etalase";
        cout << "\n5. Keluar";
        cout << "\nPilihan : ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            createData();
            break;

        case 2:
            updateData();
            break;

        case 3:
            deleteData();
            break;

        case 4:
            simulasiEtalase();
            break;

        case 5:
            cout << "Program selesai\n";
            break;

        default:
            cout << "Pilihan tidak tersedia\n";
        }

    } while (pilih != 5);

    return 0;
}