#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1024        // 最大输入长度

// 函数声明
void Menu();
void CaesarEncrypt(const char *plaintext, int key, char *ciphertext);
void CaesarDecrypt(const char *ciphertext, int key, char *plaintext);
void CaesarBruteForce(const char *ciphertext);
void VigenereEncrypt(const char *plaintext, const char *key, char *ciphertext);

void Pause();
void clearInputBuffer();
int  isValidShift(const char *str);

//////////////////////////////////////////////////////////////

int main() {
    while (1) {
        Menu();

        printf("请选择操作 (0-4): ");
        char choice[10];
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("输入错误！\n");
            Pause();
            continue;
        }
        // 移除换行符
        choice[strcspn(choice, "\n")] = '\0';

        if (strcmp(choice, "0")==0) {
            printf("程序退出。\n");
            break;
        }

        if (strlen(choice) != 1 || choice[0] < '1' || choice[0] > '4') {
            printf("无效选项，请重新选择。\n");
            Pause();
            continue;
        }

        switch (choice[0]) {
            case '1': { // 凯撒加密
                char plaintext[MAX_LEN], ciphertext[MAX_LEN];
                char keyStr[10];
                int key;

                printf("请输入明文（仅字母，其余字符保持原样）: ");
                if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
                    printf("输入错误！\n");
                    Pause();
                    break;
                }
                plaintext[strcspn(plaintext, "\n")] = '\0';

                printf("请输入移位密钥 (1-25): ");
                if (fgets(keyStr, sizeof(keyStr), stdin) == NULL || !isValidShift(keyStr)) {
                    printf("密钥无效！请输入1-25之间的整数。\n");
                    Pause();
                    break;
                }
                key = atoi(keyStr);
                CaesarEncrypt(plaintext, key, ciphertext);
                printf("密文: %s\n", ciphertext);
                Pause();
                break;
            }
            case '2': { // 凯撒解密
                char ciphertext[MAX_LEN], plaintext[MAX_LEN];
                char keyStr[10];
                int key;

                printf("请输入密文（仅字母，其余字符保持原样）: ");
                if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) {
                    printf("输入错误！\n");
                    Pause();
                    break;
                }
                ciphertext[strcspn(ciphertext, "\n")] = '\0';

                printf("请输入移位密钥 (1-25): ");
                if (fgets(keyStr, sizeof(keyStr), stdin) == NULL || !isValidShift(keyStr)) {
                    printf("密钥无效！请输入1-25之间的整数。\n");
                    Pause();
                    break;
                }
                key = atoi(keyStr);
                CaesarDecrypt(ciphertext, key, plaintext);
                printf("明文: %s\n", plaintext);
                Pause();
                break;
            }
            case '3': { // 凯撒穷举破译
                char ciphertext[MAX_LEN];
                printf("请输入密文（仅字母，其余字符保持原样）: ");
                if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) {
                    printf("输入错误！\n");
                    Pause();
                    break;
                }
                ciphertext[strcspn(ciphertext, "\n")] = '\0';

                printf("\n===== 开始穷举破译 (密钥1~25) =====\n");
                CaesarBruteForce(ciphertext);
                printf("=====================================\n");
                Pause();
                break;
            }
            case '4': { // 维吉尼亚加密
                char plaintext[MAX_LEN], key[MAX_LEN], ciphertext[MAX_LEN];

                printf("请输入明文（仅字母，其余字符保持原样）: ");
                if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
                    printf("输入错误！\n");
                    Pause();
                    break;
                }
                plaintext[strcspn(plaintext, "\n")] = '\0';

                printf("请输入密钥（仅字母）: ");
                if (fgets(key, sizeof(key), stdin) == NULL) {
                    printf("输入错误！\n");
                    Pause();
                    break;
                }
                key[strcspn(key, "\n")] = '\0';

                // 检查密钥是否包含非字母字符
                int valid = 1;
                for (int i = 0; key[i] != '\0'; i++) {
                    if (!isalpha((unsigned char)key[i])) {
                        valid = 0;
                        break;
                    }
                }
                if (!valid || strlen(key) == 0) {
                    printf("密钥必须只包含字母，且不能为空！\n");
                    Pause();
                    break;
                }

                VigenereEncrypt(plaintext, key, ciphertext);
                printf("密文: %s\n", ciphertext);
                Pause();
                break;
            }
            default:
                printf("无效选项。\n");
                Pause();
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////
// 菜单
void Menu() {
    system("cls");
    printf("============= 古典密码算法演示程序 =============\n");
    printf("===             ===  菜  单  ===             ===\n");
    printf("                0. 退出程序                    \n");
    printf("                1. 凯撒密码加密                \n");
    printf("                2. 凯撒密码解密                 \n");
    printf("                3. 凯撒密码穷举破译             \n");
    printf("                4. 维吉尼亚密码加密             \n");
    printf("================================================\n");
}

//////////////////////////////////////////////////////////////
// 暂停并清除缓冲区
void Pause() {
    printf("\n按回车键继续....");
    clearInputBuffer();
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

//////////////////////////////////////////////////////////////
// 验证移位密钥是否为 1-25 的有效整数
int isValidShift(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    // 去除可能的换行符
    char temp[10];
    strncpy(temp, str, sizeof(temp)-1);
    temp[sizeof(temp)-1] = '\0';
    temp[strcspn(temp, "\n")] = '\0';

    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] < '0' || temp[i] > '9') return 0;
    }
    int val = atoi(temp);
    return (val >= 1 && val <= 25);
}

//////////////////////////////////////////////////////////////
// 凯撒加密
void CaesarEncrypt(const char *plaintext, int key, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isupper((unsigned char)ch)) {
            ciphertext[i] = (char)((ch - 'A' + key) % 26 + 'A');
        } else if (islower((unsigned char)ch)) {
            ciphertext[i] = (char)((ch - 'a' + key) % 26 + 'a');
        } else {
            ciphertext[i] = ch; // 非字母保留
        }
    }
    ciphertext[i] = '\0';
}

//////////////////////////////////////////////////////////////
// 凯撒解密
void CaesarDecrypt(const char *ciphertext, int key, char *plaintext) {
    // 解密即用 26-key 的移位
    int decryptKey = 26 - (key % 26);
    CaesarEncrypt(ciphertext, decryptKey, plaintext);
}

//////////////////////////////////////////////////////////////
// 凯撒穷举破译
void CaesarBruteForce(const char *ciphertext) {
    for (int key = 1; key <= 25; key++) {
        char decrypted[MAX_LEN];
        CaesarDecrypt(ciphertext, key, decrypted);
        printf("密钥 %2d: %s\n", key, decrypted);
    }
}

//////////////////////////////////////////////////////////////
// 维吉尼亚加密
void VigenereEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen  = strlen(key);
    int j = 0; // 密钥索引

    for (int i = 0; i < textLen; i++) {
        char ch = plaintext[i];
        if (isalpha((unsigned char)ch)) {
            // 将密钥字符转换为移位量 (0~25)
            int shift = tolower((unsigned char)key[j % keyLen]) - 'a';
            if (isupper((unsigned char)ch)) {
                ciphertext[i] = (char)((ch - 'A' + shift) % 26 + 'A');
            } else {
                ciphertext[i] = (char)((ch - 'a' + shift) % 26 + 'a');
            }
            j++; // 只对字母字符消耗密钥
        } else {
            ciphertext[i] = ch; // 非字母保留
        }
    }
    ciphertext[textLen] = '\0';
}