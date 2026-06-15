// RSA_实验.cpp
// 只有 gcc 才能编译！
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
#include <fstream>
#include <direct.h>
#include <errno.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <cctype>
#include <chrono>

using namespace std;

void print_encoding_info();
string base64_encode(const unsigned char *buf, size_t len);
string base64_decode(const string &in);
string try_convert_utf8_to_local(const string &s);

// #region agent log
static string bytes_to_hex(const string& s, size_t maxn = 64) {
    stringstream hs;
    hs << std::hex;
    for (size_t i = 0; i < s.size() && i < maxn; ++i) {
        if (i) hs << " ";
        hs << (int)(unsigned char)s[i];
    }
    return hs.str();
}
static void dbg_log(const char* loc, const char* msg, const char* hyp,
                    const string& data_json) {
    ofstream lf("debug-76ba26.log", ios::app);
    if (!lf) return;
    auto ts = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
    lf << "{\"sessionId\":\"76ba26\",\"timestamp\":" << ts
       << ",\"location\":\"" << loc << "\",\"message\":\"" << msg
       << "\",\"hypothesisId\":\"" << hyp << "\",\"data\":" << data_json
       << ",\"runId\":\"post-fix\"}\n";
}
// #endregion

typedef unsigned long long ull;
typedef long long ll;

void Menu();
int input(char c);
bool InputInt(const char *s, int *n);
void clearInputBuffer();

// RSA 功能模块
ull modmul(ull a, ull b, ull mod);
ull modpow(ull a, ull d, ull mod);
bool isPrime(ull n);
ull genPrime(ull bits);
ull gcd_ll(ull a, ull b);
ll egcd(ll a, ll b, ll &x, ll &y);
ull modinv(ull a, ull m);
void genKeys(ull &n, ull &e, ull &d);
// 密钥持久化
bool saveKeys(const char* path, ull n, ull e, ull d);
bool loadKeys(const char* path, ull &n, ull &e, ull &d);
vector<ull> string_to_blocks(const string &s, ull n);
string blocks_to_string(const vector<ull> &blocks, ull n);
vector<ull> encrypt_blocks(const vector<ull> &blocks, ull e, ull n);
vector<ull> decrypt_blocks(const vector<ull> &blocks, ull d, ull n);
string blocks_to_hex(const vector<ull> &blocks);
vector<ull> hex_to_blocks(const string &hexstr);

int main()
{
    srand((unsigned)time(NULL));
    // 统一控制台为 UTF-8，避免中文输入/输出乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    print_encoding_info();

    ull n = 0, e = 0, d = 0;
    int choice = 0;
    char c = 'N';

    do {
        Menu();
        cin >> c;
        choice = input(c);
        clearInputBuffer();

        switch(choice) {
            case 0:
                cout << "\n退出程序。\n";
                break;
            case 1: {
                genKeys(n, e, d);
                cout << "\n生成密钥成功！\n";
                printf("公钥 (n, e):\n n = %llu\n e = %llu\n", n, e);
                printf("私钥 d = %llu\n", d);
                const char* keypath = "data/rsa_keypair.txt";
                if(saveKeys(keypath, n, e, d))
                    cout << "密钥已保存到 " << keypath << "\n";
                else
                    cout << "密钥保存失败！\n";
                break;
            }
            case 2: {
                if(n==0 || e==0) {
                    // 尝试从文件加载公钥
                    const char* keypath = "data/rsa_keypair.txt";
                    if(loadKeys(keypath, n, e, d)) {
                        cout << "从 " << keypath << " 加载密钥成功。\n";
                    } else {
                        cout << "\n请先生成密钥（选项1）或将密钥文件 " << keypath << " 放到程序目录。\n";
                        break;
                    }
                }
                cout << "\n请输入明文（一行）:\n";
                string plain;
                getline(cin, plain);
                if(plain.size()==0) { getline(cin, plain); } // in case newline
                // 为保证跨环境正确恢复，先将原始字节 base64 编码，再加密 base64 文本
                string b64 = base64_encode((const unsigned char*)plain.data(), plain.size());
                vector<ull> blocks = string_to_blocks(b64, n);
                vector<ull> cipher = encrypt_blocks(blocks, e, n);
                string hex = blocks_to_hex(cipher);
                // #region agent log
                {
                    stringstream dj;
                    dj << "{\"n\":" << n << ",\"plainLen\":" << plain.size()
                       << ",\"plainHex\":\"" << bytes_to_hex(plain) << "\""
                       << ",\"b64Len\":" << b64.size() << ",\"b64\":\"" << b64 << "\""
                       << ",\"blockCount\":" << blocks.size()
                       << ",\"blocks\":[";
                    for (size_t i = 0; i < blocks.size(); ++i) {
                        if (i) dj << ",";
                        dj << blocks[i];
                    }
                    dj << "]}";
                    dbg_log("RSA.cpp:encrypt", "encrypt_done", "F", dj.str());
                }
                // #endregion
                cout << "\n加密后密文（16 进制块, 空格分隔）:\n" << hex << "\n";
                cout << "（共 " << cipher.size() << " 个块，解密时请完整粘贴全部块）\n";
                break;
            }
            case 3: {
                if(n==0 || d==0) {
                    // 尝试从文件加载密钥
                    const char* keypath = "data/rsa_keypair.txt";
                    if(loadKeys(keypath, n, e, d)) {
                        cout << "从 " << keypath << " 加载密钥成功。\n";
                    } else {
                        cout << "\n请先生成密钥（选项1）或确保 " << keypath << " 存在。\n";
                        break;
                    }
                }
                cout << "\n请输入密文（16 进制块，空格分隔）:\n";
                string hex;
                getline(cin, hex);
                if(hex.size()==0) { getline(cin, hex); }
                vector<ull> cipher = hex_to_blocks(hex);
                vector<ull> plain_blocks = decrypt_blocks(cipher, d, n);
                // #region agent log
                {
                    stringstream dj;
                    dj << "{\"cipherCount\":" << cipher.size()
                       << ",\"plainBlocks\":[";
                    for (size_t i = 0; i < plain_blocks.size(); ++i) {
                        if (i) dj << ",";
                        dj << plain_blocks[i];
                    }
                    dj << "]}";
                    dbg_log("RSA.cpp:decrypt", "decrypt_blocks_done", "G", dj.str());
                }
                // #endregion
                // 首先把解密得到的文本视为 base64 再解码回原始字节
                string b64 = blocks_to_string(plain_blocks, n);
                // #region agent log
                {
                    stringstream dj;
                    ull tmp = n - 1; int bb = 0; while (tmp) { bb++; tmp >>= 8; }
                    ull first = plain_blocks.empty() ? 0 : plain_blocks[0];
                    size_t maxpb = plain_blocks.size() >= 2 ? (plain_blocks.size()-1) * (size_t)bb : 0;
                    dj << "{\"b64Len\":" << b64.size() << ",\"b64\":\"" << b64 << "\""
                       << ",\"blockBytes\":" << bb << ",\"firstBlock\":" << first
                       << ",\"maxPayload\":" << maxpb
                       << ",\"useLengthHeader\":" << (first <= maxpb ? "true" : "false") << "}";
                    dbg_log("RSA.cpp:decrypt", "blocks_to_string_done", "H", dj.str());
                }
                // #endregion
                string orig = base64_decode(b64);
                // #region agent log
                {
                    stringstream dj;
                    dj << "{\"origLen\":" << orig.size()
                       << ",\"origHex\":\"" << bytes_to_hex(orig) << "\"}";
                    dbg_log("RSA.cpp:decrypt", "base64_decode_done", "I", dj.str());
                }
                // #endregion
                if(orig.empty()) {
                    cout << "\n（警告）解密后的 base64 解码为空，显示解密得到的整数块以便调试：\n";
                    for(size_t i=0;i<plain_blocks.size();++i) {
                        printf("块 %zu : dec=%llu hex=%llx\n", i, plain_blocks[i], plain_blocks[i]);
                    }
                } else if(!plain_blocks.empty() && b64.size() != (size_t)plain_blocks[0]) {
                    cout << "\n（警告）恢复的 base64 长度 " << b64.size()
                         << " 与长度头 " << plain_blocks[0] << " 不一致，密文可能不完整。\n";
                }
                // #region agent log
                {
                    stringstream dj;
                    dj << "{\"origLen\":" << orig.size()
                       << ",\"displaySameAsOrig\":true"
                       << ",\"origHex\":\"" << bytes_to_hex(orig) << "\"}";
                    dbg_log("RSA.cpp:decrypt", "display_output", "J", dj.str());
                }
                // #endregion
                cout << "\n解密后明文:\n" << orig << "\n";
                break;
            }
            default:
                cout << "\n无效选择！\n";
        }

        if(choice!=0) {
            cout << "\n按回车继续...";
            getchar();
        }
    } while(choice!=0);

    return 0;
}

void Menu()
{
    system("cls");
    cout << "******* RSA 密码学实验 *******\n";
    cout << "-----------------------------\n";
    cout << "  1  生成 RSA 密钥对\n";
    cout << "  2  对明文加密\n";
    cout << "  3  对密文解密\n";
    cout << "  0  退出\n";
    cout << "-----------------------------\n";
    cout << "请选择: ";
}

int input(char c)
{
    if('0'<=c && c<='9') return c - '0';
    return -1;
}

bool InputInt(const char *s, int *n)
{
    if(s) printf("%s", s);
    if(scanf("%d", n)!=1) {
        printf("\n输入错误!\n");
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

void clearInputBuffer() {
    while(getchar()!='\n');
}

// ----------------- RSA 辅助实现 -----------------

// 便携的乘法取模（避免在不支持 __uint128_t 的编译器上报错）
ull modmul(ull a, ull b, ull mod)
{
    if (mod == 0) return 0;
    a %= mod;
    b %= mod;
    ull res = 0;
    while (b) {
        if (b & 1) {
            // res = (res + a) % mod;  // 使用无溢出的加法方式
            if (mod - res <= a) res = res + a - mod;
            else res = res + a;
        }
        b >>= 1;
        if (b) {
            // a = (a + a) % mod;
            if (a >= mod - a) a = a + a - mod;
            else a = a + a;
        }
    }
    return res % mod;
}

ull modpow(ull a, ull d, ull mod)
{
    ull res = 1;
    ull base = a % mod;
    while(d) {
        if(d & 1) res = modmul(res, base, mod);
        base = modmul(base, base, mod);
        d >>= 1;
    }
    return res;
}

// Miller-Rabin 判定（64 位确定性基集合）
bool isPrime(ull n)
{
    if(n < 2) return false;
    static ull smallPrimes[] = {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,0};
    for(int i=0; smallPrimes[i]; ++i) {
        if(n % smallPrimes[i] == 0) return n == smallPrimes[i];
    }
    ull d = n-1, s = 0;
    while((d & 1) == 0) { d >>= 1; ++s; }
    ull bases[] = {2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL,0};
    for(int i=0; bases[i]; ++i) {
        ull a = bases[i] % n;
        if(a==0) continue;
        ull x = modpow(a, d, n);
        if(x==1 || x==n-1) continue;
        bool composite = true;
        for(ull r=1; r<s; ++r) {
            x = modmul(x, x, n);
            if(x == n-1) { composite = false; break; }
        }
        if(composite) return false;
    }
    return true;
}

// 随机生成 bits 位素数（注意：bits <= 63）
ull genPrime(ull bits)
{
    if(bits < 3) bits = 3;
    ull low = 1ULL << (bits-1);
    ull high = ((bits==64)?~0ULL:((1ULL<<bits)-1));
    while(true) {
        ull x = ((ull)rand() << 32) ^ ((ull)rand() << 16) ^ rand();
        x = (x % (high - low + 1)) + low;
        x |= 1ULL; // 奇数
        if(isPrime(x)) return x;
    }
}

ull gcd_ll(ull a, ull b)
{
    while(b) { ull t = a % b; a = b; b = t; }
    return a;
}

ll egcd(ll a, ll b, ll &x, ll &y)
{
    if(b==0) { x = 1; y = 0; return a; }
    ll x1,y1;
    ll g = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b) * y1;
    return g;
}

ull modinv(ull a, ull m)
{
    // phi 可达 ~2^64，必须用 128 位中间量，不能用有符号 ll
    __int128 t = 0, newt = 1;
    __int128 r = m, newr = a % m;
    while (newr != 0) {
        __int128 q = r / newr;
        __int128 tmp = t; t = newt; newt = tmp - q * newt;
        tmp = r; r = newr; newr = tmp - q * newr;
    }
    if (r > 1) return 0;
    __int128 res = t;
    if (res < 0) res += m;
    return (ull)res;
}

// 生成密钥：为演示选择较小位长（例如 32 位素数各自 -> n ~ 64 位）

// 将密钥保存到文本文件（n e d），并确保目录存在
bool ensure_parent_dir(const std::string &filepath)
{
    size_t pos = filepath.find_last_of("\\/");
    if(pos == std::string::npos) return true;
    std::string dir = filepath.substr(0, pos);
    std::string cur;
    for(size_t i=0;i<dir.size();++i) {
        cur.push_back(dir[i]);
        if(dir[i]=='\\' || dir[i]=='/') {
            std::string t = cur.substr(0, cur.size()-1);
            if(_mkdir(t.c_str()) != 0) {
                if(errno != EEXIST) {
                    // 继续尝试其余目录
                }
            }
        }
    }
    if(_mkdir(dir.c_str()) != 0) {
        if(errno != EEXIST) {
            return false;
        }
    }
    return true;
}

bool saveKeys(const char* path, ull n, ull e, ull d)
{
    if(!ensure_parent_dir(std::string(path))) return false;
    std::ofstream ofs(path);
    if(!ofs) return false;
    ofs << n << " " << e << " " << d << "\n";
    ofs.close();
    return true;
}

// 从文本文件加载密钥（尝试读取 n e d）
bool loadKeys(const char* path, ull &n, ull &e, ull &d)
{
    std::ifstream ifs(path);
    if(!ifs) return false;
    ull rn=0,re=0,rd=0;
    ifs >> rn >> re >> rd;
    if(!ifs) return false;
    n = rn; e = re; d = rd;
    return true;
}

void genKeys(ull &n, ull &e, ull &d)
{
    // 这里为演示使用 32 位素数
    ull p = genPrime(32);
    ull q = genPrime(32);
    while(q == p) q = genPrime(32);
    n = p * q;
    ull phi = (p-1)*(q-1);
    e = 65537; // 常用公钥指数
    if(gcd_ll(e, phi) != 1) {
        // 找一个小的 e
        e = 3;
        while(gcd_ll(e, phi) != 1) e += 2;
    }
    d = modinv(e, phi);
    // #region agent log
    {
        stringstream dj;
        dj << "{\"p\":" << p << ",\"q\":" << q << ",\"n\":" << n << ",\"e\":" << e
           << ",\"d\":" << d << ",\"phi\":" << phi
           << ",\"verify\":" << modpow(modpow(42,e,n),d,n) << "}";
        dbg_log("RSA.cpp:genKeys", "keys_generated", "D", dj.str());
    }
    // #endregion
}

// 将字符串打包为小于 n 的整数块（按字节合并，保证块值 < n）
vector<ull> string_to_blocks(const string &s, ull n)
{
    vector<ull> blocks;
    // 计算每块能容纳的字节数（block_bytes）
    ull tmp = n - 1;
    int block_bytes = 0;
    while(tmp) { block_bytes++; tmp >>= 8; }
    if(block_bytes <= 0) block_bytes = 1;
    // 首个块保存原始明文长度
    blocks.push_back((ull)s.size());
    size_t i = 0;
    while(i < s.size()) {
        ull block = 0;
        for(int k = 0; k < block_bytes && i < s.size(); ++k, ++i) {
            block |= ((ull)(unsigned char)s[i]) << (8 * k); // little-endian
        }
        blocks.push_back(block);
    }
    if(blocks.size() == 1) // 空明文时仍保持一个长度块
        blocks.push_back(0);
    return blocks;
}

string blocks_to_string(const vector<ull> &blocks, ull n)
{
    string out;
    if(blocks.empty()) return out;
    ull tmp = n - 1;
    int block_bytes = 0;
    while(tmp) { block_bytes++; tmp >>= 8; }
    if(block_bytes <= 0) block_bytes = 1;

    // 加密端始终在首块写入 payload 长度，解密端固定按长度头还原
    if(blocks.size() < 2) return out;
    size_t need = (size_t)blocks[0];
    size_t got = 0;
    for(size_t bi = 1; bi < blocks.size() && got < need; ++bi) {
        ull x = blocks[bi];
        for(int k = 0; k < block_bytes && got < need; ++k) {
            unsigned char ch = (unsigned char)(x & 0xFFULL);
            out.push_back((char)ch);
            x >>= 8;
            ++got;
        }
    }
    return out;
}

// Base64 helpers
static const string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64_encode(const unsigned char *buf, size_t len) {
    string ret;
    int i=0; unsigned char char_array_3[3]; unsigned char char_array_4[4];
    size_t pos = 0;
    while(len--) {
        char_array_3[i++] = buf[pos++];
        if(i==3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for(int j=0;j<4;j++) ret.push_back(b64_chars[char_array_4[j]]);
            i=0;
        }
    }
    if(i) {
        for(int j=i;j<3;j++) char_array_3[j]=0;
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for(int j=0;j<i+1;j++) ret.push_back(b64_chars[char_array_4[j]]);
        while((int)ret.size()%4) ret.push_back('=');
    }
    return ret;
}

inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c=='+') || (c=='/'));
}

string base64_decode(const string &in) {
    size_t len = in.size();
    string ret;
    int i=0; int j=0; int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    while(len-- && ( in[in_] != '=') && is_base64(in[in_])) {
        char_array_4[i++] = in[in_]; in_++;
        if(i==4) {
            for(i=0;i<4;i++) char_array_4[i] = (unsigned char)b64_chars.find(char_array_4[i]);
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for(i=0;i<3;i++) ret.push_back((char)char_array_3[i]);
            i=0;
        }
    }
    if(i) {
        for(j=i;j<4;j++) char_array_4[j]=0;
        for(j=0;j<4;j++) char_array_4[j] = (unsigned char)b64_chars.find(char_array_4[j]);
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for(j=0;j<i-1;j++) ret.push_back((char)char_array_3[j]);
    }
    return ret;
}

// 尝试把 UTF-8 字节串转换为当前 ANSI 代码页字符串以正确显示
string try_convert_utf8_to_local(const string &s) {
    if(s.empty()) return s;
    // 先尝试把 s 当作 UTF-8 转为宽字符
    int wide_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.c_str(), (int)s.size(), NULL, 0);
    if(wide_len == 0) {
        // 不是合法 UTF-8，直接返回原始字符串（假定已是本地编码）
        return s;
    }
    std::vector<wchar_t> wbuf(wide_len+1);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), wbuf.data(), wide_len);
    wbuf[wide_len]=0;
    int out_len = WideCharToMultiByte(CP_ACP, 0, wbuf.data(), -1, NULL, 0, NULL, NULL);
    if(out_len == 0) return s;
    std::vector<char> outbuf(out_len);
    WideCharToMultiByte(CP_ACP, 0, wbuf.data(), -1, outbuf.data(), out_len, NULL, NULL);
    return string(outbuf.data());
}

void print_encoding_info()
{
    DWORD in_cp = GetConsoleCP();
    DWORD out_cp = GetConsoleOutputCP();
    UINT acp = GetACP();
    BOOL isTTY = _isatty(_fileno(stdout));
    char cwd[1024];
    DWORD cwdlen = GetCurrentDirectoryA(sizeof(cwd), cwd);

    printf("[环境诊断] 控制台输入代码页: %u\n", (unsigned)in_cp);
    printf("[环境诊断] 控制台输出代码页: %u\n", (unsigned)out_cp);
    printf("[环境诊断] 系统 ANSI 代码页(GetACP): %u\n", (unsigned)acp);
    printf("[环境诊断] stdout 是否为终端(isatty): %d\n", (int)isTTY);
    if(cwdlen > 0 && cwdlen < (DWORD)sizeof(cwd)) printf("[环境诊断] 当前工作目录: %s\n", cwd);

    // 显示示例 UTF-8 字符串（用字节字面量避免源文件编码影响）
    const unsigned char sample_utf8[] = {
        0xE4,0xBD,0xA0,0xE5,0xA5,0xBD,0xEF,0xBC,0x8C,
        0xE6,0x96,0xB0,0xE4,0xB8,0x96,0xE7,0x95,0x8C,0
    };
    string sample((const char*)sample_utf8);
    printf("[示例] UTF-8 文本: %s\n", sample.c_str());

    if(GetConsoleOutputCP() != CP_UTF8) {
        printf("[提示] 已尝试切换控制台为 UTF-8；若仍乱码，请确认终端字体支持中文。\n");
    }
}

vector<ull> encrypt_blocks(const vector<ull> &blocks, ull e, ull n)
{
    vector<ull> out;
    for(ull m : blocks) {
        ull c = modpow(m, e, n);
        out.push_back(c);
    }
    return out;
}

vector<ull> decrypt_blocks(const vector<ull> &blocks, ull d, ull n)
{
    vector<ull> out;
    for(ull c : blocks) {
        ull m = modpow(c, d, n);
        out.push_back(m);
    }
    return out;
}

string blocks_to_hex(const vector<ull> &blocks)
{
    stringstream ss;
    for(size_t i=0;i<blocks.size();++i) {
        ss << std::hex << blocks[i];
        if(i+1<blocks.size()) ss << " ";
    }
    return ss.str();
}

vector<ull> hex_to_blocks(const string &hexstr)
{
    vector<ull> out;
    stringstream ss(hexstr);
    string token;
    while(ss >> token) {
        ull v = 0;
        std::stringstream conv;
        conv << std::hex << token;
        conv >> v;
        out.push_back(v);
    }
    return out;
}