#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Mobil{
    string plat;
    string pemilik;
    string kondisi;

    Mobil *left;
    Mobil *right;

    Mobil(string p, string nama){

        plat = p;
        pemilik = nama;
        kondisi = "Di Luar Parkiran";

        left = NULL;
        right = NULL;
    }
};

struct Riwayat{

    string plat;
    string aktivitas;

    Riwayat *next;
    Riwayat(string p, string a){

        plat = p;
        aktivitas = a;
        next = NULL;
    }
};

struct QueueParkir{
    string plat;

    QueueParkir *next;
    QueueParkir(string p){
        plat = p;
        next = NULL;
    }
};

Mobil *root = NULL;
Riwayat *topRiwayat = NULL;

QueueParkir *frontQ = NULL;
QueueParkir *rearQ = NULL;

const int kapasitas = 3;
int totalParkir = 0;

void garis(){
    cout << "================================================================================\n";
}

void judul(string teks){

    system("cls");

    cout << "            SISTEM PARKIR BANDARA GSA\n";
    garis();
    cout << teks << endl;
}

void pauseProgram(){
    cout << "\n";
    garis();
    cout << "Tekan ENTER";
	cin.get();
}

Mobil* insertMobil(Mobil *node, string plat, string nama){

    if(node == NULL){
        return new Mobil(plat, nama);
    }
    if(plat < node->plat){
        node->left = insertMobil(node->left, plat, nama);
    }
    else if(plat > node->plat){
        node->right = insertMobil(node->right, plat, nama);
    }
    return node;
}

Mobil* searchMobil(Mobil *node, string plat){
    if(node == NULL || node->plat == plat){
        return node;
    }
    if(plat < node->plat){
        return searchMobil(node->left, plat);
    }
    return searchMobil(node->right, plat);
}

void tampilData(Mobil *node){

    if(node != NULL){
        tampilData(node->left);

        cout << "| "
             << left << setw(20) << node->plat
             << "| "
             << setw(25) << node->pemilik
             << "| "
             << setw(25) << node->kondisi
             << "|" << endl;

        tampilData(node->right);
    }
}

Mobil* nodeTerkecil(Mobil *node){
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}

Mobil* deleteMobil(Mobil *node, string plat){
    if(node == NULL){
        return node;
    }
    if(plat < node->plat){
        node->left = deleteMobil(node->left, plat);
    }
    else if(plat > node->plat){
        node->right = deleteMobil(node->right, plat);
    }
    else{
        if(node->left == NULL){
            Mobil *temp = node->right;
            delete node;
            return temp;
        }
        else if(node->right == NULL){
            Mobil *temp = node->left;
            delete node;
            return temp;
        }
        Mobil *temp = nodeTerkecil(node->right);

        node->plat = temp->plat;
        node->pemilik = temp->pemilik;
        node->kondisi = temp->kondisi;

        node->right = deleteMobil(node->right, temp->plat);
    }
    return node;
}

void pushRiwayat(string plat, string aksi){
    Riwayat *baru = new Riwayat(plat, aksi);

    baru->next = topRiwayat;
    topRiwayat = baru;
}

void undoParkir(){
    judul("UNDO AKSI");

    cout << endl;

    if(topRiwayat == NULL){
        cout << "Tidak ada aksi untuk di-undo\n";

        pauseProgram();
        return;
    }
    Riwayat *hapus = topRiwayat;
    topRiwayat = topRiwayat->next;

    Mobil *mobil = searchMobil(root, hapus->plat);

    if(mobil != NULL){
        if(hapus->aktivitas == "masuk"){
            mobil->kondisi = "Di Luar Parkiran";
            totalParkir--;
            cout << "Undo : Kendaraan keluar dari parkiran\n";
        }
        else{
            mobil->kondisi = "Di Parkiran";
            totalParkir++;
            cout << "Undo : Kendaraan masuk kembali ke parkiran\n";
        }
    }
    delete hapus;
    pauseProgram();
}

void enqueueMobil(string plat){

    QueueParkir *baru = new QueueParkir(plat);

    if(rearQ == NULL){
        frontQ = rearQ = baru;
    }
    else{
        rearQ->next = baru;
        rearQ = baru;
    }
}

string dequeueMobil(){

    if(frontQ == NULL){
        return "";
    }

    QueueParkir *hapus = frontQ;
    string plat = hapus->plat;

    frontQ = frontQ->next;

    if(frontQ == NULL){
        rearQ = NULL;
    }
    delete hapus;
    return plat;
}

void tambahData(){

    judul("TAMBAH KENDARAAN");
    cout << endl;
    string plat, nama;

    cout << "Nomor Polisi : ";
    getline(cin, plat);

    cout << "Nama Pemilik : ";
    getline(cin, nama);

    root = insertMobil(root, plat, nama);

    cout << "\nData kendaraan berhasil ditambahkan\n";
    pauseProgram();
}

void tampilKendaraan(){

    judul("DATA KENDARAAN");
    cout << endl;

    if(root == NULL){
        cout << "Data kendaraan kosong\n";
    }
    else{

        garis();

        cout << "| "
             << left << setw(20) << "No Polisi"
             << "| "
             << setw(25) << "Pemilik"
             << "| "
             << setw(25) << "Status"
             << "|" << endl;
        garis();
        tampilData(root);
        garis();
    }
    pauseProgram();
}

void kendaraanMasuk(){

    judul("KENDARAAN MASUK");
    cout << endl;

    string plat;

    cout << "Nomor Polisi : ";
    getline(cin, plat);

    Mobil *mobil = searchMobil(root, plat);

    if(mobil == NULL){
        cout << "Kendaraan tidak ditemukan\n";
    }
    else if(mobil->kondisi == "Di Parkiran"){
        cout << "Kendaraan sudah berada di parkiran\n";
    }
    else{
        if(totalParkir < kapasitas){
            mobil->kondisi = "Di Parkiran";
            totalParkir++;
            pushRiwayat(plat, "masuk");
            cout << "\nKendaraan berhasil masuk\n";
        }
        else{
            enqueueMobil(plat);
            cout << "\nParkiran penuh, kendaraan masuk antrian\n";
        }
    }
    pauseProgram();
}

void kendaraanKeluar(){
    judul("KENDARAAN KELUAR");
    cout << endl;

    string plat;

    cout << "Nomor Polisi : ";
    getline(cin, plat);

    Mobil *mobil = searchMobil(root, plat);
    if(mobil == NULL){
        cout << "Kendaraan tidak ditemukan\n";
    }
    else if(mobil->kondisi == "Di Luar Parkiran"){
        cout << "Kendaraan tidak berada di parkiran\n";
    }
    else{
        mobil->kondisi = "Di Luar Parkiran";
        totalParkir--;
        pushRiwayat(plat, "keluar");

        cout << "\nKendaraan berhasil keluar\n";

        if(frontQ != NULL){
            string next = dequeueMobil();

            Mobil *antri = searchMobil(root, next);

            if(antri != NULL){
                antri->kondisi = "Di Parkiran";
                totalParkir++;
            }
            cout << "Kendaraan antrian masuk parkiran\n";
        }
    }
    pauseProgram();
}

void hapusData(){

    judul("HAPUS KENDARAAN");
    cout << endl;

    string plat;

    cout << "Nomor Polisi : ";
    getline(cin, plat);

    if(searchMobil(root, plat) == NULL){
        cout << "Kendaraan tidak ditemukan\n";
    }
    else{
        root = deleteMobil(root, plat);
        cout << "\nData kendaraan berhasil dihapus\n";
    }
    pauseProgram();
}

void tampilAntrian(){

    judul("ANTRIAN PARKIR");
    cout << endl;

    if(frontQ == NULL){
        cout << "Antrian kosong\n";
    }
    else{
        QueueParkir *bantu = frontQ;
        int no = 1;
        garis();

        while(bantu != NULL){
            cout << no << ". "
                 << bantu->plat
                 << " menunggu giliran masuk parkiran\n";
            bantu = bantu->next;
            no++;
        }
        garis();
    }
    pauseProgram();
}

int main(){
    int pilih;

    do{
        judul("MENU UTAMA");

        cout << endl;

        cout << "1. Tambah Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Kendaraan Masuk\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Hapus Kendaraan\n";
        cout << "6. Undo\n";
        cout << "7. Tampil Antrian\n";
        cout << "8. Keluar\n";

        garis();

        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih){

            case 1:
                tambahData();
                break;

            case 2:
                tampilKendaraan();
                break;

            case 3:
                kendaraanMasuk();
                break;

            case 4:
                kendaraanKeluar();
                break;

            case 5:
                hapusData();
                break;

            case 6:
                undoParkir();
                break;

            case 7:
                tampilAntrian();
                break;

            case 8:

                judul("PROGRAM SELESAI");

                cout << endl;

                cout << "Terima kasih sudah menggunakan program\n";
                break;

            default:
                cout << "Menu tidak tersedia\n";
                pauseProgram();
        }
    }while(pilih != 8);

    return 0;
}
