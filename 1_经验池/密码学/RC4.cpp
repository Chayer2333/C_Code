// RC4_实验.cpp —— RC4 流密码加解密实验
// RC4 流密码由 Ron Rivest 于1987年设计，核心思想：用一个密钥调度算法(KSA)打乱S盒，
// 再用伪随机生成算法(PRGA)产生密钥流，最后将密钥流与明文/密文逐字节异或。
// 由于异或操作的对称性，加密与解密使用完全相同的算法。
#include <stdio.h>
#include <cstdlib> 			// system(), rand(), srand()
#include <ctime>    			// time()
#include <stdlib.h> 			// malloc, free
#include <iostream>  			// cin, cout
#include <stdbool.h> 		// bool
#include <string.h>  			// strlen, strcpy, strcspn, memcpy
#include <stdint.h>   			// uint8_t
#include <fstream>    			// ofstream, ifstream
#include <direct.h>   			// _mkdir (Windows)

#define MAX_LEN      2048		// 最大数据处理长度
#define MAX_KEY_LEN   256		// RC4 密钥最大长度（标准为1~256字节）

using namespace std;

// ================== 函数声明 ==================
// --- 通用工具 ---
void Menu();
void Pause();
void clearInputBuffer();
 int input(char c);

// --- RC4 核心算法（两大功能模块）---
void RC4_KSA(unsigned char *S, const unsigned char *key, int keylen);			// ① 密钥调度算法 (KSA)
void RC4_PRGA(unsigned char *S, unsigned char *keystream, int datalen);		// ② 伪随机生成算法 (PRGA)
void RC4_Crypt(const unsigned char *input, unsigned char *output, int len,
               const unsigned char *key, int keylen);						// RC4 加解密（KSA+PRGA+异或）

// --- 十六进制转换 ---
void bytesToHex(const unsigned char *b, int n, char *h);
 int hexToBytes(const char *h, unsigned char *b, int maxLen);

// --- 密钥文件操作 ---
bool saveKeyToFile(const char *key);
bool loadKeyFromFile(char *key, int maxLen);

// --- 密文文件操作 ---
bool saveCipherToFile(const char *hexCipher);
bool loadCipherFromFile(char *hexCipher, int maxLen);

// --- 辅助打印 ---
void printSBox(const unsigned char *S, const char *title);

// --- 交互子系统 ---
void encryptMenu(char *g_key);			// 加密菜单
void decryptMenu(char *g_key);			// 解密菜单
void selfVerify();						// 自验证
void keyManageMenu(char *g_key);		// 密钥管理子系统
void cipherFileMenu(char *g_key);		// 密文文件子系统

// ================== 主程序 ==================
int main()
{
	int choice=0;
	char c='N';
	static char g_key[MAX_KEY_LEN+1]={0};	// 当前会话密钥

	srand((unsigned)time(NULL));			// 随机种子（自验证用）

	// 确保 data 目录存在
	_mkdir("data");

	do
	{
		choice=0; c='N';
		Menu();
		cin>>(c);
		choice=input(c);
		clearInputBuffer();

		switch(choice)
		{
			case 0: {			// ** 退出指令 **
				cout<<"\nRC4 实验程序已退出。\n";
				break;
			}

			case 1: {			// ** RC4 加密 **
				encryptMenu(g_key);
				break;
			}

			case 2: {			// ** RC4 解密 **
				decryptMenu(g_key);
				break;
			}

			case 3: {			// ** 自验证 **
				selfVerify();
				break;
			}

			case 4: {			// ** 密钥管理 **
				keyManageMenu(g_key);
				break;
			}

			case 5: {			// ** 密文文件操作 **
				cipherFileMenu(g_key);
				break;
			}

			default: cout<<"\n---- 输入错误! ----\n";
		}
	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
	} while(choice);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void Menu()
{
	system("cls");
	cout<<"===========  RC4 流密码算法演示程序  ===========\n";
	cout<<"------------------------------------------------\n";
	cout<<"              1. RC4 加密                       \n";
	cout<<"              2. RC4 解密                       \n";
	cout<<"              3. 自验证（加解密一致性测试）     \n";
	cout<<"------------------------------------------------\n";
	cout<<"              4. 密钥管理                       \n";
	cout<<"              5. 密文文件操作                   \n";
	cout<<"------------------------------------------------\n";
	cout<<"              0. 退出程序                       \n";
	cout<<"================================================\n";
	cout<<"请选择：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 暂停与清除缓冲区 **

void Pause()
{
	printf("\n按回车键继续....");
	clearInputBuffer();
}

void clearInputBuffer()
{
	while(getchar()!='\n');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** sys选择验证 **

int input(char c)
{
	if('0'<=c && '9'>=c)
		return c-'0';
	else
		return -1;
}

// ==================== ① 密钥调度算法 (KSA) ====================
// 原理：先将S盒初始化为0~255的线性排列，
// 然后用密钥逐字节打乱S盒，使S盒成为密钥相关的伪随机排列。
// 参数：S —— 256字节S盒（输出）；key —— 密钥字节数组；keylen —— 密钥长度(1~256)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RC4_KSA(unsigned char *S, const unsigned char *key, int keylen)
{
	int i, j=0;
	unsigned char tmp;

	// 步骤1：初始化S盒为 0,1,2,...,255
	for(i=0; i<256; i++)
		S[i]=(unsigned char)i;

	// 步骤2：用密钥打乱S盒
	for(i=0; i<256; i++)
	{
		j=(j + S[i] + key[i % keylen]) % 256;
		// 交换 S[i] 与 S[j]
		tmp=S[i];
		S[i]=S[j];
		S[j]=tmp;
	}
}

// ==================== ② 伪随机生成算法 (PRGA) ====================
// 原理：KSA完成后，S盒已呈伪随机状态。
// PRGA 持续搅动S盒并从中取出一个字节作为密钥流字节，
// 每产生一个密钥流字节，S盒就多搅动一次，
// 使得产生的密钥流在统计上接近真随机。
// 参数：S —— 已完成KSA的S盒（会被继续修改）；
//       keystream —— 存放生成的密钥流（长度 = datalen）
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RC4_PRGA(unsigned char *S, unsigned char *keystream, int datalen)
{
	int i=0, j=0, k;
	unsigned char tmp;

	for(k=0; k<datalen; k++)
	{
		i=(i + 1) % 256;
		j=(j + S[i]) % 256;

		// 交换 S[i] 与 S[j]
		tmp=S[i];
		S[i]=S[j];
		S[j]=tmp;

		// 取 S[(S[i]+S[j]) % 256] 作为密钥流字节
		keystream[k]=S[(S[i]+S[j]) % 256];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** RC4 加解密（KSA + PRGA + 异或）**
// 加密：ciphertext = plaintext XOR keystream
// 解密：plaintext = ciphertext XOR keystream
// 两者共用同一函数，因为 (A XOR K) XOR K = A
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RC4_Crypt(const unsigned char *input, unsigned char *output, int len,
               const unsigned char *key, int keylen)
{
	unsigned char S[256];
	unsigned char *keystream;

	keystream=(unsigned char *)malloc(len);
	if(!keystream) return;

	// ① KSA：用密钥初始化S盒
	RC4_KSA(S, key, keylen);

	// ② PRGA：生成与数据等长的密钥流
	RC4_PRGA(S, keystream, len);

	// ③ 异或：逐字节加密/解密
	for(int i=0; i<len; i++)
		output[i]=input[i] ^ keystream[i];

	free(keystream);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 二进制转十六进制字符串 **

void bytesToHex(const unsigned char *b, int n, char *h)
{
	for(int i=0; i<n; i++)
		sprintf(h+i*2, "%02x", b[i]);
	h[n*2]='\0';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 十六进制字符串转二进制 **
// 返回转换后的字节数，失败返回 -1

int hexToBytes(const char *h, unsigned char *b, int maxLen)
{
	int len=(int)strlen(h);
	if(len % 2 != 0) return -1;
	int blen=len/2;
	if(blen > maxLen) return -1;
	for(int i=0; i<blen; i++)
	{
		unsigned int v;
		if(sscanf(h+i*2, "%2x", &v) != 1) return -1;
		b[i]=(unsigned char)v;
	}
	return blen;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 保存密钥到文件 **

bool saveKeyToFile(const char *key)
{
	ofstream ofs("data/rc4_key.txt");
	if(!ofs.is_open())
	{
		printf("无法打开 data/rc4_key.txt 进行写入！\n");
		return false;
	}
	ofs << key;
	ofs.close();
	printf("密钥已保存到 data/rc4_key.txt\n");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 从文件加载密钥 **

bool loadKeyFromFile(char *key, int maxLen)
{
	ifstream ifs("data/rc4_key.txt");
	if(!ifs.is_open())
	{
		printf("无法打开 data/rc4_key.txt！请先保存密钥。\n");
		return false;
	}
	ifs.getline(key, maxLen);
	ifs.close();
	if(strlen(key)==0)
	{
		printf("密钥文件为空！\n");
		return false;
	}
	printf("密钥已从 data/rc4_key.txt 加载。\n");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 保存密文到文件（追加模式，含算法标签与时间戳）**

bool saveCipherToFile(const char *hexCipher)
{
	// 获取当前时间
	time_t now=time(NULL);
	struct tm *lt=localtime(&now);
	char timestamp[64];
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", lt);

	ofstream ofs("data/last_cipher.txt", ios::app);
	if(!ofs.is_open())
	{
		printf("无法打开 data/last_cipher.txt 进行写入！\n");
		return false;
	}
	ofs << "[RC4] " << timestamp << " " << hexCipher << endl;
	ofs.close();
	printf("密文已追加到 data/last_cipher.txt\n");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 从文件加载最近一条 RC4 密文 **
// 遍历文件，取最后一行以 [RC4] 开头的密文

bool loadCipherFromFile(char *hexCipher, int maxLen)
{
	ifstream ifs("data/last_cipher.txt");
	if(!ifs.is_open())
	{
		printf("无法打开 data/last_cipher.txt！\n");
		return false;
	}

	char line[MAX_LEN*2+128];	// 足够容纳一行
	char lastRC4[MAX_LEN*2+1]={0};
	bool found=false;

	while(ifs.getline(line, sizeof(line)))
	{
		// 判断是否以 "[RC4]" 开头
		if(strncmp(line, "[RC4]", 5)==0)
		{
			// 格式：[RC4] YYYY-MM-DD HH:MM:SS <hex>
			// 用 sscanf 跳过日期(%*s)和时间(%*s)，直接提取十六进制密文
			char hexBuf[MAX_LEN*2+2];
			if(sscanf(line, "[RC4] %*s %*s %s", hexBuf)==1)
			{
				strncpy(lastRC4, hexBuf, maxLen-1);
				lastRC4[maxLen-1]='\0';
				found=true;
			}
		}
	}
	ifs.close();

	if(!found)
	{
		printf("文件中未找到 [RC4] 标记的密文记录！\n");
		return false;
	}

	strncpy(hexCipher, lastRC4, maxLen-1);
	hexCipher[maxLen-1]='\0';
	printf("已从 data/last_cipher.txt 加载 RC4 密文。\n");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 打印 S 盒（前 n 字节）**

void printSBox(const unsigned char *S, const char *title)
{
	printf("\n---- %s ----\n", title);
	printf("  S盒前32字节: ");
	for(int i=0; i<32; i++)
		printf("%02x ", S[i]);
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选项1：RC4 加密子系统 **

void encryptMenu(char *g_key)
{
	system("cls");
	cout<<"=========== RC4 加密 ===========\n\n";

	char plaintext[MAX_LEN];
	char keyInput[MAX_KEY_LEN+2];
	unsigned char plainBytes[MAX_LEN], cipherBytes[MAX_LEN];
	char hexCipher[MAX_LEN*2+1];
	unsigned char S[256];

	printf("请输入明文：");
	if(fgets(plaintext, sizeof(plaintext), stdin)==NULL)
	{
		printf("输入错误！\n");
		Pause(); return;
	}
	plaintext[strcspn(plaintext, "\n")]='\0';
	int plainLen=(int)strlen(plaintext);
	if(plainLen==0)
	{
		printf("明文不能为空！\n");
		Pause(); return;
	}

	// 密钥输入：优先使用当前会话密钥
	int keyLen;
	if(strlen(g_key)>0)
	{
		char useExisting;
		printf("当前会话密钥为: %s\n", g_key);
		printf("是否使用当前密钥？(Y/N): ");
		useExisting=getchar(); clearInputBuffer();
		if(useExisting=='Y' || useExisting=='y')
		{
			strcpy(keyInput, g_key);
			keyLen=(int)strlen(keyInput);
		}
		else
		{
			printf("请输入密钥（1~256 字符）：");
			if(fgets(keyInput, sizeof(keyInput), stdin)==NULL)
			{
				printf("输入错误！\n");
				Pause(); return;
			}
			keyInput[strcspn(keyInput, "\n")]='\0';
			keyLen=(int)strlen(keyInput);
		}
	}
	else
	{
		printf("请输入密钥（1~256 字符）：");
		if(fgets(keyInput, sizeof(keyInput), stdin)==NULL)
		{
			printf("输入错误！\n");
			Pause(); return;
		}
		keyInput[strcspn(keyInput, "\n")]='\0';
		keyLen=(int)strlen(keyInput);
	}

	if(keyLen<1 || keyLen>MAX_KEY_LEN)
	{
		printf("密钥长度必须在 1~%d 之间！\n", MAX_KEY_LEN);
		Pause(); return;
	}

	// 执行加密
	memcpy(plainBytes, plaintext, plainLen);
	RC4_Crypt(plainBytes, cipherBytes, plainLen, (unsigned char*)keyInput, keyLen);
	bytesToHex(cipherBytes, plainLen, hexCipher);

	// 输出结果
	cout<<"\n==============================\n";
	printf("明文: %s\n", plaintext);
	printf("密钥: %s (长度=%d字节)\n", keyInput, keyLen);
	printf("密文(十六进制): %s\n", hexCipher);
	cout<<"==============================\n";

	// 打印 S 盒中间状态（教学观察）
	RC4_KSA(S, (unsigned char*)keyInput, keyLen);
	printSBox(S, "KSA 完成后 S 盒");

	// 打印密钥流前 32 字节样例
	unsigned char sampleKS[32];
	RC4_PRGA(S, sampleKS, 32);
	printf("  密钥流前32字节: ");
	for(int i=0; i<32; i++)
		printf("%02x ", sampleKS[i]);
	printf("\n\n");

	// 保存当前密钥到会话
	strcpy(g_key, keyInput);

	// 询问是否保存密钥/密文到文件
	char saveChoice;
	printf("是否保存密钥到文件？(Y/N): ");
	saveChoice=getchar(); clearInputBuffer();
	if(saveChoice=='Y' || saveChoice=='y')
		saveKeyToFile(g_key);

	printf("是否保存密文到文件？(Y/N): ");
	saveChoice=getchar(); clearInputBuffer();
	if(saveChoice=='Y' || saveChoice=='y')
		saveCipherToFile(hexCipher);

	Pause();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选项2：RC4 解密子系统 **

void decryptMenu(char *g_key)
{
	system("cls");
	cout<<"=========== RC4 解密 ===========\n\n";

	char hexCipher[MAX_LEN*2+1];
	char keyInput[MAX_KEY_LEN+2];
	unsigned char cipherBytes[MAX_LEN], plainBytes[MAX_LEN];
	char plaintext[MAX_LEN];

	printf("=== 密文输入方式 ===\n");
	printf("  1. 手动输入十六进制密文\n");
	printf("  2. 从文件加载密文\n");
	printf("请选择 (1-2): ");
	char mode=getchar(); clearInputBuffer();

	if(mode=='2')
	{
		// 从文件加载密文
		if(!loadCipherFromFile(hexCipher, sizeof(hexCipher)))
		{
			Pause(); return;
		}
		printf("加载的密文: %s\n", hexCipher);
	}
	else
	{
		printf("请输入十六进制密文：");
		if(fgets(hexCipher, sizeof(hexCipher), stdin)==NULL)
		{
			printf("输入错误！\n");
			Pause(); return;
		}
		hexCipher[strcspn(hexCipher, "\n")]='\0';
		if(strlen(hexCipher)==0)
		{
			printf("密文不能为空！\n");
			Pause(); return;
		}
	}

	// 十六进制→二进制
	int cipherLen=hexToBytes(hexCipher, cipherBytes, sizeof(cipherBytes));
	if(cipherLen<0)
	{
		printf("密文格式错误！必须是偶数长度的十六进制字符串。\n");
		Pause(); return;
	}

	// 密钥输入
	printf("\n=== 密钥输入方式 ===\n");
	printf("  1. 手动输入密钥\n");
	if(strlen(g_key)>0)
		printf("  2. 使用当前会话密钥: %s\n", g_key);
	printf("  3. 从文件加载密钥\n");
	printf("请选择 (1-3): ");
	mode=getchar(); clearInputBuffer();

	if(mode=='3')
	{
		if(!loadKeyFromFile(keyInput, sizeof(keyInput)))
		{
			Pause(); return;
		}
		printf("加载的密钥: %s\n", keyInput);
	}
	else if(mode=='2' && strlen(g_key)>0)
	{
		strcpy(keyInput, g_key);
		printf("使用当前会话密钥: %s\n", keyInput);
	}
	else
	{
		printf("请输入密钥：");
		if(fgets(keyInput, sizeof(keyInput), stdin)==NULL)
		{
			printf("输入错误！\n");
			Pause(); return;
		}
		keyInput[strcspn(keyInput, "\n")]='\0';
	}

	int keyLen=(int)strlen(keyInput);
	if(keyLen<1 || keyLen>MAX_KEY_LEN)
	{
		printf("密钥长度必须在 1~%d 之间！\n", MAX_KEY_LEN);
		Pause(); return;
	}

	// 执行解密
	RC4_Crypt(cipherBytes, plainBytes, cipherLen, (unsigned char*)keyInput, keyLen);
	memcpy(plaintext, plainBytes, cipherLen);
	plaintext[cipherLen]='\0';

	// 输出结果
	cout<<"\n==============================\n";
	printf("密文(十六进制): %s\n", hexCipher);
	printf("密钥: %s (长度=%d字节)\n", keyInput, keyLen);
	printf("明文: %s\n", plaintext);
	cout<<"==============================\n";

	// 更新会话密钥
	strcpy(g_key, keyInput);

	Pause();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选项3：自验证子系统 **
// 随机生成明文和密钥 → 加密 → 解密 → 比对，验证加解密一致性

void selfVerify()
{
	system("cls");
	cout<<"=========== RC4 自验证 ===========\n\n";

	// 随机生成测试数据
	int testLen=rand()%100 + 10;		// 10~109 字节明文
	int keyLen=rand()%16 + 5;			// 5~20 字节密钥

	unsigned char plaintext[MAX_LEN], key[MAX_KEY_LEN];
	unsigned char cipherBytes[MAX_LEN], decrypted[MAX_LEN];
	char hexCipher[MAX_LEN*2+1];
	unsigned char S[256];

	// 生成随机明文
	for(int i=0; i<testLen; i++)
		plaintext[i]=(unsigned char)(rand()%95 + 32);  // 可打印ASCII字符

	// 生成随机密钥
	for(int i=0; i<keyLen; i++)
		key[i]=(unsigned char)(rand()%95 + 32);

	// 打印测试参数
	printf("明文长度: %d 字节\n", testLen);
	printf("明文内容: ");
	for(int i=0; i<testLen && i<60; i++)
		printf("%c", plaintext[i]);
	if(testLen>60) printf("...");
	printf("\n");

	printf("密钥长度: %d 字节\n", keyLen);
	printf("密钥内容: ");
	for(int i=0; i<keyLen; i++)
		printf("%c", key[i]);
	printf("\n\n");

	// --- 加密 ---
	printf("===== 加密过程 =====\n");
	RC4_Crypt(plaintext, cipherBytes, testLen, key, keyLen);
	bytesToHex(cipherBytes, testLen, hexCipher);
	printf("密文(十六进制): %s\n", hexCipher);

	// 打印 KSA 后的 S 盒
	unsigned char S_encrypt[256];
	RC4_KSA(S_encrypt, key, keyLen);
	printSBox(S_encrypt, "加密时 KSA 完成后 S 盒");

	// --- 解密 ---
	printf("\n===== 解密过程 =====\n");
	RC4_Crypt(cipherBytes, decrypted, testLen, key, keyLen);

	printf("解密结果: ");
	for(int i=0; i<testLen && i<60; i++)
		printf("%c", decrypted[i]);
	if(testLen>60) printf("...");
	printf("\n");

	// --- 比对 ---
	bool match=true;
	for(int i=0; i<testLen; i++)
	{
		if(plaintext[i] != decrypted[i])
		{
			match=false;
			break;
		}
	}

	cout<<"\n==============================\n";
	printf("验证结果: %s\n", match?"[成功] 加解密一致，RC4 算法正确！":"[失败] 加解密不一致，请检查算法！");
	cout<<"==============================\n";

	Pause();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选项4：密钥管理子系统 **

void keyManageMenu(char *g_key)
{
	int choice;
	char c='N';
	do
	{
		choice=999; c='N';
		system("cls");
		cout<<"=========== RC4 流密码 ===========\n";
		cout<<"----------------------------------\n";
		cout<<"--------- 密钥管理子系统 ---------\n";
		cout<<"      1. 查看当前密钥             \n";
		cout<<"      2. 保存密钥到文件           \n";
		cout<<"      3. 从文件加载密钥           \n";
		cout<<"      4. 随机生成密钥             \n";
		cout<<"      0. 返回主菜单               \n";
		cout<<"----------------------------------\n";
		cout<<"**********************************\n";
		printf("\n请选择 (0-4): ");
		cin>>(c);
		choice=input(c);
		clearInputBuffer();

		switch(choice)
		{
			case 0: return;

			case 1: {
				if(strlen(g_key)==0)
					printf("\n---- 当前无会话密钥！请先生成或加载密钥。----\n");
				else
					printf("\n---- 当前会话密钥: %s (长度=%d字节) ----\n", g_key, (int)strlen(g_key));
				break;
			}

			case 2: {
				if(strlen(g_key)==0)
				{
					printf("\n当前无会话密钥，请先输入或生成密钥！\n");
					break;
				}
				saveKeyToFile(g_key);
				break;
			}

			case 3: {
				char loadedKey[MAX_KEY_LEN+2]={0};
				if(loadKeyFromFile(loadedKey, sizeof(loadedKey)))
				{
					strcpy(g_key, loadedKey);
					printf("会话密钥已更新: %s\n", g_key);
				}
				break;
			}

			case 4: {
				int keyLen;
				char lenStr[10];

				printf("\n请输入密钥长度 (1-%d): ", MAX_KEY_LEN);
				if(fgets(lenStr, sizeof(lenStr), stdin)==NULL)
				{
					printf("输入错误！\n"); break;
				}
				lenStr[strcspn(lenStr, "\n")]='\0';
				keyLen=atoi(lenStr);
				if(keyLen<1 || keyLen>MAX_KEY_LEN)
				{
					printf("长度无效！\n");
					break;
				}

				for(int i=0; i<keyLen; i++)
					g_key[i]=(char)(rand()%95 + 32);  // 可打印字符
				g_key[keyLen]='\0';

				printf("已生成随机密钥: %s (长度=%d)\n", g_key, keyLen);
				break;
			}

			default: cout<<"\n---- 输入错误! ----\n";
		}
	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
	} while(choice!=0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选项5：密文文件操作子系统 **

void cipherFileMenu(char *g_key)
{
	int choice;
	char c='N';
	do
	{
		choice=999; c='N';
		system("cls");
		cout<<"=========== RC4 流密码 ===========\n";
		cout<<"----------------------------------\n";
		cout<<"------- 密文文件操作子系统 -------\n";
		cout<<"      1. 加密并保存密文到文件     \n";
		cout<<"      2. 从文件读取密文并解密     \n";
		cout<<"      0. 返回主菜单               \n";
		cout<<"----------------------------------\n";
		cout<<"**********************************\n";
		printf("\n请选择 (0-2): ");
		cin>>(c);
		choice=input(c);
		clearInputBuffer();

		switch(choice)
		{
			case 0: return;

			case 1: {
				char plaintext[MAX_LEN], keyInput[MAX_KEY_LEN+2];
				unsigned char plainBytes[MAX_LEN], cipherBytes[MAX_LEN];
				char hexCipher[MAX_LEN*2+1];

				printf("\n请输入明文：");
				if(fgets(plaintext, sizeof(plaintext), stdin)==NULL)
				{
					printf("输入错误！\n"); break;
				}
				plaintext[strcspn(plaintext, "\n")]='\0';
				int plainLen=(int)strlen(plaintext);
				if(plainLen==0)
				{
					printf("明文不能为空！\n"); break;
				}

				// 密钥
				if(strlen(g_key)>0)
				{
					printf("当前会话密钥: %s\n", g_key);
					printf("使用当前密钥？(Y/N): ");
					char yn=getchar(); clearInputBuffer();
					if(yn=='Y' || yn=='y')
						strcpy(keyInput, g_key);
					else
					{
						printf("请输入密钥：");
						if(fgets(keyInput, sizeof(keyInput), stdin)==NULL) break;
						keyInput[strcspn(keyInput, "\n")]='\0';
					}
				}
				else
				{
					printf("请输入密钥：");
					if(fgets(keyInput, sizeof(keyInput), stdin)==NULL) break;
					keyInput[strcspn(keyInput, "\n")]='\0';
				}

				int keyLen=(int)strlen(keyInput);
				if(keyLen<1 || keyLen>MAX_KEY_LEN)
				{
					printf("密钥长度无效！\n"); break;
				}

				// 加密
				memcpy(plainBytes, plaintext, plainLen);
				RC4_Crypt(plainBytes, cipherBytes, plainLen, (unsigned char*)keyInput, keyLen);
				bytesToHex(cipherBytes, plainLen, hexCipher);
				printf("密文(十六进制): %s\n", hexCipher);

				// 保存到文件
				saveCipherToFile(hexCipher);
				strcpy(g_key, keyInput);	// 更新会话密钥
				break;
			}

			case 2: {
				char hexCipher[MAX_LEN*2+1];
				char keyInput[MAX_KEY_LEN+2];
				unsigned char cipherBytes[MAX_LEN], plainBytes[MAX_LEN];
				char plaintext[MAX_LEN];

				if(!loadCipherFromFile(hexCipher, sizeof(hexCipher)))
					break;
				printf("加载的密文: %s\n", hexCipher);

				int cipherLen=hexToBytes(hexCipher, cipherBytes, sizeof(cipherBytes));
				if(cipherLen<0)
				{
					printf("密文格式错误！\n"); break;
				}

				// 密钥
				if(strlen(g_key)>0)
				{
					printf("当前会话密钥: %s\n", g_key);
					printf("使用当前密钥？(Y/N): ");
					char yn=getchar(); clearInputBuffer();
					if(yn=='Y' || yn=='y')
						strcpy(keyInput, g_key);
					else
					{
						printf("请输入密钥：");
						if(fgets(keyInput, sizeof(keyInput), stdin)==NULL) break;
						keyInput[strcspn(keyInput, "\n")]='\0';
					}
				}
				else
				{
					printf("请输入密钥：");
					if(fgets(keyInput, sizeof(keyInput), stdin)==NULL) break;
					keyInput[strcspn(keyInput, "\n")]='\0';
				}

				int keyLen=(int)strlen(keyInput);
				if(keyLen<1 || keyLen>MAX_KEY_LEN)
				{
					printf("密钥长度无效！\n"); break;
				}

				// 解密
				RC4_Crypt(cipherBytes, plainBytes, cipherLen, (unsigned char*)keyInput, keyLen);
				memcpy(plaintext, plainBytes, cipherLen);
				plaintext[cipherLen]='\0';

				printf("解密结果: %s\n", plaintext);
				strcpy(g_key, keyInput);
				break;
			}

			default: cout<<"\n---- 输入错误! ----\n";
		}
	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
	} while(choice!=0);
}
