#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
void loadAccounts(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(&accountCount, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    } else {
        accountCount = 0;
    }
}
void saveAccounts(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}
int isUsernameExists(const char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}
void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Danh sach tai khoan da day\n");
        return;
    }

    char username[50], password[50], confirmPassword[50];
    printf("Nhap tai khoan: ");
    scanf("%s", username);

    if (isUsernameExists(username)) {
        printf("Tai khoan da ton tai. Vui long nhap lai\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", password);
    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Vui long thu lai\n");
        return;
    }

    strcpy(accounts[accountCount].username, username);
    strcpy(accounts[accountCount].password, password);
    accountCount++;

    printf("Dang ky thanh cong\n");
}
void login() {
    char username[50], password[50];
    printf("Nhap tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong\n");
            return;
        }
    }
    printf("Dang nhap that bai. Tai khoan hoac mat khau khong dung\n");
}
void menu() {
    const char *filename = "accounts.dat";
    loadAccounts(filename);

    while (1) {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                saveAccounts(filename);
                printf("Da luu du lieu va thoat chuong trinh\n");
                return;
            default:
                printf("Lua chon khong hop le. Vui long chon lai\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
