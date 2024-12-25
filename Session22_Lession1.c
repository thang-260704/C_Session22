#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char id[10];
    char name[50];
    int age;
} Student;

Student students[MAX];
int studentCount = 0;
void loadStudents(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(Student), studentCount, file);
        fclose(file);
    } else {
        studentCount = 0;
    }
}
void saveStudents(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(&studentCount, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}
void displayStudents() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien trong.\n");
        return;
    }
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %s, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}
void addStudent() {
    if (studentCount >= MAX) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    printf("Nhap ID: ");
    scanf("%s", students[studentCount].id);
    printf("Nhap Ten: ");
    scanf(" %[^\n]", students[studentCount].name);
    printf("Nhap Tuoi: ");
    scanf("%d", &students[studentCount].age);
    studentCount++;
    printf("Them sinh vien thanh cong.\n");
}
void editStudent() {
    char id[10];
    printf("Nhap ID sinh vien can sua: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("Nhap Ten moi: ");
            scanf(" %[^\n]", students[i].name);
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            printf("Sua thong tin thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID nay.\n");
}
void deleteStudent() {
    char id[10];
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Xoa sinh vien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID nay.\n");
}
void searchStudent() {
    char id[10];
    printf("Nhap ID sinh vien can tim: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("Tim thay: ID: %s, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID nay.\n");
}
void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (strcmp(students[i].id, students[j].id) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep.\n");
}
void menu() {
    const char *filename = "students.dat";
    loadStudents(filename);
    while (1) {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                saveStudents(filename);
                printf("Da luu du lieu va thoat chuong trinh.\n");
                return;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
