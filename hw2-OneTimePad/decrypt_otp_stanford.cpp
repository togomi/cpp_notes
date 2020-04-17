#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// function prototype
int crackOTP( const vector<string> &ciphertexts );


int main (void)
{
    // ciphertext given by programming assignment
    vector<string> ciphertexts = {  "315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd8883a7bc37520e06e515d22c954eba5025b8cc57ee59418ce7dc6bc41556bdb36bbca3e8774301fbcaa3b83b220809560987815f65286764703de0f3d524400a19b159610b11ef3e",
"234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf064bbde548b12b07df44ba7191d9606ef4081ffde5ad46a5069d9f7f543bedb9c861bf29c7e205132eda9382b0bc2c5c4b45f919cf3a9f1cb74151f6d551f4480c82b2cb24cc5b028aa76eb7b4ab24171ab3cdadb8356f",
"32510ba9a7b2bba9b8005d43a304b5714cc0bb0c8a34884dd91304b8ad40b62b07df44ba6e9d8a2368e51d04e0e7b207b70b9b8261112bacb6c866a232dfe257527dc29398f5f3251a0d47e503c66e935de81230b59b7afb5f41afa8d661cb",
"32510ba9aab2a8a4fd06414fb517b5605cc0aa0dc91a8908c2064ba8ad5ea06a029056f47a8ad3306ef5021eafe1ac01a81197847a5c68a1b78769a37bc8f4575432c198ccb4ef63590256e305cd3a9544ee4160ead45aef520489e7da7d835402bca670bda8eb775200b8dabbba246b130f040d8ec6447e2c767f3d30ed81ea2e4c1404e1315a1010e7229be6636aaa",
"3f561ba9adb4b6ebec54424ba317b564418fac0dd35f8c08d31a1fe9e24fe56808c213f17c81d9607cee021dafe1e001b21ade877a5e68bea88d61b93ac5ee0d562e8e9582f5ef375f0a4ae20ed86e935de81230b59b73fb4302cd95d770c65b40aaa065f2a5e33a5a0bb5dcaba43722130f042f8ec85b7c2070",
"32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd2061bbde24eb76a19d84aba34d8de287be84d07e7e9a30ee714979c7e1123a8bd9822a33ecaf512472e8e8f8db3f9635c1949e640c621854eba0d79eccf52ff111284b4cc61d11902aebc66f2b2e436434eacc0aba938220b084800c2ca4e693522643573b2c4ce35050b0cf774201f0fe52ac9f26d71b6cf61a711cc229f77ace7aa88a2f19983122b11be87a59c355d25f8e4",
"32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd90f1fa6ea5ba47b01c909ba7696cf606ef40c04afe1ac0aa8148dd066592ded9f8774b529c7ea125d298e8883f5e9305f4b44f915cb2bd05af51373fd9b4af511039fa2d96f83414aaaf261bda2e97b170fb5cce2a53e675c154c0d9681596934777e2275b381ce2e40582afe67650b13e72287ff2270abcf73bb028932836fbdecfecee0a3b894473c1bbeb6b4913a536ce4f9b13f1efff71ea313c8661dd9a4ce",
"315c4eeaa8b5f8bffd11155ea506b56041c6a00c8a08854dd21a4bbde54ce56801d943ba708b8a3574f40c00fff9e00fa1439fd0654327a3bfc860b92f89ee04132ecb9298f5fd2d5e4b45e40ecc3b9d59e9417df7c95bba410e9aa2ca24c5474da2f276baa3ac325918b2daada43d6712150441c2e04f6565517f317da9d3",
"271946f9bbb2aeadec111841a81abc300ecaa01bd8069d5cc91005e9fe4aad6e04d513e96d99de2569bc5e50eeeca709b50a8a987f4264edb6896fb537d0a716132ddc938fb0f836480e06ed0fcd6e9759f40462f9cf57f4564186a2c1778f1543efa270bda5e933421cbe88a4a52222190f471e9bd15f652b653b7071aec59a2705081ffe72651d08f822c9ed6d76e48b63ab15d0208573a7eef027",
"466d06ece998b7a2fb1d464fed2ced7641ddaa3cc31c9941cf110abbf409ed39598005b3399ccfafb61d0315fca0a314be138a9f32503bedac8067f03adbf3575c3b8edc9ba7f537530541ab0f9f3cd04ff50d66f1d559ba520e89a2cb2a83",
"32510ba9babebbbefd001547a810e67149caee11d945cd7fc81a05e9f85aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde9e77472dbff89d71b57bddef121336cb85ccb8f3315f4b52e301d16e9f52f904"
    };

    crackOTP(ciphertexts);

    return 0;

}

/*-----------------------------------------------------------------------------
-   Convert ciphertext to vector of characters
-
-    Parameters:
-        ciphertexts    -  string vector of ciphertexts to decrypt
-
-    Return value: 0 or error code
-*/
int convert(char ch)
{
    if(ch >= '0' && ch <= '9')
        return ch-'0';
    else if(ch >= 'A' && ch <= 'F')
        return ch-'A'+10;
    else if(ch >= 'a' && ch <= 'f')
        return ch-'a'+10;
    else
    {
        cout << "Input ciphertext does not contain valid character!" << endl;
        exit(1);
    }
}

/*-----------------------------------------------------------------------------
-   Crack Multi-Time-Pad
-
-    Parameters:
-        ciphertexts    -  string vector of ciphertexts to decrypt
-
-    Return value: 0 or error code
-*/
int crackOTP( const vector<string> &ciphertexts )
{

    /* ********************************************************************
        This part consists of finding out length of given ciphertexts
    **********************************************************************/

    // number of given ciphertexts
    size_t numCiphers = ciphertexts.size();

    // length of the longest ciphertexts
    size_t maxLenCipher = 0;
    size_t minLenCipher = 0;

    // find minimum and maximum length ciphertext
    for(size_t i=0; i<numCiphers; i++)
    {
        if(minLenCipher == 0)
        {
            // start with 1st ciphertext length
            minLenCipher = ciphertexts[i].size();
        }

        // determine maximum length
        if(ciphertexts[i].size() > maxLenCipher)
            maxLenCipher = ciphertexts[i].size();

        // determine maximum length
        if(ciphertexts[i].size() < minLenCipher)
            minLenCipher = ciphertexts[i].size();
    }
    cout << "Min length: " << minLenCipher << endl;
    cout << "Max length: " << maxLenCipher << endl << endl;


    /* ********************************************************************
        Now convert HEX string in to HEX value(byte array) vector.
    **********************************************************************/

    // length of maximum ciphertexts (byte)
    size_t lenCipher = maxLenCipher/2;

    // covert to byte vectors "ciphers"
    // ex. FF012F -> 0xFF, 0x01, 0x2F
    vector<vector<int>> ciphers(numCiphers, vector<int> (lenCipher, 0));

    for(size_t i=0; i<numCiphers; i++)
    {
        // to compare with original hex string
//        cout << ciphertexts[i] << endl;

        for(size_t j=0; j<(ciphertexts[i].size())/2; j++)
        {
            int ch = convert(ciphertexts[i][2*j])*0x10 + convert(ciphertexts[i][2*j+1]);
            ciphers[i][j] = ch;

//            cout << setfill('0') << setw(2) << hex /*<< uppercase*/ << (int) ciphers[i][j];
        }
//        cout << endl << endl;
    }

    cout << endl;


    /* ********************************************************************
        For j^th position, try XOR-ing every combination.
    **********************************************************************/

    // XOR ciphers in the same position, count space
    vector<vector<int>> countSpace(numCiphers, vector<int> (lenCipher, 0));

    // for each j^th byte position..
    for(size_t j=0; j<lenCipher; j++)
    {
        // XOR every combination
        for(size_t i=0; i<numCiphers; i++)
        {
            int sum = 0;
            int c =  ciphers[i][j];

            for(size_t k=0; k<numCiphers; k++)
            {
                // skip XOR-ing itself
                if( i==k )
                    continue;

                // case of letter^space; XOR value > 0x40 = 0b0100_0000
                if( (c ^ ciphers[k][j]) > 0x40)
                    sum++;
            }
            countSpace[i][j] = sum;
        }
    }

/*
    cout << "---------------------------------------------------------------" << endl;
    cout << "Each number represents number of times it XOR to produce space" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for(size_t i=0; i<numCiphers; i++)
    {
        for(size_t j=0; j<lenCipher; j++)
        {
            cout << setfill('0') << setw(2) << uppercase << (int) ciphers[i][j] << ".";
        }
        cout << "  <- " << "cipher " << i << endl;
        for(size_t j=0; j<lenCipher; j++)
        {
            cout << setfill('0') << setw(2) << uppercase << (int) countSpace[i][j] << ".";
        }
        cout << "  <- " << "count for cipher " << i << endl << endl;
    }
    cout << "---------------------------------------------------------------" << endl;
*/

    /* ********************************************************************
        For j^th position, find the key by finding the index having valid maximum XOR count.
    **********************************************************************/

    // Determine OTP key for each i^th byte
    vector<int> keys(lenCipher, -1);

    // choose index that gives the maximum countSpace
    for(size_t j=0; j<lenCipher; j++)
    {
        int index = 0;
        int max = 0;

        for(size_t i=0; i<numCiphers; i++)
        {
            if(countSpace[i][j] > max)
            {
                max = countSpace[i][j];
                index = i;
            }
        }
//        cout << setfill('0') << setw(2) << index << ".";

        if(max>0)
        {
            keys[j] = (' ' ^ ciphers[index][j]);
        }

    }
/*
    cout << "  <- index having the highest count" << endl;
    cout << "---------------------------------------------------------------" << endl << endl;
*/


    cout << "---------------------------------------------------------------" << endl;
    cout << "First, Lets see the guessed key"                                 << endl;
    cout << "---------------------------------------------------------------" << endl;

    for(size_t i=0; i<lenCipher; i++)
    {
        cout << setfill('0') << setw(2) << uppercase << hex << (int) keys[i] << ".";
    }
    cout << endl;


    cout << "---------------------------------------------------------------" << endl << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Lets see the decryped message using guessed key"                 << endl;
    cout << "---------------------------------------------------------------" << endl;

    // decrypt if space ciphertext (key) is finalized.
    for(size_t i=0; i<numCiphers; i++)
    {
        cout << "[" << setfill('0') << setw(2) << dec << i << "]: ";
        for(size_t j=0; j<(ciphertexts[i].size())/2; j++)
        {
            if( keys[j] != -1 )
            {
                int c = keys[j] ^ ciphers[i][j];
                cout << (char) c;
            }else
            {
                cout << '*';
            }
        }
        cout << endl;
    }

    cout << "---------------------------------------------------------------" << endl << endl;



    /* ********************************************************************
        Unset key if the decrypted text is un-readable .
    **********************************************************************/

    cout << "---------------------------------------------------------------" << endl;
    cout << "Unset key if the decrypted text is not readable"                 << endl;
    cout << "---------------------------------------------------------------" << endl;

    // for each j^th byte position..
    for(size_t j=0; j<minLenCipher; j++)
    {
        // skip if key is not determined
        if(keys[j] == -1) continue;

        // set key to be not determined if text is unreadable
        for(size_t i=0; i<numCiphers; i++)
        {
            int c = keys[j] ^ ciphers[i][j];
            if( c < 0x20 || c > 0x7E )
            {
                keys[j] = -1;
                break;
            }
        }
    }

    for(size_t i=0; i<lenCipher; i++)
    {
        cout << setfill('0') << setw(2) << uppercase << hex << (int) keys[i] << ".";
    }
    cout << endl << endl;


    cout << "---------------------------------------------------------------" << endl;
    cout << "Removed unreadable part"                                          << endl;
    cout << "---------------------------------------------------------------" << endl;

    // decrypt if space ciphertext (key) is finalized.
    for(size_t i=0; i<numCiphers; i++)
    {
        cout << "[" << setfill('0') << setw(2) << dec << i << "]: ";
        for(size_t j=0; j<(ciphertexts[i].size())/2; j++)
        {
            if( keys[j] != -1 )
            {
                int c = keys[j] ^ ciphers[i][j];
                cout << (char) c;
            }else
            {
                cout << '*';
            }
        }
        cout << endl;
    }

    cout << "---------------------------------------------------------------" << endl << endl;


    /* ********************************************************************
        Guess keys to make all ciphertexts readable .
    **********************************************************************/
    cout << "---------------------------------------------------------------" << endl;
    cout << "Corrected Keys..."                                               << endl;
    cout << "---------------------------------------------------------------" << endl;

    keys = {0x66, 0x39, 0x6e, 0x89, 0xc9, 0xdb, 0xd8, 0xcc, 0x98, 0x74, 0x35, 0x2a, 0xcd, 0x63, 0x95, 0x10, 0x2e, 0xaf, 0xce, 0x78, \
            0xaa, 0x7f, 0xed, 0x28, 0xa0, 0x7f, 0x6b, 0xc9, 0x8d, 0x29, 0xc5, 0x0b, 0x69, 0xb0, 0x33, 0x9a, 0x19, 0xf8, 0xaa, 0x40, \
            0x1a, 0x9c, 0x6d, 0x70, 0x8f, 0x80, 0xc0, 0x66, 0xc7, 0x63, 0xfe, 0xf0, 0x12, 0x31, 0x48, 0xcd, 0xd8, 0xe8, 0x02, 0xd0, \
            0x5b, 0xa9, 0x87, 0x77, 0x33, 0x5d, 0xae, 0xfc, 0xec, 0xd5, 0x9c, 0x43, 0x3a, 0x6b, 0x26, 0x8b, 0x60, 0xbf, 0x4e, 0xf0, \
            0x3c, 0x9a, 0x61, 0x10, 0x98, 0xbb, 0x3e, 0x9a, 0x31, 0x61, 0xed, 0xc7, 0xb8, 0x04, 0xa3, 0x35, 0x22, 0xcf, 0xd2, 0x02, \
            0xd2, 0xc6, 0x8c, 0x57, 0x37, 0x6e, 0xdb, 0xa8, 0xc2, 0xca, 0x50, 0x02, 0x7c, 0x61, 0x24, 0x6c, 0xe2, 0xa1, 0x2b, 0x0c, \
            0x45, 0x02, 0x17, 0x50, 0x10, 0xc0, 0xa1, 0xba, 0x46, 0x25, 0x78, 0x6d, 0x91, 0x11, 0x00, 0x79, 0x7d, 0x8a, 0x47, 0xe9, \
            0x8b, 0x02, 0x04, 0xc4, 0xef, 0x06, 0xc8, 0x67, 0xa9, 0x50, 0xf1, 0x1a, 0xc9, 0x89, 0xde, 0xa8, 0x8f, 0xd1, 0xdb, 0xf1, \
            0x67, 0x48, 0x74, 0x9e, 0xd4, 0xc6, 0xf4, 0x5b, 0x38, 0x4c, 0x9d, 0x96, 0xc4};

    // keys: "66396e89c9dbd8cc9874352acd6395102eafce78aa7fed28a07f6bc98d29c50b69b0339a19f8aa401a9c6d708f80c066c763fef0123148cdd8e802d05ba98777335daefcecd59c433a6b268b60bf4ef03c9a611098bb3e9a3161edc7b804a33522cfd202d2c68c57376edba8c2ca50027c61246ce2a12b0c4502175010c0a1ba4625786d911100797d8a47e98b0204c4ef06c867a950f11ac989dea88fd1dbf16748749ed4c6f45b384c9d96c4"

    for(size_t i=0; i<lenCipher; i++)
    {
        cout << setfill('0') << setw(2) << uppercase << hex << (int) keys[i] << ".";
    }
    cout << endl;
    cout << "---------------------------------------------------------------" << endl << endl;

    // decrypt if space ciphertext (key) is finalized.
    for(size_t i=0; i<numCiphers; i++)
    {
        cout << "[" << setfill('0') << setw(2) << dec << i << "]: ";
        for(size_t j=0; j<(ciphertexts[i].size())/2; j++)
        {
            if( keys[j] != -1 )
            {
                int c = keys[j] ^ ciphers[i][j];
                cout << (char) c;
            }else
            {
                cout << '*';
            }
        }
        cout << endl;
    }

    cout << "---------------------------------------------------------------" << endl << endl;

    return 0;
}
