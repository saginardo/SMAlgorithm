package com.example.smalgorithm

class SMAlgorithm {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("SMAlgorithm-lib")
        }

        const val SM3_KEY_LEN_ERROR = 10

        const val SM4_KEY_LEN_ERROR = 12
        const val SM4_INPUT_IS_NULL = 13
        const val SM4_CBC_LEN_ERROR = 14

        const val SM2_PUBLIC_KEY_LEN_ERROR = 15
        const val SM2_PRIVATE_KEY_LEN_ERROR = 16
        const val SM2_SIGN_LEN_ERROR = 17

        const val SM2_PRIVATE_KEY_LEN = 32
        const val SM2_PUBLIC_KEY_LEN = 64
        const val SM2_SIGN_LEN = 64
        const val SM3_KEY_LEN = 32

        const val ALG_MODE_CBC = 0x01
        const val ALG_MODE_OFB = 0x02
    }

    external fun SM2Init()
    external fun SM2GenKey(
        priKey: ByteArray,
        priKeyLen: IntArray,
        pubKey: ByteArray,
        pubKeyLen: IntArray
    ): Int

    external fun SM2SignHash(
        hash: ByteArray,
        iHashLen: Int,
        priKey: ByteArray,
        iPriKeyLen: Int,
        sign: ByteArray,
        piSignLen: IntArray
    ): Int

    external fun SM2VerifyHash(
        hash: ByteArray,
        iHashLen: Int,
        pubKey: ByteArray,
        iPubKeyLen: Int,
        sign: ByteArray,
        iSignLen: Int
    ): Int

    external fun DotProduct(workKey: ByteArray, pubKey: ByteArray, priKey: ByteArray)

    external fun sm3(input: ByteArray, iLen: Int, output: ByteArray)
    external fun sm3_hmac(key: ByteArray, keyLen: Int, input: ByteArray, iLen: Int, output: ByteArray)
    external fun Mode_SMS4_encrypt(
        key: ByteArray,
        keyLen: Int,
        iv: ByteArray,
        input: ByteArray,
        iLen: Int,
        output: ByteArray,
        oLen: IntArray,
        mode: Int
    ): Int

    external fun Mode_SMS4_decrypt(
        key: ByteArray,
        keyLen: Int,
        iv: ByteArray,
        input: ByteArray,
        iLen: Int,
        output: ByteArray,
        oLen: IntArray,
        mode: Int
    ): Int
    
}