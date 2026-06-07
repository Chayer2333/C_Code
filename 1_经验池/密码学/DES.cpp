#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////////////////////////////////////////////////////////////
// DES 算法常量定义
//////////////////////////////////////////////////////////////

// 初始置换 IP (64位 -> 64位)
static const int IP_Table[64]={
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// 逆初始置换 IP^-1 (64位 -> 64位)
static const int IP_1_Table[64]={
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9,  49, 17, 57, 25
};

// 扩展置换 E (32位 -> 48位)
static const int E_Table[48]={
    32, 1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9,  10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// P 置换 (32位 -> 32位)
static const int P_Table[32]={
    16, 7,  20, 21, 29, 12, 28, 17,
    1,  15, 23, 26, 5,  18, 31, 10,
    2,  8,  24, 14, 32, 27, 3,  9,
    19, 13, 30, 6,  22, 11, 4,  25
};

// S盒 (8个S盒，每个6位输入 -> 4位输出)
static const int S_Box[8][4][16]={
    // S1
    {
        {14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7},
        {0,  15, 7,  4,  14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3,  8},
        {4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0},
        {15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6,  13}
    },
    // S2
    {
        {15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10},
        {3,  13, 4,  7,  15, 2,  8,  14, 12, 0,  1,  10, 6,  9,  11, 5},
        {0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15},
        {13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5,  14, 9}
    },
    // S3
    {
        {10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8},
        {13, 7,  0,  9,  3,  4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1},
        {13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7},
        {1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12}
    },
    // S4
    {
        {7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15},
        {13, 8,  11, 5,  6,  15, 0,  3,  4,  7,  2,  12, 1,  10, 14, 9},
        {10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4},
        {3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7,  2,  14}
    },
    // S5
    {
        {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9},
        {14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9,  8,  6},
        {4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14},
        {11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4,  5,  3}
    },
    // S6
    {
        {12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11},
        {10, 15, 4,  2,  7,  12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8},
        {9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6},
        {4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13}
    },
    // S7
    {
        {4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1},
        {13, 0,  11, 7,  4,  9,  1,  10, 14, 3,  5,  12, 2,  15, 8,  6},
        {1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2},
        {6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2,  3,  12}
    },
    // S8
    {
        {13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7},
        {1,  15, 13, 8,  10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2},
        {7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8},
        {2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11}
    }
};

// 密钥置换 PC-1 (64位 -> 56位，去掉8个校验位)
static const int PC_1_Table[56]={
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};

// 密钥压缩置换 PC-2 (56位 -> 48位)
static const int PC_2_Table[48]={
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// 左移位数表 (16轮)
static const int Shift_Table[16]={
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

//////////////////////////////////////////////////////////////
// 函数声明
//////////////////////////////////////////////////////////////

void Menu();
void Pause();
void clearInputBuffer();

// 位操作辅助函数
void CharToBits(const unsigned char *input, int *bits, int len);
void BitsToChar(const int *bits, unsigned char *output, int len);
void Permute(const int *input, int *output, const int *table, int n);
void LeftShift(int *bits, int shifts, int len);
void XOR(const int *a, const int *b, int *result, int len);

// DES核心函数
void GenerateSubKeys(const int *keyBits, int subKeys[16][48]);
void Feistel(const int *R, const int *subKey, int *output);
void DESEncryptBlock(const int *plainBits, const int *keyBits, int *cipherBits);
void DESDecryptBlock(const int *cipherBits, const int *keyBits, int *plainBits);

// 字符串处理
void StringToKeyBits(const char *keyStr, int *keyBits);
void PrintHex(const unsigned char *data, int len);
void ReadHexString(const char *hexStr, unsigned char *output, int *outLen);

//////////////////////////////////////////////////////////////

int main() {
    while (1) {
        Menu();

        printf("请选择操作 (0-3): ");
        char choice[10];
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("输入错误\n");
            Pause();
            continue;
        }
        choice[strcspn(choice, "\n")]='\0';

        if (strcmp(choice, "0") == 0) {
            printf("程序已退出\n");
            break;
        }

        if (strlen(choice) != 1 || choice[0]<'1' || choice[0]>'3') {
            printf("无效选项，请重新选择\n");
            Pause();
            continue;
        }

        switch (choice[0]) {
            case '1': { // DES加密
                char keyStr[20], plainStr[100];
                unsigned char plaintext[8];
                int keyBits[64], plainBits[64], cipherBits[64];
                unsigned char ciphertext[8];

                printf("请输入8字节密钥 (如: 12345678): ");
                if (fgets(keyStr, sizeof(keyStr), stdin) == NULL) {
                    printf("输入错误\n");
                    Pause();
                    break;
                }
                keyStr[strcspn(keyStr, "\n")]='\0';

                printf("请输入明文 (最多8字节，不足补空格): ");
                if (fgets(plainStr, sizeof(plainStr), stdin) == NULL) {
                    printf("输入错误\n");
                    Pause();
                    break;
                }
                plainStr[strcspn(plainStr, "\n")]='\0';

                // 填充明文到8字节
                int len=strlen(plainStr);
                if (len>8) len=8;
                memcpy(plaintext, plainStr, len);
                for (int i=len; i<8; i++) plaintext[i]=' ';

                StringToKeyBits(keyStr, keyBits);
                CharToBits(plaintext, plainBits, 8);
                DESEncryptBlock(plainBits, keyBits, cipherBits);
                BitsToChar(cipherBits, ciphertext, 8);

                printf("密文 (Hex): ");
                PrintHex(ciphertext, 8);
                printf("\n");
                Pause();
                break;
            }
            case '2': { // DES解密
                char keyStr[20], hexStr[50];
                unsigned char ciphertext[8];
                int keyBits[64], cipherBits[64], plainBits[64];
                unsigned char plaintext[9];
                int cipherLen;

                printf("请输入8字节密钥 (如: 12345678): ");
                if (fgets(keyStr, sizeof(keyStr), stdin) == NULL) {
                    printf("输入错误\n");
                    Pause();
                    break;
                }
                keyStr[strcspn(keyStr, "\n")]='\0';

                printf("请输入密文 (16进制，16个字符): ");
                if (fgets(hexStr, sizeof(hexStr), stdin) == NULL) {
                    printf("输入错误\n");
                    Pause();
                    break;
                }
                hexStr[strcspn(hexStr, "\n")]='\0';

                ReadHexString(hexStr, ciphertext, &cipherLen);
                if (cipherLen != 8) {
                    printf("密文长度错误，应为16个十六进制字符(8字节)\n");
                    Pause();
                    break;
                }

                StringToKeyBits(keyStr, keyBits);
                CharToBits(ciphertext, cipherBits, 8);
                DESDecryptBlock(cipherBits, keyBits, plainBits);
                BitsToChar(plainBits, plaintext, 8);
                plaintext[8]='\0';

                printf("解密结果: %s\n", plaintext);
                Pause();
                break;
            }
            case '3': { // 测试向量验证
                printf("\n===== DES标准测试向量验证 =====\n");
                
                // 测试向量1: 全0密钥，全0明文
                int keyBits1[64]={0};
                int plainBits1[64]={0};
                int cipherBits1[64];
                unsigned char result1[8];
                
                DESEncryptBlock(plainBits1, keyBits1, cipherBits1);
                BitsToChar(cipherBits1, result1, 8);
                printf("测试1-密钥: 0000000000000000, 明文: 0000000000000000\n");
                printf("标准密文: 8CA64DE9C1B123A7\n");
                printf("计算密文: ");
                PrintHex(result1, 8);
                printf("\n\n");

                // 测试向量2
                unsigned char key2[8]={0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
                unsigned char plain2[8]={0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
                int keyBits2[64], plainBits2[64], cipherBits2[64];
                unsigned char result2[8];
                
                CharToBits(key2, keyBits2, 8);
                CharToBits(plain2, plainBits2, 8);
                DESEncryptBlock(plainBits2, keyBits2, cipherBits2);
                BitsToChar(cipherBits2, result2, 8);
                printf("测试2-密钥: 0123456789ABCDEF, 明文: 0123456789ABCDEF\n");
                printf("标准密文: 85E813540F0AB405\n");
                printf("计算密文: ");
                PrintHex(result2, 8);
                printf("\n");

                printf("=================================\n");
                Pause();
                break;
            }
            default:
                printf("无效选项\n");
                Pause();
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////
// 菜单
//////////////////////////////////////////////////////////////
void Menu() {
    system("cls");
    printf("=========== DES数据加密标准算法演示 ============\n");
    printf("===             ===  菜  单  ===             ===\n");
    printf("                0. 退出程序                    \n");
    printf("                1. DES加密                    \n");
    printf("                2. DES解密                     \n");
    printf("                3. 标准测试向量验证             \n");
    printf("================================================\n");
}

//////////////////////////////////////////////////////////////
// 暂停与清缓冲区
//////////////////////////////////////////////////////////////
void Pause() {
    printf("\n按回车键继续....");
    clearInputBuffer();
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

//////////////////////////////////////////////////////////////
// 位操作辅助函数
//////////////////////////////////////////////////////////////

// 将字节数组转换为位数组 (MSB在前)
void CharToBits(const unsigned char *input, int *bits, int len) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<8; j++) {
            bits[i*8+j]=(input[i] >> (7-j)) & 1;
        }
    }
}

// 将位数组转换为字节数组
void BitsToChar(const int *bits, unsigned char *output, int len) {
    for (int i=0; i<len; i++) {
        output[i]=0;
        for (int j=0; j<8; j++) {
            output[i]=(output[i] << 1) | bits[i*8+j];
        }
    }
}

// 置换操作 (根据置换表对输入位进行重排)
void Permute(const int *input, int *output, const int *table, int n) {
    for (int i=0; i<n; i++) {
        output[i]=input[table[i]-1];  // 表中索引从1开始
    }
}

// 循环左移
void LeftShift(int *bits, int shifts, int len) {
    int temp[28];
    for (int i=0; i<len; i++) {
        temp[i]=bits[(i+shifts) % len];
    }
    for (int i=0; i<len; i++) {
        bits[i]=temp[i];
    }
}

// 异或操作
void XOR(const int *a, const int *b, int *result, int len) {
    for (int i=0; i<len; i++) {
        result[i]=a[i] ^ b[i];
    }
}

//////////////////////////////////////////////////////////////
// DES核心函数
//////////////////////////////////////////////////////////////

// 生成16个子密钥
void GenerateSubKeys(const int *keyBits, int subKeys[16][48]) {
    int permutedKey[56];
    int left[28], right[28];
    int combined[56];

    // PC-1置换 (64位 -> 56位)
    Permute(keyBits, permutedKey, PC_1_Table, 56);

    // 分成左右两部分
    for (int i=0; i<28; i++) {
        left[i]=permutedKey[i];
        right[i]=permutedKey[i+28];
    }

    // 生成16个子密钥
    for (int round=0; round<16; round++) {
        // 左右两部分分别循环左移
        LeftShift(left, Shift_Table[round], 28);
        LeftShift(right, Shift_Table[round], 28);

        // 合并
        for (int i=0; i<28; i++) {
            combined[i]=left[i];
            combined[i+28]=right[i];
        }

        // PC-2置换 (56位 -> 48位)
        Permute(combined, subKeys[round], PC_2_Table, 48);
    }
}

// Feistel轮函数 (F函数)
void Feistel(const int *R, const int *subKey, int *output) {
    int expanded[48];
    int xored[48];
    int sBoxOutput[32];

    // 扩展置换 E (32位 -> 48位)
    Permute(R, expanded, E_Table, 48);

    // 与子密钥异或
    XOR(expanded, subKey, xored, 48);

    // S盒替换 (48位 -> 32位)
    for (int i=0; i<8; i++) {
        // 每个S盒6位输入
        int row=xored[i*6]*2+xored[i*6+5];  // 首尾两位
        int col=xored[i*6+1]*8+xored[i*6+2]*4 +
                  xored[i*6+3]*2+xored[i*6+4];  // 中间四位

        int val=S_Box[i][row][col];
        // 转换为4位二进制
        for (int j=0; j<4; j++) {
            sBoxOutput[i*4+3-j]=(val >> j) & 1;
        }
    }

    // P置换 (32位 -> 32位)
    Permute(sBoxOutput, output, P_Table, 32);
}

// DES加密单个数据块 (64位)
void DESEncryptBlock(const int *plainBits, const int *keyBits, int *cipherBits) {
    int subKeys[16][48];
    int permuted[64];
    int left[32], right[32];
    int temp[32];
    int preOutput[64];

    // 生成子密钥
    GenerateSubKeys(keyBits, subKeys);

    // 初始置换 IP
    Permute(plainBits, permuted, IP_Table, 64);

    // 分成左右两部分
    for (int i=0; i<32; i++) {
        left[i]=permuted[i];
        right[i]=permuted[i+32];
    }

    // 16轮Feistel网络
    for (int round=0; round<16; round++) {
        // L(i)=R(i-1)
        for (int i=0; i<32; i++) {
            temp[i]=left[i];
        }

        // R(i)=L(i-1) XOR F(R(i-1), K(i))
        int fOutput[32];
        Feistel(right, subKeys[round], fOutput);
        XOR(left, fOutput, left, 32);

        // 交换
        for (int i=0; i<32; i++) {
            left[i]=right[i];
            right[i]=temp[i];
        }
    }

    // 最后一轮不进行交换，所以这里需要再交换回来
    // 实际上上面的循环已经做了16次交换，第16轮不应该交换
    // 但按照标准实现，我们在第16轮后需要把左右互换回来
    for (int i=0; i<32; i++) {
        temp[i]=left[i];
        left[i]=right[i];
        right[i]=temp[i];
    }

    // 合并左右两部分
    for (int i=0; i<32; i++) {
        preOutput[i]=left[i];
        preOutput[i+32]=right[i];
    }

    // 逆初始置换 IP^-1
    Permute(preOutput, cipherBits, IP_1_Table, 64);
}

// DES解密单个数据块 (64位)
void DESDecryptBlock(const int *cipherBits, const int *keyBits, int *plainBits) {
    int subKeys[16][48];
    int subKeysRev[16][48];
    int permuted[64];
    int left[32], right[32];
    int temp[32];
    int preOutput[64];

    // 生成子密钥
    GenerateSubKeys(keyBits, subKeys);

    // 反转子密钥顺序 (解密使用逆序子密钥)
    for (int i=0; i<16; i++) {
        for (int j=0; j<48; j++) {
            subKeysRev[i][j]=subKeys[15-i][j];
        }
    }

    // 初始置换 IP
    Permute(cipherBits, permuted, IP_Table, 64);

    // 分成左右两部分
    for (int i=0; i<32; i++) {
        left[i]=permuted[i];
        right[i]=permuted[i+32];
    }

    // 16轮Feistel网络 (使用逆序子密钥)
    for (int round=0; round<16; round++) {
        for (int i=0; i<32; i++) {
            temp[i]=left[i];
        }

        int fOutput[32];
        Feistel(right, subKeysRev[round], fOutput);
        XOR(left, fOutput, left, 32);

        for (int i=0; i<32; i++) {
            left[i]=right[i];
            right[i]=temp[i];
        }
    }

    // 最后交换回来
    for (int i=0; i<32; i++) {
        temp[i]=left[i];
        left[i]=right[i];
        right[i]=temp[i];
    }

    // 合并
    for (int i=0; i<32; i++) {
        preOutput[i]=left[i];
        preOutput[i+32]=right[i];
    }

    // 逆初始置换 IP^-1
    Permute(preOutput, plainBits, IP_1_Table, 64);
}

//////////////////////////////////////////////////////////////
// 字符串处理辅助函数
//////////////////////////////////////////////////////////////

// 将字符串密钥转换为64位密钥位数组 (不足8字节补空格)
void StringToKeyBits(const char *keyStr, int *keyBits) {
    unsigned char keyBytes[8];
    int len=strlen(keyStr);
    if (len>8) len=8;
    memcpy(keyBytes, keyStr, len);
    for (int i=len; i<8; i++) keyBytes[i]=' ';
    CharToBits(keyBytes, keyBits, 8);
}

// 以十六进制格式打印数据
void PrintHex(const unsigned char *data, int len) {
    for (int i=0; i<len; i++) {
        printf("%02X", data[i]);
    }
}

// 读取十六进制字符串并转换为字节数组
void ReadHexString(const char *hexStr, unsigned char *output, int *outLen) {
    int len=strlen(hexStr);
    *outLen=0;
    for (int i=0; i<len; i += 2) {
        if (i+1 >= len) break;
        char hexByte[3]={hexStr[i], hexStr[i+1], '\0'};
        output[(*outLen)++]=(unsigned char)strtol(hexByte, NULL, 16);
    }
}
