#include <iostream>
using namespace std;

//dengan Bubble sort secara ascending
void bubbleSort(string nama[], int n){
		for(int i = 0; i < n - 1; i++) //perulangan untuk sorting
		{
				for(int j = 0; j < n - 1; j++) //membandingkan data
				{
						if(nama[j] > nama[j + 1]) //jika data lebih besar
						{
								string temp = nama[j + 1]; //simpan sementara
								nama[j + 1] = nama[j]; //menukar posisi
								nama[j] = temp;
							}
					}
			}
}

//dengan Quick sort secara descending
void quick_sort(string nama[], int awal, int akhir) {
    int low = awal, high = akhir; //posisi awal & akhir
    string pivot = nama[(awal + akhir) / 2]; //menetukan pivot
    
    //perulangan sorting
    do {
        while (nama[low] > pivot) //mencari dari kiri
            low++;
        while (nama[high] < pivot) //mencari dari kanan
            high--;

        if (low <= high) {
            swap(nama[low], nama[high]); //menukar data
            low++; //menggeser posisi pointer
            high--; //menggeser posisi pointer
	}
	  } while (low <= high); //diulang selama kondisi terpenuhi

    if (awal < high) //rekursi bagian kiri
        quick_sort(nama, awal, high);

    if (low < akhir) //rekursi bagian kanan
        quick_sort(nama, low, akhir);
}

int main(){
	//deklarasi
	int n, pilihan;
	
	//user input banyaknya mahasiswa
	cout << "Banyaknya Mahasiswa: ";
	cin >> n; 
	cin.ignore();
	
	string nama[n]; //array untuk menyimpan nama
	
	//user memasukan nama mahasiswa
	cout << "\nMasukkan nama Mahasiswa\n ";
	for(int i = 0; i < n; i ++){
			cout << "	Nama ke-" << i + 1 << ": ";
			getline(cin, nama[i]); //input nama
		}
		
	//menampilkan data sebelum diurutkan
	cout << "\nData sebelumnya: \n";
	for(int i = 0; i < n; i++){
			cout << nama[i] << endl; //menampilkan data awal
		}
		
	//menu pilihan
	cout << "\n=== Menu Pilihan ===\n";
	cout << "1. Bubble Sort dengan Ascending\n";
	cout << "2. Quick Sort dengan Descending\n";
	cout << "Pilihan: ";
	cin >> pilihan; //input pilihan
	
	if(pilihan == 1){
		bubbleSort(nama, n); //menjalankan Bubble Sort
		cout << "\nUrutan data setelah Bubble sort: \n";
		} else if(pilihan == 2){
				quick_sort(nama, 0, n - 1); //menjalankan Quick Sort
				cout << "\nUrutan data setelah Quick sort: \n";
			} else {
					cout << "Pilihan tidak ada!!"; //jika pilihan salah
					return 0;
				}
	
	//hasil setelah disorting
	for(int i = 0; i < n; i++){
			cout << nama[i] << endl;
		}
	
	
	return 0;

}
