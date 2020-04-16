#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function prototype
int crackOTP( const vector<string> &ciphertexts );


int main (void)
{
    // ciphertext given by programming assignment
    vector<string> ciphertexts = {  "BB3A65F6F0034FA957F6A767699CE7FABA855AFB4F2B520AEAD612944A801E",
                                    "BA7F24F2A35357A05CB8A16762C5A6AAAC924AE6447F0608A3D11388569A1E",
                                    "A67261BBB30651BA5CF6BA297ED0E7B4E9894AA95E300247F0C0028F409A1E",
                                    "A57261F5F0004BA74CF4AA2979D9A6B7AC854DA95E305203EC8515954C9D0F",
                                    "BB3A70F3B91D48E84DF0AB702ECFEEB5BC8C5DA94C301E0BECD241954C831E",
                                    "A6726DE8F01A50E849EDBC6C7C9CF2B2A88E19FD423E0647ECCB04DD4C9D1E",
                                    "BC7570BBBF1D46E85AF9AA6C7A9CEFA9E9825CFD5E3A0047F7CD009305A71E" };

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
    if(ch >= '0' && ch <= '9') return ch-'0';
    else return ch-'A'+10;
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
    // lengths of all ciphertexts are equal
    size_t numCiphers = ciphertexts.size();
    size_t lenCipher = ciphertexts[0].size();

    // covert to character vectors "ciphers"
    // ex. FF012F -> 0xFF, 0x01, 0x2F
    vector<vector<int>> ciphers(numCiphers, vector<int> ((int)lenCipher/2, 0));
    for(size_t j=0; j<lenCipher; j+=2)
    {
        for(size_t i=0; i<numCiphers; i++)
        {
            int ch = convert(ciphertexts[i][j])*0x10 + convert(ciphertexts[i][j+1]);
            ciphers[i][j/2] = ch;
        }
    }

    // XOR ciphers in the same position, count space
    vector<vector<int>> countSpace(numCiphers, vector<int> ((int)lenCipher/2, 0));

    // for each j^th byte position..
    for(size_t j=0; j<lenCipher/2; j++)
    {
        // XOR every combination
        for(size_t i=0; i<numCiphers; i++)
        {
            int sum = 0;
            int c = ciphers[i][j];
            for(size_t k=0; k<numCiphers; k++)
            {
                // double count to ensure it's counted for next element
                if(i==k) continue;
                // case of letter^space; XOR value > 0x40 = 0b0100_0000
                if( (c ^ ciphers[k][j]) > 0x40)
                    sum++;
            }
            countSpace[i][j] = sum;
        }
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "Each number represents number of times it XOR to produce space" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for(size_t i=0; i<numCiphers; i++)
    {
        for(size_t j=0; j<lenCipher/2; j++)
        {
            cout << countSpace[i][j] ;
        }
        cout << endl;
    }
    cout << "---------------------------------------------------------------" << endl;

    // Determine OTP key for each i^th byte
    vector<int> keys((int)lenCipher/2, -1);

    // choose index that gives the maximum countSpace
    for(size_t j=0; j<lenCipher/2; j++)
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
        cout << index;

        if(max>0)
            keys[j] = (' ' ^ ciphers[index][j]);
    }
    cout << "  <- index having the highest count" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // decrypt if space ciphertext (key) is finalized.
    for(size_t i=0; i<numCiphers; i++)
    {
        for(size_t j=0; j<lenCipher/2; j++)
        {
            // if found the key using the space
            if(keys[j] >= 0)
            {
                char c = keys[j] ^ ciphers[i][j];
                cout << c;
            }else
            {
                cout << '*';
            }
        }
        cout << endl;
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "Guessed rest of the keys from roughly decrypted text" << endl;
    keys[0] = 'T' ^ ciphers[5][0];
    keys[6] = 'k' ^ ciphers[4][6];
    keys[8] = 'e' ^ ciphers[2][8];
    keys[10] = 'i' ^ ciphers[0][10];
    keys[17] = 'e' ^ ciphers[0][17];
    keys[20] = 'e' ^ ciphers[0][20];
    keys[29] = 'n' ^ ciphers[0][29];
    keys[30] = '.' ^ ciphers[0][30];
    cout << "---------------------------------------------------------------" << endl;

    // decrypt rest of the ciphertexts
    for(size_t i=0; i<numCiphers; i++)
    {
        for(size_t j=0; j<lenCipher/2; j++)
        {
            // if found the key using the space
            if(keys[j] >= 0)
            {
                char c = keys[j] ^ ciphers[i][j];
                cout << c;
            }else
            {
                cout << '*';
            }
        }
        cout << endl;
    }
    return 0;
}
