#include <jni.h>
#include <string>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <android/log.h>
#include <cstring>

#define LOG_TAG "DES_LOG"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace std;

// 🔥 密钥也混淆存储（每个字节 ^ 0x5A）
unsigned char obfuscated_key[] = {
        's' ^ 0x5A, 'e' ^ 0x5A, 'c' ^ 0x5A, 'u' ^ 0x5A,
        'r' ^ 0x5A, 'i' ^ 0x5A, 't' ^ 0x5A, 'y' ^ 0x5A,
        0x00
};

// 🔥 加密数据（同样可以混淆，这里为了演示直接加明文了）
unsigned char obfuscated_data[] = {
        's' ^ 0x5A, 'e' ^ 0x5A, 'c' ^ 0x5A, 'u' ^ 0x5A,
        'r' ^ 0x5A, 'i' ^ 0x5A, 't' ^ 0x5A, 'y' ^ 0x5A,
        0x00
};

// 通用解混淆函数
void decode(unsigned char *data, unsigned char xor_key) {
    for (int i = 0; data[i] != 0; i++) {
        data[i] ^= xor_key;
    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_des_MainActivity_desEncrypt(JNIEnv *env, jobject thiz) {
    // 1. 解密出明文数据
    unsigned char real_data[9] = {0};
    memcpy(real_data, obfuscated_data, sizeof(obfuscated_data));
    decode(real_data, 0x5A);

    // 2. 解密出真实key
    unsigned char real_key[9] = {0};
    memcpy(real_key, obfuscated_key, sizeof(obfuscated_key));
    decode(real_key, 0x5A);

    LOGI("解混淆得到的明文: %s", real_data);
    LOGI("解混淆得到的密钥: %s", real_key);

    // 3. 用解混淆后的 key 加密
    unsigned char out[1024] = {0};
    DES_key_schedule key_sch;
    DES_set_key((const_DES_cblock *)real_key, &key_sch);

    // 只加密8字节
    DES_ecb_encrypt((const_DES_cblock *)real_data, (DES_cblock *)out, &key_sch, DES_ENCRYPT);

    // 4. 打印加密结果
    std::string hexStr;
    for (int i = 0; i < 8; ++i) {
        char buf[5];
        sprintf(buf, "%02x ", out[i]);
        hexStr.append(buf);
    }
    LOGE("加密后的16进制: %s", hexStr.c_str());

    jstring javaString = env->NewStringUTF(hexStr.c_str());
    return javaString;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_des_MainActivity_desDecrypt(JNIEnv *env, jobject thiz) {
    // 注意：这里用你加密出来的密文
    unsigned char encrypted_data[8] = { 0x3a, 0x84, 0xe7, 0x60, 0x3a, 0x0c, 0xc8, 0x4c };

    // 解密 key
    unsigned char real_key[9] = {0};
    memcpy(real_key, obfuscated_key, sizeof(obfuscated_key));
    decode(real_key, 0x5A);

    unsigned char out2[1024] = {0};
    DES_key_schedule key_sch;
    DES_set_key((const_DES_cblock *)real_key, &key_sch);

    DES_ecb_encrypt((const_DES_cblock *)encrypted_data, (DES_cblock *)out2, &key_sch, DES_DECRYPT);

    std::string decrypted_str(reinterpret_cast<char *>(out2), 8);
    LOGE("解密后的字符串: %s", decrypted_str.c_str());

    jstring javaString = env->NewStringUTF(decrypted_str.c_str());
    return javaString;
}
