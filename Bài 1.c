
#include <stdio.h>

#define MAX_SHELF_WEIGHT 500.0

// C?u trúc bi?u di?n thông tin ki?n hàng Pallet
typedef struct {
    int pallet_id;
    float weight_kg;
    float temp_celsius;
} PalletItem;

// C?u trúc bi?u di?n ô k? kho
typedef struct {
    int shelf_id;
    int is_cold_storage; // 1: Kho l?nh, 0: Kho thý?ng
    float current_weight_kg;
} WarehouseShelf;

// Hàm ki?m ð?nh an toàn trý?c khi nh?p ki?n hàng vào ô k?
// Tr? v? 1 n?u h?p l?, tr? v? 0 n?u vi ph?m
int kiem_tra_an_toan_nhap_kho(WarehouseShelf shelf, PalletItem item) {

    // 1. Ki?m tra nhi?t ð? b?o qu?n ð?i v?i k? kho l?nh
    if (shelf.is_cold_storage == 1) {
        if (item.temp_celsius < -18.0 ||
            item.temp_celsius > 5.0) {

            printf("[LOI KHO LANH] Nhiet do %.1f C "
                   "khong dat chuan (-18 C den 5 C)!\n",
                   item.temp_celsius);

            return 0;
        }
    }

    // 2. Ki?m tra t?ng t?i tr?ng c?a k? sau khi nh?p hàng
    if (shelf.current_weight_kg + item.weight_kg
        > MAX_SHELF_WEIGHT) {

        printf("[LOI QUA TAI] Tong tai trong %.1f kg "
               "vuot gioi han %.1f kg!\n",
               shelf.current_weight_kg + item.weight_kg,
               MAX_SHELF_WEIGHT);

        return 0;
    }

    // C? hai ði?u ki?n ð?u h?p l?
    return 1;
}

int main() {
    // K? 101 ðang ch?a 400 kg hàng trong kho l?nh
    WarehouseShelf ke_lanh_101 = {101, 1, 400.0};

    // Pallet m?i n?ng 150 kg, nhi?t ð? b?o qu?n 12 C
    PalletItem pallet_moi = {5001, 150.0, 12.0};

    printf("=== HE THONG GIAM SAT AN TOAN NHAP KHO ===\n");

    printf("Thong tin ke %d: Tai trong hien tai = %.1f kg"
           " | Loai kho = %s\n",
           ke_lanh_101.shelf_id,
           ke_lanh_101.current_weight_kg,
           ke_lanh_101.is_cold_storage
               ? "Kho Lanh" : "Kho Thuong");

    printf("Kien hang: Ma = %d | Nang = %.1f kg"
           " | Nhiet do = %.1f C\n",
           pallet_moi.pallet_id,
           pallet_moi.weight_kg,
           pallet_moi.temp_celsius);

    printf("--------------------------------------------\n");

    int ket_qua = kiem_tra_an_toan_nhap_kho(
        ke_lanh_101, pallet_moi
    );

    if (ket_qua == 1) {
        printf("KET QUA: [DUYET] Du dieu kien nhap kho!\n");
    } else {
        printf("KET QUA: [TU CHOI] Vi pham quy dinh an toan!\n");
    }

    return 0;
}

