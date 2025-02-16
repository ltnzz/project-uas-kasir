#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int ID;
    char namaBarang[200];
    float hargaBarang;
} Barang;

typedef struct {
    char namaBarang[200];
    float hargaBarang;
    int jumlah;
    float hargaTotalBarang;
} Transaksi;

int binarySearch(Barang arr[], int size, int ID) {
   int left = 0, right = size - 1;

   while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid].ID == ID )
        return mid;
    else if (arr[mid].ID < ID)
        left = mid + 1;
    else
        right = mid - 1;
   }
   return -1;
}

void simpanDataTransaksi(int transaksi, int count, Transaksi items[], float total, float diskon, float pajak, float totalKeseluruhan, float pembayaran, float kembalian) {
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    char filename[150];
    char timestamp[100];
    snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    snprintf(filename, sizeof(filename), "%04d-%02d-%02d %02d%02d%02d.txt", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    FILE *file = fopen(filename, "w");
    if ( file != NULL) {
        fprintf(file, "                Toko Akbar Cab. Benhil\n");
        fprintf(file, "             JL. In Aja Dulu Blok A No. 99\n\n");
        fprintf(file, "==========================================================\n");
        fprintf(file, "%s ", timestamp);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);
        fprintf(file, "No Struk #%04d%02d%02d%d\n", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, transaksi);
        fprintf(file, "                     Sales Receipt\n\n");
        for (int i = 0; i < count; i++) {
            fprintf(file,"%s\n%dx \t\t@%.2f\t\t\t\tRp %.2f\n", items[i].namaBarang, items[i].jumlah, items[i].hargaBarang, items[i].hargaTotalBarang);
        }
        fprintf(file, "---------------------------------------------------------\n");
        fprintf(file, "Subtotal:Rp %.2f\nDiskon:Rp %.2f\nPajak:Rp %.2f\nTotal bayar:Rp %.2f\nPembayaran:Rp %.2f\nKembalian:Rp %.2f", total, diskon, pajak, totalKeseluruhan, pembayaran, kembalian);

        fprintf(file, "\n---------------------------------------------------------\n");
        fprintf(file, "     Terima kasih telah berbelanja di Toko Akbar\n");
        fprintf(file, "      barang yang sudah dibeli atau sudah masuk\n");
        fprintf(file, "input kasir tidak dapat dikembalikan atau ditukar kembali\n");
        fprintf(file, "---------------------------------------------------------\n");
        fprintf(file, "                  Layanan Konsumen\n");
        fprintf(file, "                  Email   : tokoakbar99@gmail.com\n");
        fprintf(file, "                  Twitter : @tokoakbar99\n");
        fprintf(file, "                  Telepon : 0912897482372\n");
        fclose(file);
    } else {
        printf("              gagal membuka file untuk menyimpan data.\n");
        transaksi --;
    }
}

int main() {
    //data barang
    Barang barang[] = {
        {1, "Susu", 11875},
        {2, "Terigu", 12250},
        {3, "Telur", 36000},
        {4, "Minyak", 14500},
        {5, "Beras", 14125},
        {6, "Dji Samsoe", 21000},
        {7, "Gula Pasir", 16875},
        {8, "Indomie", 3000},
        {9, "Susu Kental Manis", 11875}
    };

    //variable
    char beli[] = "0", belii[] = "Done", exitp[] = "exit";
    float total, hargaTotalBarang, pembayaran, pajak, totalKeseluruhan = 0.0, diskon = 0.0;
    int ID, result, sum = 0, transaksi = 1, count;
    int size = sizeof(barang) / sizeof(barang[0]);
    
    //perulangan utama program
    while (true) {
        char beli[] = "0";
        sum = 0;
        total = 0.0;
        hargaTotalBarang = 0.0; 
        pembayaran = 0.0;
        pajak = 0.0;
        totalKeseluruhan = 0.0;
        pembayaran = 0.0;
        diskon = 0.0;
        count = 0;
        Transaksi items[200];
        printf("                Toko Akbar Cab. Benhil\n");
        printf("             JL. In Aja Dulu Blok A No. 99\n");
        printf("=======================================================\n");

        // waktu
        time_t now = time(NULL);
        struct tm *localTime = localtime(&now);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);
    
        printf("                  %s\n", timestamp);
        printf("\t\t     Transaksi ke-%d\n", transaksi);
        
        //sub perulangan
        do {
            printf("-------------------------------------------------------\n");
            printf("(Masukkan 'Done' jika ingin melakukan pembayaran,\natau 'exit' untuk keluar dari program.)\nSearch barang by id: ");
            fscanf(stdin, "%s", beli);

            if (strcmp(beli, exitp) == 0) {
                printf("\nProgram telah berhenti.\nTerima Kasih telah menggunakan program ini.\n");
                return 0;
            } else if (strcmp(beli, belii) == 0) {
                break;
            }
            
            sscanf(beli, "%d", &ID);
            result = binarySearch(barang, size, ID);
    
            if (result == -1) {
                printf("Data tidak ditemukan. Cari barang lagi!\n");
                }
            else {
                fflush(stdin);
                printf("Barang: %s\nHarga:Rp %.2f\n", barang[result].namaBarang, barang[result].hargaBarang);
                printf("Jumlah: ");
                fscanf(stdin, "%d", &sum);
                fflush(stdin);
                while (sum <= 0) {
                    printf("Jumlah beli tidak valid. Input jumlah kembali!\n");
                    printf("Jumlah: ", sum);
                    fscanf(stdin, "%d", &sum);
                    fflush(stdin);
                }
                    printf("%d x %.2f\n", sum, barang[result].hargaBarang);
                    hargaTotalBarang = sum * barang[result].hargaBarang;
                    printf("Harga Total perbarang:Rp %.2f\n", hargaTotalBarang);
                    total += hargaTotalBarang;
                    
                //copy string
                strcpy(items[count].namaBarang, barang[result].namaBarang);
                items[count].hargaBarang = barang[result].hargaBarang;
                items[count].jumlah = sum;
                items[count].hargaTotalBarang = hargaTotalBarang;
                count++;
            }
            ID = 0;
            sum = 0;
        } while (true);

        printf("-------------------------------------------------------\n");
        printf("Subtotal:Rp %.2f\n", total);
         if (total >= 99999) {
            diskon = total * 0.05;
            printf("Anda dapat diskon sebesar 5%%: Rp %.2f\n", diskon);
        }
        pajak = total * 0.12;
        printf("Pajak (12%%):Rp %.2f\n", pajak);
        totalKeseluruhan = (total + pajak) - diskon;
        printf("Total bayar:Rp %.2f", totalKeseluruhan);
        do {
        fflush(stdin);
        printf("\nPembayaran :Rp ");
        fscanf(stdin, "%f", &pembayaran);
        fflush(stdin);
            if (pembayaran < totalKeseluruhan) {
                printf("Uang tidak cukup atau tidak valid.");
            }
        } while (pembayaran < totalKeseluruhan);

        float kembalian = pembayaran - totalKeseluruhan;
        printf("Kembalian:Rp %.2f", kembalian);
        printf("\n-------------------------------------------------------\n");
        printf("     Terima kasih telah berbelanja di Toko Akbar\n");
        printf("      Barang yang sudah dibeli atau sudah masuk\n");
        printf("input kasir tidak dapat dikembalikan atau ditukar kembali\n");
        printf("-------------------------------------------------------\n");
        printf("                  Layanan Konsumen\n");
        printf("                  Email   : tokoakbar99@gmail.com\n");
        printf("                  Twitter : @tokoakbar99\n");
        printf("                  Telepon : 0912897482372\n");
        printf("-------------------------------------------------------\n\n\n");

        simpanDataTransaksi(transaksi++, count, items, total, diskon, pajak, totalKeseluruhan, pembayaran, kembalian);
    }
    return 0;
}