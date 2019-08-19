#include <jni.h>
#include <string>
#include "smAlgorithm-lib.h"

extern "C" JNIEXPORT void
Java_com_example_smalgorithm_SMAlgorithm_SM2Init(
        JNIEnv *env,
        jobject instance
) {
    SM2Init();
}

extern "C" JNIEXPORT void
Java_com_example_smalgorithm_SMAlgorithm_SM2GenKey(
        JNIEnv *env,
        jobject instance,
        jbyteArray priKey_, jintArray priKeyLen_,
        jbyteArray pubKey_, jintArray pubKeyLen_
) {

    jbyte *priKey = env->GetByteArrayElements(priKey_, NULL);
    jint *priKeyLen = env->GetIntArrayElements(priKeyLen_, NULL);
    jbyte *pubKey = env->GetByteArrayElements(pubKey_, NULL);
    jint *pubKeyLen = env->GetIntArrayElements(pubKeyLen_, NULL);

    RC_U8 *b_priKey = (RC_U8 *) priKey;
    RC_U8 *b_pubKey = (RC_U8 *) pubKey;

    SM2GenKey(b_priKey, priKeyLen, b_pubKey, pubKeyLen);

    env->ReleaseByteArrayElements(priKey_, priKey, 0);
    env->ReleaseByteArrayElements(pubKey_, pubKey, 0);
    env->ReleaseIntArrayElements(priKeyLen_, priKeyLen, 0);
    env->ReleaseIntArrayElements(pubKeyLen_, pubKeyLen, 0);
}

extern "C" JNIEXPORT jint
Java_com_example_smalgorithm_SMAlgorithm_SM2SignHash(
        JNIEnv *env,
        jobject instance,
        jbyteArray hash_, jint iHashLen,
        jbyteArray priKey_, jint iPriKeyLen,
        jbyteArray sign_, jintArray piSignLen_
) {

    jbyte *hash = env->GetByteArrayElements(hash_, NULL);
    jbyte *priKey = env->GetByteArrayElements(priKey_, NULL);
    jbyte *sign = env->GetByteArrayElements(sign_, NULL);
    jint *piSignLen = env->GetIntArrayElements(piSignLen_, NULL);

    RC_U8 *b_hash = (RC_U8 *) hash;
    RC_U8 *b_priKey = (RC_U8 *) priKey;
    RC_U8 *b_sign = (RC_U8 *) sign;

    if(iPriKeyLen!=SM2_PRIVATE_KEY_LEN){
        return SM2_PRIVATE_KEY_LEN_ERROR;
    }

    if(iHashLen!=SM3_KEY_LEN){
        return SM3_KEY_LEN_ERROR;
    }

    int rst = SM2SignHash(b_hash, iHashLen, b_priKey, iPriKeyLen, b_sign, piSignLen);

    env->ReleaseByteArrayElements(hash_, hash, 0);
    env->ReleaseByteArrayElements(priKey_, priKey, 0);
    env->ReleaseByteArrayElements(sign_, sign, 0);
    env->ReleaseIntArrayElements(piSignLen_, piSignLen, 0);
    return rst;
}

extern "C" JNIEXPORT jint
Java_com_example_smalgorithm_SMAlgorithm_SM2VerifyHash(
        JNIEnv *env,
        jobject instance,
        jbyteArray hash_, jint iHashLen,
        jbyteArray pubKey_, jint iPubKeyLen,
        jbyteArray sign_, jint piSignLen
) {

    jbyte *hash = env->GetByteArrayElements(hash_, NULL);
    jbyte *pubKey = env->GetByteArrayElements(pubKey_, NULL);
    jbyte *sign = env->GetByteArrayElements(sign_, NULL);

    RC_U8 *b_hash = (RC_U8 *) hash;
    RC_U8 *b_pubKey = (RC_U8 *) pubKey;
    RC_U8 *b_sign = (RC_U8 *) sign;

    if(iHashLen!=SM3_KEY_LEN){
        return SM3_KEY_LEN_ERROR;
    }

    if(piSignLen!=SM2_SIGN_LEN){
        return SM2_SIGN_LEN_ERROR;
    }

    if(iPubKeyLen!=SM2_PUBLIC_KEY_LEN){
        return SM2_PUBLIC_KEY_LEN_ERROR;
    }

    int rst = SM2VerifyHash(b_hash, iHashLen, b_pubKey, iPubKeyLen, b_sign, piSignLen);

    env->ReleaseByteArrayElements(hash_, hash, 0);
    env->ReleaseByteArrayElements(pubKey_, pubKey, 0);
    env->ReleaseByteArrayElements(sign_, sign, 0);
    return rst;
}

extern "C" JNIEXPORT void
Java_com_example_smalgorithm_SMAlgorithm_DotProduct(
        JNIEnv *env,
        jobject instance,
        jbyteArray workKey_,
        jbyteArray pubKey_,
        jbyteArray priKey_
) {

    jbyte *workKey = env->GetByteArrayElements(workKey_, NULL);
    jbyte *pubKey = env->GetByteArrayElements(pubKey_, NULL);
    jbyte *priKey = env->GetByteArrayElements(priKey_, NULL);


    RC_U8 *b_workKey = (RC_U8 *) workKey;
    RC_U8 *b_priKey = (RC_U8 *) priKey;
    RC_U8 *b_pubKey = (RC_U8 *) pubKey;

    DotProduct(b_workKey, b_pubKey, b_priKey);

    env->ReleaseByteArrayElements(workKey_, workKey, 0);
    env->ReleaseByteArrayElements(priKey_, priKey, 0);
    env->ReleaseByteArrayElements(pubKey_, pubKey, 0);
}

extern "C" JNIEXPORT void
Java_com_example_smalgorithm_SMAlgorithm_sm3(
        JNIEnv *env,
        jobject instance,
        jbyteArray data_, jint iLen, jbyteArray outData_
) {

    jbyte *data = env->GetByteArrayElements(data_, NULL);
    jbyte *outData = env->GetByteArrayElements(outData_, NULL);

    RC_U8 *b_data = (RC_U8 *) data;
    RC_U8 *b_outData = (RC_U8 *) outData;

    if (iLen <= 0) {
        return;
    }

    sm3(b_data, iLen, b_outData);

    env->ReleaseByteArrayElements(data_, data, 0);
    env->ReleaseByteArrayElements(outData_, outData, 0);
}

extern "C" JNIEXPORT void
Java_com_example_smalgorithm_SMAlgorithm_sm3_1hmac(
        JNIEnv *env,
        jobject instance,
        jbyteArray key_, jint keyLen,
        jbyteArray data_, jint iLen, jbyteArray outData_
) {
    jbyte *key = env->GetByteArrayElements(key_, NULL);
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    jbyte *outData = env->GetByteArrayElements(outData_, NULL);

    RC_U8 *b_key = (RC_U8 *) key;
    RC_U8 *b_data = (RC_U8 *) data;
    RC_U8 *b_outData = (RC_U8 *) outData;

    if (keyLen <= 0) {
        return;
    }
    if (iLen <= 0) {
        return;
    }

    sm3_hmac(b_key, keyLen, b_data, iLen, b_outData);


    env->ReleaseByteArrayElements(key_, key, 0);
    env->ReleaseByteArrayElements(data_, data, 0);
    env->ReleaseByteArrayElements(outData_, outData, 0);
}

extern "C" JNIEXPORT jint
Java_com_example_smalgorithm_SMAlgorithm_Mode_1SMS4_1encrypt(
        JNIEnv *env,
        jobject instance,
        jbyteArray key_, jint keyLen, jbyteArray iv_,
        jbyteArray data_, jint iLen, jbyteArray outData_,
        jintArray outLen_, jint mode
) {
    jbyte *key = env->GetByteArrayElements(key_, NULL);
    jbyte *iv = env->GetByteArrayElements(iv_, NULL);
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    jbyte *outData = env->GetByteArrayElements(outData_, NULL);
    jint *outLen = env->GetIntArrayElements(outLen_, NULL);


    RC_U8 *b_key = (RC_U8 *) key;
    RC_U8 *b_iv = (RC_U8 *) iv;
    RC_U8 *b_data = (RC_U8 *) data;
    RC_U8 *b_outData = (RC_U8 *) outData;
    RC_U32 *b_outLen = (RC_U32 *) outLen;

    if (keyLen <= 0 || keyLen != 16) {
        return SM4_KEY_LEN_ERROR;
    }
    if (iLen <= 0 ) {
        return SM4_INPUT_IS_NULL;
    }
    if(mode==ALG_MODE_CBC && iLen % 16 != 0){
        return SM4_CBC_LEN_ERROR;
    }

    int result = Mode_SMS4_encrypt(b_key, (RC_U32) keyLen, b_iv, b_data, (RC_U32) iLen, b_outData, b_outLen, mode);

    memset(outLen, iLen, 1);

    env->ReleaseByteArrayElements(key_, key, 0);
    env->ReleaseByteArrayElements(iv_, iv, 0);
    env->ReleaseByteArrayElements(data_, data, 0);
    env->ReleaseByteArrayElements(outData_, outData, 0);
    env->ReleaseIntArrayElements(outLen_, outLen, 0);

    return result;
}

extern "C" JNIEXPORT jint
Java_com_example_smalgorithm_SMAlgorithm_Mode_1SMS4_1decrypt(
        JNIEnv *env,
        jobject instance,
        jbyteArray key_, jint keyLen, jbyteArray iv_,
        jbyteArray data_, jint iLen, jbyteArray outData_,
        jintArray outLen_, jint mode
) {
    jbyte *key = env->GetByteArrayElements(key_, NULL);
    jbyte *iv = env->GetByteArrayElements(iv_, NULL);
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    jbyte *outData = env->GetByteArrayElements(outData_, NULL);
    jint *outLen = env->GetIntArrayElements(outLen_, NULL);

    RC_U8 *b_key = (RC_U8 *) key;
    RC_U8 *b_iv = (RC_U8 *) iv;
    RC_U8 *b_data = (RC_U8 *) data;
    RC_U8 *b_outData = (RC_U8 *) outData;
    RC_U32 *b_outLen = (RC_U32 *) outLen;

    if (keyLen <= 0 || keyLen != 16) {
        return SM4_KEY_LEN_ERROR;
    }
    if (iLen <= 0) {
        return SM4_INPUT_IS_NULL;
    }
    if(mode==ALG_MODE_CBC && iLen % 16 != 0){
        return SM4_CBC_LEN_ERROR;
    }

    int result = Mode_SMS4_decrypt(b_key, (RC_U32) keyLen, b_iv, b_data, (RC_U32) iLen, b_outData, b_outLen, mode);

    memset(outLen, iLen, 1);

    env->ReleaseByteArrayElements(key_, key, 0);
    env->ReleaseByteArrayElements(iv_, iv, 0);
    env->ReleaseByteArrayElements(data_, data, 0);
    env->ReleaseByteArrayElements(outData_, outData, 0);
    env->ReleaseIntArrayElements(outLen_, outLen, 0);

    return result;
}
