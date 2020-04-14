#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define KEY_LENGTH 4 // Can be anything from 1 to 13

#define MIN_KEY_LENGTH 1
#define MAX_KEY_LENGTH 13
#define KEY_SPACE 256
#define ENGLISH_LETTER_FREQUENCY .065

int vigenereEncrypt();
int crackVigenere();


int main( void )
{
    //vigenereEncrypt();
    crackVigenere();

    return 0;
}

/*-----------------------------------------------------------------------------
-   Encrypt Plaintext using (Variant) Vigenere Cipher.
-
-   This function was given by assignment.
-
-    Parameters:
-        None
-
-    Return value: 0 or error code
-*/
int vigenereEncrypt() {
    unsigned char ch;
    FILE *fpIn, *fpOut;
    int i;

    // To confirm key
    unsigned char key[KEY_LENGTH] = {0x6C, 0x75, 0x6B, 0x65};

    fpIn = fopen("ptext.txt", "r");
    if (fpIn == NULL)
    {
        return 1;
    }

    fpOut = fopen("ctext.txt", "w");
    i=0;
    while (fscanf(fpIn, "%c", &ch) != EOF) {
        /* avoid encrypting newline characters */
        /* In a "real-world" implementation of the Vigenere cipher,
         every ASCII character in the plaintext would be encrypted.
         However, I want to avoid encrypting newlines here because
         it makes recovering the plaintext slightly more difficult... */
        /* ...and my goal is not to create "production-quality" code =) */
        if (ch!='\n')
        {
            fprintf(fpOut, "%02X", ch ^ key[i % KEY_LENGTH]); // ^ is logical XOR
            i++;
        }
    }

    fclose(fpIn);
    fclose(fpOut);

    return 0;
}



/*-----------------------------------------------------------------------------
-   Frequency analysis of lower case English letters appearing in the given stream.
-
-   Try decrypting the stream using every possible byte value B.
-       - If correct, a ll bytes in the P.T. will be between 32 and 127.
-       - The frequencies of lowercase ltters should be close to knwon English-letter frequencies
-           - Should find sum(p<sub>i</sub>q<sub>i</sub>) =~ sum (p<sub>i</sub><sup>2</sup>) =~ 0.065
-
-   Parameters:
-       repeat          -   the number of ciphertext bytes, encrypted by same key byte
-       groupedStream   -   re-ordered cipher stream (with offset)
-
-   Return value: frequency
-*/
double frequencyAnalysis(const size_t repeat, const unsigned char *groupedStream)
{
    size_t *frequency = malloc(sizeof(size_t) * KEY_SPACE);

    for (size_t i = 0; i < repeat; ++i)
    {
        frequency[groupedStream[i]] += 1;
    }

    size_t summation = 0;
    for (size_t i = 97; i < 122; ++i)
    {
        summation += frequency[i] * (frequency[i] - 1);
    }

    free(frequency);

    const size_t lowerCaseSize = KEY_SPACE;
    const double result = (double)summation / (lowerCaseSize * (lowerCaseSize - 1));

    return result;
}


/*-----------------------------------------------------------------------------
-   Returns the most suitable guess for the character in the key
-       based on a frequency analysis.
-
-   This function takes all the data encoded by the same character in the key
-
-   Parameters:
-       repeat          -   the number of ciphertext bytes, encrypted by same key byte
-       groupedStream   -   re-ordered cipher stream (with offset)
-
-   Return value: calculated key (one byte)
-*/
unsigned char calculateKey(const size_t repeat, const unsigned char *groupedStream) {

    unsigned char *shiftedStream = malloc(sizeof(unsigned char) * repeat);

    // frequency matrix to calculate all the possibilties of a key-byte over key space
    double frequencies[KEY_SPACE];
    memset(frequencies, 0x00, sizeof(size_t) * KEY_SPACE);

    // Try out all possibility of a key byte..
    for (unsigned char b = 0x00; b < 0xFF; ++b)
     {
        // flag to indicate the guess is valid
        size_t validGuess = 1;

        for (size_t j = 0; j < repeat; ++j)
        {
            shiftedStream[j] = groupedStream[j] ^ b;

            // When the guess 'b' is correct, all bytes in the plaintext
            // (ASCII values of the English alphabet, including punctuation)
            // This ranges from space(0x20) to z(0x7A)
            if ((shiftedStream[j] < 0x20) || (shiftedStream[j] > 0x7A))
            {
                validGuess = 0;
                break;
            }

            // These are characters that shouldn't appear in the plaintext (to narrow down)
            if ((shiftedStream[j] == 0x23 || // #
                 shiftedStream[j] == 0x24 || // $
                 shiftedStream[j] == 0x26 || // &
                 shiftedStream[j] == 0x2A || // *
                 shiftedStream[j] == 0x2B || // +
                 shiftedStream[j] == 0x5E || // ^
                 shiftedStream[j] == 0x5F || // _
                 shiftedStream[j] == 0x60 )) // `
            {
                validGuess = 0;
                break;
            }
        }

        // if guessed key looks valid, then do frequency analysis
        // otherwise, frequency will be 0
        if (validGuess)
        {
            frequencies[b] = frequencyAnalysis(repeat, shiftedStream);
        }
    }

    // find out maximum frequency
    double max = 0.;
    unsigned char key = 0x00;
    for (unsigned char b = 0x00; b < 0xFF; ++b)
    {
        if (max < frequencies[b])
        {
            max = frequencies[b];
            key = b;
        }
    }

    free(shiftedStream);

    return key;
}


/*-----------------------------------------------------------------------------
-   Find Key Length
-
-   It will return the most suitable guess for the length of the key based on a frequency analysis.
-
-   If the key length is N, every N^th character of the P.T is encrypted using same "shift"
-       - If take every N<sup>th</sup> character and calculate frequencies, we should get p<sub>i</sub>'s in permuted order
-       - If take every M<sup>th</sup>(not multiple of N) character and calculate frequencies, we should get something close to uniform
-
-   Compute some candidate distribution sum(q<sub>i</sub><sup>2</sup>). Try all possibilities for the key length, compute distribution and look for maximum value.
-       - If close to uniform, ~1/256
-       - If a permutation of p<sub>i</sub>, then much larger than 1/256
-
-   Parameters:
-       size        -   byte-size of ciphertext
-       pStream     -   cipher stream
-
-   Return value: Guessed key size
-*/
size_t findKeyLength(const size_t size, const unsigned char *cipherStream)
{

    unsigned char *stream = malloc(sizeof(unsigned char) * size);

    size_t *frequency = malloc(sizeof(size_t) * KEY_SPACE);
    double summations[MAX_KEY_LENGTH];
    memset(summations, 0, sizeof(double) * MAX_KEY_LENGTH);

    /* --- Make sure we are operating on valid key  --- */
    assert(MIN_KEY_LENGTH > 0);
    assert(MIN_KEY_LENGTH < MAX_KEY_LENGTH);

    /* --- So we have to try every possible key length  --- */
    for (size_t n = MIN_KEY_LENGTH; n <= MAX_KEY_LENGTH; ++n)
    {
        double averageSummation = 0.;

        // For each position in the key (k_i...k_n)
        for (size_t k = 0; k < n; ++k)
        {
            // reset stream and frequency
            memset(stream, 0x00, size);
            memset(frequency, 0, sizeof(size_t) * KEY_SPACE);

            size_t j = 0; // "j" will be the length of the stream
            for (size_t i = k; i < size; i += n)
            {
                // Start from the k_i position
                stream[j++] = cipherStream[i];
            }

            // For each position in stream, record the frequency of each byte
            for (size_t i = 0; i < j; ++i)
            {
                frequency[stream[i]] += 1;
            }

            size_t summation = 0;
            for (size_t i = 0; i < KEY_SPACE; ++i)
            {
                // Perhaps, reduce this loop to 65-127 (?)
                summation += frequency[i] * (frequency[i] - 1);
            }

            averageSummation += (double)summation / (j * (j - 1));
        }

        summations[n - 1] = averageSummation / n ;

        // There may be a certain threshold where we can break out of here with
        // a high degree of confidence (perhaps >0.06?) that we have obtained the key length.
    }

    double max = 0.;
    size_t keyLength = 0;
    for (size_t i = MIN_KEY_LENGTH - 1; i < MAX_KEY_LENGTH; ++i)
    {
        if (max < summations[i])
        {
            max = summations[i];
            keyLength = i + 1; // Add 1 to adjust for 0 based indexing.
        }
    }

    free(stream);
    free(frequency);

    return keyLength;
}


/*-----------------------------------------------------------------------------
-   Read ciphertext and determine byte-size of ciphertext
-
-   Parameters:
-       pOut     -   A pointer to hold ciphertext (byte/char array)
-
-   Return value: byte-size of ciphertext.
-*/
size_t readFile(unsigned char **pOut)
{

    // Open the ciphertext to decrypt
    FILE *cipherFile = fopen("ctext.txt", "r");

    if (cipherFile == NULL)
        return 0;


    /* --- Get the length of the file and set it back to the beginning --- */
    fseek(cipherFile, 0L, SEEK_END); // sets the position of stream to the offset 0L + EOF
    const size_t fileSize = ftell(cipherFile); // returns the current file position of the given stream
    rewind(cipherFile); // sets file position to the beginning of the file


    /* --- Read the entire file into allocated memory --- */
    unsigned char *rawData = malloc(sizeof(unsigned char) * fileSize);

    if (fread(rawData, sizeof(char), fileSize, cipherFile) != fileSize)
    {
        free(rawData);
        fclose(cipherFile);
        return 0;
    }
    fclose(cipherFile);

    /* --- Convert the data from HEX format to ASCII ---
        ex) 1F2F .. -> 0x1F 2F ..
    */
    const size_t size = fileSize / 2; // Divide by 2 since 1 hex value occupies 2 bytes
    unsigned char *cipherStream = malloc(sizeof(unsigned char) * size);

    size_t count = 0;
    for (size_t i = 0; i < fileSize; i += 2)
    {
        if (sscanf((char *)rawData + i, "%2hhX", &cipherStream[count++]) != 1)
            break;
    }

    if (count == size)
    {
        // Conversion to hex worked, so return the data
        free(rawData);
        *pOut = cipherStream;
        return size;
    } else
    {
        // File was not in hex, so return the raw data
        free(cipherStream);
        *pOut = rawData;
        return fileSize;
    }
}


/*-----------------------------------------------------------------------------
-   Attack the (variant) Vigenere cipher with following two steps:
-
-   - Step 1: Determine the key length (bytes in the key)
-   - Step 2: Determine (each byte of) the key
-
-   And print decrypted ciphertext
-
-   Parameters:
-       None     -   Mpme
-
-   Return value: 0 or error code
-*/
int crackVigenere()
{

    // A pointer hold ciphertext string
    unsigned char *cipherStream = NULL;

    /* --- STEP 1: Determine the key length (bytes in the key) --- */
    const size_t size = readFile(&cipherStream); // Determine length of ciphertext
    const size_t keyLength = findKeyLength(size, cipherStream); // Find key length by frequency analysis


    // keyMemorySize must account for size not evenly divided by keyLength
    const size_t keyMemorySize = (size / keyLength) + (size % keyLength);

    // Load the cipher text grouped by c_i where k_i was used as the shift
    /* stream will contain reordered ciphertext
        eg) C.T. :  0x23 0xAB 0xAF 0xCF 0XEF (5 bytes)
            Key  :   k1   k2   k1   k2   k1  (assume key is 2-byte length)
        Then, stream is 3*2 bytes long
            Stream:  (0x23, 0xAF, 0xEF), (0xAB 0xCF, - )
            groupLengths = ( 3, 2 )

    */
    const size_t streamSize = keyMemorySize * keyLength;
    unsigned char *stream = malloc(sizeof(unsigned char) * streamSize);

    // Length of each group of characters encoded by the same shift.

    size_t *groupLengths = malloc(sizeof(size_t) * keyLength);

    for (size_t n = 0; n < keyLength; ++n)
    {
        size_t j = keyMemorySize * n;
        size_t k = 0;
        for (size_t i = 0 + n; i < size; i += keyLength)
        {
            stream[j++] = cipherStream[i];
            k++;
        }

        // groupLength contains information about how many each k^i should be used for decryption
        groupLengths[n] = k;
    }

    /* --- STEP 2: Determine (each byte of) the key --- */
    unsigned char *key = calloc(keyLength, sizeof(unsigned char));
    for (size_t n = 0; n < keyLength; ++n)
    {
        // To find the each byte of the key, provide with the offset n*keyMemorySize...
        key[n] = calculateKey(groupLengths[n], stream + (n * keyMemorySize));
    }

    /* --- STEP 3: Decrypt text and print  --- */
    for (size_t count = 0; count < size; ++count)
    {
        fprintf(stderr, "%c", cipherStream[count] ^ key[count % keyLength]); // xor back
    }
    printf("\n");

    // free resources
    free(cipherStream);
    free(groupLengths);
    free(stream);
    free(key);

    return 0;
}