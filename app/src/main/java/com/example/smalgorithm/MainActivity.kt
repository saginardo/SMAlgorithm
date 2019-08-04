package com.example.smalgorithm

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    companion object {
        const val TAG = "MainActivity"
        val alg = SMAlgorithm()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = "Hello"

        //sm3()
        //sm4()
        //sm2()
        sm2DoPoint()
    }

    private fun sm2DoPoint() {
        var workKey1 = ByteArray(64)
        var workKey2 = ByteArray(64)
        var pubKey1 = ByteUtil.hexToByte("D1BE2797309ED8FC6D3FC834A9E928D5D55D0B20D05C9A1217B663CAFFF737BDB61159CEE6EF6B288FAF651231A93D19C8DBF27ECDB6DB1888A7331D53F541D1")
        var priKey1 = ByteUtil.hexToByte("75AB23E1D7DD58E8FFBF92715DCEC90F7EEFCDFCFFB926F3FF6357D267FCB772")

        var pubKey2 = ByteUtil.hexToByte("22FBBADED50591A3DF827E55E2A6B9A2A51F4F5AC0CC04C2C46DE4667962A1B029159779591051EAF2CAD426D2263D7595E16154A158711C3E101FFDA0030FE8")
        var priKey2 = ByteUtil.hexToByte("5BDA2A7FFF7F7996EE7FFEA9FEBBFD1FEFBE1D947DDD4CC66CFF30CF7EFDB215")


        alg.DotProduct(workKey1, pubKey2, priKey1)
        alg.DotProduct(workKey2, pubKey1, priKey2)

        if(workKey1.contentEquals(workKey2)){
            Log.i(TAG, "DoPoint result is same.")
        }


    }

    private fun sm2(){
        alg.SM2Init()

        var priKey = ByteArray(32)
        var pubKey = ByteArray(64)

        var priKeyLen = intArrayOf(32)
        var pubKeyLen = intArrayOf(64)
        alg.SM2GenKey(priKey, priKeyLen, pubKey, pubKeyLen)
        Log.i(TAG,"priKey is : ${ByteUtil.byteToHex(priKey)}")
        Log.i(TAG,"pubKey is : ${ByteUtil.byteToHex(pubKey)}")

        //9BF6E46DDD4E732ABFB73394FCB3DC24555EA96B7B962AC57ED75429F9FF2460
        //43BFC47FE048AE70336AE3FE1AC2CD7C0399C825661156BDF19C1C4DE1A3FAC5D6A4A51D0B4189080287CBB680B0F0BCBD7D579A4ABD7CBBAB9EAC6C3C30CD0E

        /*
        c_pk: B9294D08AB2F49121B51986CE324122B21EBE9E415786B7BFAF1B7012195B0A25C1818BD34DDC8F89B0CFA1D25EE507FD9EC951D5CADBD64040F1B4008883C5E
        hash_c_pk: 0F7D6FA5ADEF9A1C61D2F1830F24CEC1DEBBCCC62341FF88DC220DB3BB084110
        c_sk: 30AFB913516EF437368D5C914CE07647EBCE264522A3924500C41BD101DD9EF9
        csign: 14182612F82322D4FDBAF65F71B0DF122AE27AB81AA3A7BE338735C228A5EB63E99A0DEA46B7C59F80CDF2F0684DF2B2CD03D33EED2CAA217C6630A4BE8AF1E3
         */


        var priKey1 = ByteUtil.hexToByte("DEFBFFEE6FE98378FF36FE87FDFEB0156AA9A1536FF64CB17D5FC6E2C7F92A70")
        var pubKey1 = ByteUtil.hexToByte("1343391DDA29AEFEB1BD0F990C1883718233C0BD0691FE30EF6BBF8A6C213486CBB2595B34FB6195001FE055C9EDB4464D97641743E966457656D25C837FD441")
        var data = ByteUtil.hexToByte("7FE534FD4EE5C6A26779453F47C33EAE74D35953FEAF7ECBFF672571DF7B81A3")

        var sign = ByteArray(64)
        var signLen = intArrayOf(64)

        var rst0 = alg.SM2SignHash(data, data.size, priKey1, priKey1.size, sign, signLen)
        Log.i(TAG,"rst is $rst0, sign is : ${ByteUtil.byteToHex(sign)}")

        var sign_c = ByteUtil.hexToByte("69033627832BE451DD8521E8681FAE9EF0F7158718570271DBA9929B8B12B2466A9E541FA7B727CF720B02BA21E49784C4DADFCF28C91E60A6A911FCCE386633")
        var rst = alg.SM2VerifyHash(data, data.size, pubKey1, pubKey1.size, sign_c, sign_c.size)
        Log.i(TAG,"verify sign result is : $rst")

        var data2 = ByteUtil.hexToByte("B9294D08AB2F49121B51986CE324122B21EBE9E415786B7BFAF1B7012195B0A25C1818BD34DDC8F89B0CFA1D25EE507FD9EC951D5CADBD64040F1B4008883C5E")
        var hashData = ByteArray(32)
        alg.sm3(data2,data2.size,hashData)
        Log.i(TAG, "public key hash data: " +ByteUtil.byteToHex(hashData))

        var sign2 = ByteUtil.hexToByte("14182612F82322D4FDBAF65F71B0DF122AE27AB81AA3A7BE338735C228A5EB63E99A0DEA46B7C59F80CDF2F0684DF2B2CD03D33EED2CAA217C6630A4BE8AF1E3")
        var pubkey2 = ByteUtil.hexToByte("B9294D08AB2F49121B51986CE324122B21EBE9E415786B7BFAF1B7012195B0A25C1818BD34DDC8F89B0CFA1D25EE507FD9EC951D5CADBD64040F1B4008883C5E")
        var rst2 = alg.SM2VerifyHash(hashData, hashData.size, pubkey2, pubkey2.size, sign2, sign2.size)
        Log.i(TAG,"verify sign 2 result is : $rst2")
    }

    private fun sm4() {

        //011D2D14836B72CC1870F5B5B8F50A78F07828E6F076156A775A48E10A7113AEEB3D63D29BF4C8365CBA38CEE5AA41BE0AD0B77971BFC80F8121276E808028B7C17DB3F7513AEC10068A9270BF674BACD04E981B6D74C0B9B1F0FF67F14D2C758FDCE84F06332FC34BC62C5A826651F5
        //EEB320056859D0C86C9470D21E1D7A27

        //var random = Random()


        var bKey = ByteUtil.hexToByte("EEB320056859D0C86C9470D21E1D7A27")

        var bIv = ByteUtil.hexToByte("00000000000000000000000000000000")

        var bInputData = ByteUtil.hexStringToBytes("9BF6E46DDD4E732ABFB73394FCB3DC24555EA96B7B962AC57ED75429F9FF2460")

        //var bInputData = ByteArray(2048*1024) //2 MB
        //random.nextBytes(bInputData)

        var bOutData = ByteArray(bInputData.size)
        var bOutLen = IntArray(1)

        var start = System.currentTimeMillis()
        var result = alg.Mode_SMS4_encrypt(
            bKey,
            bKey.size,
            bIv,
            bInputData,
            bInputData.size,
            bOutData,
            bOutLen,
            SMAlgorithm.ALG_MODE_OFB
        )
        var end = System.currentTimeMillis()

        Log.i(TAG, "sm4 cbc encryption result is : $result, and time is ${end-start}")
        Log.i(TAG, "sm4 cbc encryption result is : $result, and hex is:  ${ByteUtil.byteToHex(bOutData)}")
        //Log.i(TAG, "sm4 cbc encryption result length  : ${bOutLen[0]}")

        var bPlainText = ByteArray(bInputData.size)
        var bPlainTextLen = IntArray(1)
        result = alg.Mode_SMS4_decrypt(
            bKey,
            bKey.size,
            bIv,
            bOutData,
            bOutData.size,
            bPlainText,
            bPlainTextLen,
            SMAlgorithm.ALG_MODE_OFB
        )
        Log.i(TAG, "sm4 cbc decryption result is : $result, and hex is:  ${ByteUtil.byteToHex(bPlainText)}")
        //Log.i(TAG, "sm4 cbc decryption result is : $result")
        //Log.i(TAG, "sm4 cbc decryption result length  : ${bPlainTextLen[0]}")
    }


    private fun sm3() {
        var inputData = "616263"
        var bInputData = ByteUtil.hexStringToBytes(inputData)
        var bOutputData = ByteArray(32)

        alg.sm3(bInputData, bInputData.size, bOutputData)
        //DEBE9FF92275B8A138604889C18E5A4D6FDB70E5387E5765293DCBA39C0C5732
        Log.i(TAG, "sm3 hash output : ${ByteUtil.byteToHex(bOutputData)}")

        var key = "EEB320056859D0C86C9470D21E1D7A27"
        var bKey = ByteUtil.hexStringToBytes(key)
        alg.sm3_hmac(bKey, bKey.size, bInputData, bInputData.size, bOutputData)
        Log.i(TAG, "sm3 hmac output : ${ByteUtil.byteToHex(bOutputData)}")
    }


    private fun padding(input:ByteArray):ByteArray{
        if(input.size%16!=0){
            val len = input.size + (16 - input.size%16)
            val output = ByteArray(len)
            System.arraycopy(input,0, output,0, input.size)
            return output
        }
        return input
    }

}
