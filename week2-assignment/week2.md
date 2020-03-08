\*\* Week 2

\*\*\* [[https://class.coursera.org/crypto-007/lecture/12][what are block ciphers? (17 min)]]

- Block ciphers:
  - The E,D cipher takes a key (k-bits), a n-bit length PT block, and returns a
    n-bit (same length) CT block.
  - Canonical examples:
    - 1. 3DES: n=64bits, k=168bits
    - 2. AES: n=128bits, k=128, 192, 256bits
  - Block ciphers are build by iteration. The key k is expanded into
    'round keys' k1, k2, ... kn. The message m is then encoded using R
    that stands for round function, which takes one of the round keys,
    and the current state of the message /mi/. This sequence of steps
    is applied iteratively until we reach /kn/, and the concatenation
    of the output of R is our cipher text.
  - Different ciphers have different amount of rounds. For 3DES it's
    48, and for AES-128 it is 10.
  - Block ciphers are rather slow compared to stream ciphers. The
    longer the key, the slower they are. However we can do many things
    with block ciphers that we couldn't do with stream ciphers.
  - Abstract: PRPs (Pseudo Random Purmutation) and PRFs (Pseudo Random
    Function): - Pseudo Random Function is defined over a key-space K,
    input-space X and output-space Y: F: K _ X -> Y, such that there
    exists "efficient" algorithm to evaluate F(k,x). - Pseudo Random Permutations are defined over K (key-space) and X
    (set X): E: K _ X -> X,
    such that: - 1) There exists "efficient" deterministic algorithm to
    evaluate E(k,x) - 2) The function E(k,⋅) is one-to-one - 3) There exists "efficient" inversion algorithm D(k,y) - PRP can be used interchangably with the term 'block cipher' - Example PRPs: 3DES, AES, ...: - AES: K _ X -> X, where K = X = {0,1}^128 - 3DES: K _ X -> X, where X = {0,1}^64, K = {0,1}^168 - Fuectionally, any PRP is also a PRF. A PRP is a PRF where X=Y
    and is efficiently invertible. - Secure PRFs: - Let F: K \* X -> Y be a PRF - Let Funs[X,Y] be the set of all functions from X to Y (really big) - Sf = { F(k,⋅), such that k ∈ K } ⊆ Funs[X,Y], or in other
    words Sf is a set of functions that were curried with k, which
    is a subset of the set of all functions (that take X and
    output Y) - Intuition: we can say that PRF is secure if a random function
    in Funs[X,Y] is indistinguishable from a random function in Sf. - An easy application PRF => PRG: - Let F: K x {0,1}^n -> {0,1}^n be a secure PRF. Then G: K ->
    {0,1}^nt is a secure PRG: - G(k) = F(k,0) || F(k,1) || ... || F(k,t) - This process should be parallelizable - The security of G follows from the property of PRF.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/13][the data encryption standard (22 min)]]
- In order to describe how a specific block cipher works, we need to
  specify how its Key Expansion and Round Function works
- The Data Encryption Standard:
  - Based on an earlier standard called Lucifer, developed by a man
    called Horst Feistel at IBM.
  - Lucifer had key-length of 128 bits and a block length of 128 bits
  - The modified version that was adopted by NBS, now called DES, has
    a key length of 56 bits and a block length of 64 bits.
  - Limiting the key length to only 56 bits came back to bite DES in
    the ass, as it is vulnerable to an exhaustive search.
  - Broken in 1997
  - NIST (new NBS) adopts Rijndael as AES to replace DES.
  - Widely used in banking and commerce
- DES: core-idea: Feistel Network:
  - Given functions f_1, ..., f_d: {0,1}^n -> {0,1}^n that are
    arbitraty functions, that is, they don't have to be reversible, we
    want to build an invertible function F: {0,1}^2n -> {0,1}^2n
  - Feistel network is a series of steps that follow the structure:
    - We start with R_0 for the first Right Bit, L_0 for the first
      Left Bit, and f_1 for the first function.
    - We get L_1 from applying f_1 to R_1, and R_1 from XOR'ing L_0
      with the output of f_1(R_0).
    - We keep applying the same process until we reach R_d-1, L_d-1
      and fd, and the output of the process (the function F) is Rd and Ld.
    - We claim that for all arbitrary functions f_1 to f_d, the
      outlined functiond F is invertible.
    - We can proove this by constructing the inverse of the process:
      - The inverse of one round of input is:
        - R_i = L_i+1, L_i = f_i+1(L_i+1) XOR R_i+1
      - By repeating this step from d to 0, we have completed the inverse.
      - Because the process is so similar, this is very attractive
        because the hardware that encrypts can be used for decrypting.
    - Used in many block ciphers, although not in AES.
  - Theorem (Luby-Rackoff '85):
    - If f: K x {0,1}^n -> {0,1}^n is a secure PRF, then:
    - 3-round Feistel F: K^3 x {0,1}^2n -> {0,1}^2n is a secure PRP.
    - In other words, you end up with a inversible function that is
      truly indistinguishable from a truly random inversible function.
    - As you recall, the definition of a seceure block cipher is that
      it's a secure Pseudo Random Permutation.
  - DES is a 16 round Feistel network:
    - f_1, ..., f_16: {0,1}^32 -> {0,1}^32, f_i(x) = F(k_i, x), where
      k_i is the round key that we get from key expansion.
    - We start with a 64-bit input that gets fed into a Initial
      Permutation, that mixes the input bits around, this then gets
      fed into the 16-round Feistel network, which gets fed into Final
      Permutation that undoes the shuffling around of IP. We are left
      with a 64-bit output.
  - The function F(k_i, x):
    - Takes a 32-bit value and a 48-bit round key
    - x gets expanded into 48 bits by duplicating and mixing
    - This expanded x gets xor'ed with the round key
    - The resulting 48-bits are split into eight slots of 6-bits, that get
      fed into eight "S-boxes".
    - S-boxes spit out 4-bit values based on lookup tables
    - The resulting 32-bit value goes into yet another permutator,
      where it gets mixed and matched around.
    - Essentially by using different round keys, we get different,
      arbitrary round functions.
  - S-boxes: - There are good and bad versions of S-boxes. - Mainly we don't want the S-boxes to be calculated via a linear
    function, because this would mean that all that DES does is
    xor'ing and moving bits around. - If DES was wholly linear, this would mean that it's not fully random. - Choosing the S-boxes at random would not be enough to make them
    secure, as the chances of them being linear would be too high.
    The key could be recovered after about 2^24 outputs.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/14][exhaustive search attacks (20 min)]]
- Our goal: given a few input output pairs (m_i, c_i = E(k, m_i)), i =
  1, ..., 3, find key k. (m_1, m_2, m_3 -> c_1, c_2, c_3)
- Lemma: Suppose that DES is an ideal cipher (2^56 random invertible functions)
  - Then for all m, c; there is at most one key that satisfies c =
    DES(k,m), with prob. 1 >= 1 - 1/256 (99.5%)
  - For two DES pairs (m_1, c_1 = DES(k, m_1)), (m_2, c_2 = DES(k,
    m_2)), the probability is ~= 1 - 1/2^71
  - For AES-128: given two inp/out pairs, the probability is 1 - 1/2^128
  - When the probability is close to one, it is practical to use an
    Exhaustive Search attack
- A company called RSA published the DES challenge, where they
  published a number of cipher texts, of which three of them contained
  known plain text "The unknown message is: XXXXX", where XXXXX was an
  unknown part of the message.
  - The challenge was to find the key that maps m_i for c_i for i = 1,
    2, 3, where i = 1-3 is the known plain text divided into three parts
    (8-bits each)
  - In 1997 Internet search (I guess he just means connected machines?)
    could solve the challenge in three months
  - In 1998 EFF build a custom hardware machine called Deep Crack which
    solved the next iteration of the challenge in three days
  - In 1999 a combined search using the two methods solved the challenge
    in just 22 hours.
  - In 2006: COPACOBANA (120 FPGAs) that cost \$10k could solve it in 7 days
  - Result --> DES is completely broken by modern standards. 56 bit
    keys should not be used.
- What to do? Strenghening the DES:
  - Method 1: Triple-DES:
    - Instead of the usual E: K \* M -> C, we can use 3E: K^3 x M -> C
      where 3E((k1, k2, k3), m) = E(k1, D(k2, E(k3, m))).
    - If you set all three keys to be the same, using 3DES is the same
      as normal DES, although three times slower.
    - For 3DES: key-size = 3x56 = 168 bits.
    - Why not double DES? Because it's suspectible to a Meet In The Middle attack
      - We need to find k_1, k_2 such that E(k_1, E(k_2, M)) = C,
        which is the same as E(k_2, M) = D(k_1, C).
      - First we'll build a table that takes M, and encrypts it for
        all possible values of k_2 (56-bits). This takes time 2^56
        (for building) times log(2^56) (sorting)
      - Then we brute force k_1 and see if it matches any of the
        values in our table.
      - Running time for the attack: 2^56 + 2^56 \* log(2^56) < 2^63,
        which is much less than we'd expect from our original 2^112 key.
      - The same attack on 3DES reduces the time from 2^168 to 2^118.
    - Method 2: DESX:
      - Define EX -> EX((k_1, k_2, k_3), m) = k_1 XOR E(k_2, m XOR k_3)
      - Key-length for DESX is 184 bits, but easy attack time is
        2^(64+56) = 2^120.
  - 3DES is a national standard.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/15][more attacks on block ciphers (16 min)]]
- You should never ever design your own block cipher.
- Attacks on the implementation:
  - Measuring time to do enc/dec
  - Measuring power for enc/dec
  - Fault attacks: If you can cause the hardware that
    decrypts/encrypts to malfunction (i.e. by heating), you might be
    able to get access to the cipher before the last round of the
    encryption process, and this can reveal the key.
- Linear and differential attacks:
  - Given many inp/out pairs, can we recover the key in time less than
    what exhaustive search would yield us.
  - If the attacker has the message, and the cipher text, and he XORs
    sub bits of the message together, and subsets of the cipher text
    together, does this reveal any information about the xors of the
    sub bits of the key?
    - For DES this exists with epsilon 1/2^21 ~= 0.0000000477
  - Pr[ m[i_1] xor ... xor m[i_r] XOR c[j_j] xor ... xor c[j_v] =
    k[l_1] xor ... xor k[l_u] ] = 1/2 + epsilon
  - Given 1/epsilon^2 random (m, c=DES(k, m)) pairs, then:
    - k[l_1, ..., l_u] = MAJ [ m[i_1, ..., i_r] XOR c[j_j, ... j_v] ],
      with prob. >= 97.7
  - For DES: epsilon is 1/2^21, so with 2^42 inp/out pairs we can find
    k[l_1, ... l_u] in time 2^42
  - So roughly speaking we can find the remaining 56-14=42 bits in
    time 2^42. Then we can brute force the rest via exhaustive search,
    giving us total attack time of ~= 2^43 (<< 2^56)
  - This is because a tiny bit of linearity in S_5-box lead to the
    2^42 attack.
- Quantum attacks:
  - Hypothetical quantum computers excel at the kind of search task
    that is required with cryptography. This cuts the search time down
    by x^(1/2).
  - This would cut down the search space: With DES: ~= 2^28, with
    AES-128 ~= 2^64, which would still be not secure.
  - If quantum computing becomes a reality, then AES-256 would still
    be usable, as 2^128 is still too big for exhaustive search.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/16][the aes block cipher (14 min)]]
- Timeline:
  - 1997: NIST publishes a request for proposal
  - 1998: 15 submissions of which five claimed attacks
  - 2000: NIST chooses Rijndael as AES (designed in Belgium)
- AES offers key sizes of 128, 192 and 256 bits, and a block size of
  128 bits.
- AES is a Subs-Perm network (not Feistel). The general idea is:
  - In a Feistel network, half the bits don't change every round. In a
    Subs-Perm network all the bits change every round.
  - 1. We xor input with the first round key.
  - 2. We go to a substitution layer (S-boxes) with lookup tables
  - 3. We go to permutation layer, where the bits get shuffled around.
  - 4. We xor the result with the next round key, and we go through
       steps 2-4 again.
  - 5. We xor with the last round key, and this is our output.
- For AES:
  - The input, which is 128 bits or 16 bytes, gets set up in a 4x4
    byte matrix.
  - The 16 byte key gets expanded into 176 bytes (11 x 16)
  - The xor of input and r-key_1 go to an invertible function (steps
    2-3) that performs ByteSub, ShiftRow and MixColumn procedures
  - We repeat this process ten times, and then xor with the eleventh
    round key.
  - The round function:
    - ByteSub: a 1-byte S-box containing 256 bytes (easily computable).
      - We use the index of our 4x4 byte matrix to lookup from the 256
        byte table the corresponding return values.
    - ShiftRows: Each row gets shifted c+1 positions
    - MixColumns: Each column gets mixed and matched.
  - The cool thing about AES is that you can write code that
    generates the tables instead of distributing the tables
    themselves. This is used in browsers, where we send the code to
    generate the tables to save bandwith, and then those tables are
    generated on the client by the browser.
- AES instructions are now included in the Intel Westmere processor,
  which claims a 14x speed-up over OpenSSL on the same hardware.
- Attacks:
  - Best key recovery attack: four times better than ex. search, which
    would make it 2^128 -> 2^126 -> not very effective.
  - Related key attack on AES-256: - Given 2^99 inp/out pairs from four related keys you can recover
    the key in time 2^99.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/17][block ciphers from prgs(12 min)]]
- Can we build block ciphers from pseudo random functions?
- Let's start by finding out if we can build PRF from a PRG?
  - Let G: K -> K^2 be a secure PRG
  - Define 1-bit PRF F: K x {0,1} -> K as F(k, x∈{0,1}) = G(k)[x]
  - F: if 0 choose G(k)[0], if 1, choose G(k)[1]
  - Theorem: If G is a secure PRG, then F is a secure PRF.
  - Can we expand F?
  - We can expand G's output by making G_1 = G(G(k)[0]) || G(G(k)[1]),
    and now we have a two bit PRF: F(k, x∈{0,1}^2) = G_1(k)[x]
  - Using this same principle we can beep expanding G, and thus F.
- The GGM PRF:
  - Let G: K->K^2. define PRF F: K x {0,1}^n -> K as:
    - For input = x_0, x_1, ... x_n-i ∈ {0,1}^n, do:
    - For each K, take G(k_i)[x_i] until G(k_n-1)[x_n-1]
    - Since G is a secure PRG then F is a secure PRF over {0,1}^n
    - Not used much in practice because it's slow.
- Can we build a secure PRP from a secure PRG?
  - Yes! We just plug our GGM PRF into the Luby-Rackoff theorem, which states:
    - Three rounds of a Feistel network makes a PRF into a PRG.
