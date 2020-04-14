# Introduction
        
## **Classical Cryptography**
- Relied exclusive on secret information (a key) shared between the communicating parties

### **Private Key Cryptography**
- AKA secret-key, shared-key, symmetric-key cryptography
- Eg. save encrypted contexts in personal laptop. 
- A private-key encryption scheme is defined by a message space __M__ and algorithms (Gen, Enc, Dec):
    - Gen (Key-generation algorithm): generates _k_
    - Enc (Encryption algorithm algorithm): c <- Enc<sub>k</sub>(m)
        - takes key _k_ and message _m_ in __M__ as input 
        - outputs ciphertext _c_
    - Dec (Decryption algorithm): m:=Dec<sub>k</sub>(c)
        - takes key k and ciphertext c as input
        - outputs m or "error"

- For all m in M and k output by Gen,</br>
    &nbsp;&nbsp; Dec<sub>k</sub>(Enc<sub>k</sub>(m)) = m

================================================
### **Historical Encryption Scheme**

#### Shift Ciphers
- Shift Cipher: shift every letter of the plantext by k positions
    - M = {strings over lowercase English Alphabet}
    - Gen: choose uniform _k_ in {0,...,25}
    - Enc<sub>k</sub>(m<sub>1</sub>...m<sub>t</sub>):= c<sub>1</sub>...c<sub>t</sub>, where c<sub>i</sub> := [m<sub>i</sub> + _k_ mod 26]
    - Dec<sub>k</sub>(c<sub>1</sub>...c<sub>t</sub>):= m<sub>1</sub>...m<sub>t</sub>, where m<sub>i</sub> := [c<sub>i</sub> - _k_ mod 26] 
    
- Is it Secure?
    - No, because only 26 possible keys


#### Kerckhoffs's Principle
- Encryption scheme is not secret
    - The only secret is the key
    - The key must be chosen at random, kept secret

#### Sufficient Key Space Principle
- The __key space__ should be large enough to prevent "brute-force", exhaustive search attacks.
- But this does not guarantee secrecy.

#### Vigenere Cipher
- Key is now a string, not just a character
- Size of key space?
    - If keys are 14-character strings, the key space has size 26<sup>14</sup> ~ 2<sup>66</sup>
    - Brute-force search expensive/impossible

- Is it Secured?
    - No.
    - Attacking the Vengenere Cipher (a way)
        - Assume a 14-character key.
        - Observe that every 14<sup>th</sup> character is "encrypted" using the same shift.
        - Using plaintext letter frequencies
            - eg. e is the most commonly used letter in plaintext
        - Guess the first character of the key is (alpha - 'e') and repeat
        
================================================
### **Perfect Secrecy**


## HEX and ASCII
