#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct Produk{
	char nama[60];
	char kategori[30];
	double harga;
	int stok;
	float rating;
};

Produk katalog[100];
int n = 0;

void cekFile(){
	FILE *pointer = fopen("shopease_db.txt", "r");
	if(pointer == NULL){
		cout << "File Tidak Ditemukan!\n";
		} else {
			while(fscanf(pointer," %[^|]|%[^|]|%lf|%d|%f\n",
			katalog[n].nama,
			katalog[n].kategori,
			&katalog[n].harga,
			&katalog[n].stok,
			&katalog[n].rating) != EOF){
			n++;
				}
			}
	fclose(pointer);
}

void simpanFile(){
	FILE *pointer = fopen("shopease_db.txt", "w");
	
	for(int i = 0; i < n; i++){
		fprintf(pointer,"%s|%s|%lf|%d|%.1f\n",
		katalog[i].nama,
		katalog[i].kategori,
		katalog[i].harga,
		katalog[i].stok,
		katalog[i].rating);
	}
	fclose(pointer);
}

void addProduk(){
	
	char lagi;
	
	do{
	cout << "Nama Produk: ";
	cin.ignore();
	cin.getline(katalog[n].nama, 50);
	cout << "kategori   : ";
	cin.getline(katalog[n].kategori, 50);
	cout << "Harga      : ";
	cin >> katalog[n].harga;
	cout << "Stok       : ";
	cin >> katalog[n].stok;
	cout << "Rating     : ";
	cin >> katalog[n].rating;
	n++;
	
	cout << "\nTambah Produk Lagi(y/n)?";
	cin >> lagi;
	cin.ignore();
	
	} while (lagi == 'y' || lagi == 'Y');
	simpanFile();
	
	cout << "Selamat! Produk Berhasil Ditambahkan.\n";
}

void bubbleSort(Produk array[], int n){
		for(int i = 0; i < n - 1; i++){
				for(int j = 0; j < n -  1; j++){
						if(array[j].nama[0] > array[j + 1].nama[0]){
								Produk temp = array[j];
								array[j] = array[j + 1];
								array[j + 1] = temp;
							}
					}
			}
}

void quick_sort(Produk array[], int awal, int akhir) {

    int low = awal, high = akhir;
    float pivot = array[(awal + akhir) / 2].rating;

    do {
        while (array[low].rating > pivot)
            low++;
        while (array[high].rating < pivot)
            high--;

        if (low <= high) {
            swap(array[low], array[high]);
            low++;
            high--;
	}

    } while (low <= high);

    if (awal < high)
        quick_sort(array, awal, high);

    if (low < akhir)
        quick_sort(array, low, akhir);
}

void tampilProduk(){
		
	int pilihan;
		
	cout << "1. Berdasarkan Nama produk(Bubble Sort)\n";
	cout << "2. Berdasarkan Rating Produk(Quick Sort)\n";
	cout << "Pilih: ";
	cin >> pilihan;
	
	if(pilihan == 1){
		bubbleSort(katalog, n);
	} else if(pilihan == 2){
		quick_sort(katalog, 0, n-1);
	} else {
		cout << "Pilihan Tidak Tersedia!\n";
		return;
	}
	
	cout << "\n=== Daftar Produk ===\n";
	cout << "=====================================\n";
	
	for(int i = 0;i < n; i++){
		cout << "Nama    : " << katalog[i].nama << endl;
		cout << "Kategori: " << katalog[i].kategori << endl;
		cout << "Harga   : " << katalog[i].harga << endl;
		cout << "Stok    : " << katalog[i].stok << endl;
		cout << "Rating  : " << katalog[i].rating << endl;
		cout << "=====================================\n";
	}
}

void cariFile(){
	char cari[50];
		
	cout << "Masukkan Nama: ";
	cin.ignore();
	cin.getline(cari, 50);
	
	for(int i = 0; i < n; i++){
		int j;
		
		for(j = 0; cari[j] != '\0' && katalog[i].nama[j] != '\0'; j++){
			if(cari[j] != katalog[i].nama[j]){
				break;
			}
		}
		
		if(cari[j] == katalog[i].nama[j]){
			cout << "\nProduk tersedia\n";
			cout << "Nama    : " << katalog[i].nama << endl;
			cout << "Kategori: " << katalog[i].kategori << endl;
			cout << "Harga   : " << katalog[i].harga << endl;
			cout << "Stok    : " << katalog[i].stok << endl;
			cout << "Rating  : " << katalog[i].rating << endl;
			return; 
		}
	}
	cout << "Produk Tidak Ditemukan!\n";
}

int main(){
	cekFile();
	
	int pilih;
	
	do{
		cout << "\n=== Shopease ===\n";
		cout << "\n1. ADD Product";
		cout << "\n2. Show Product";
		cout << "\n3. Search Product";
		cout << "\n4. Keluar\n";
		cout << "Pilih: ";
		cin >> pilih;
		
		switch(pilih){
			case 1:
			addProduk();
			break;
			
			case 2:
			tampilProduk();
			break;
			
			case 3:
			cariFile();
			break;
			
			case 4:
			cout << "Terima kasih telah menggunakan program ini!" << endl;
			cout << "Semoga hari Anda menyenangkan. Sampai jumpa!" << endl;
			break;
			
			default:
			cout << "Menu Tidak Ada!\n";
		}
	}while (pilih != 4);
	
	return 0;
}
