## Week 1

### Course Overview

- HTTPS is simply regular HTTP on top of SSL/TLS.
- Different applications of crytograhy:
  - Secure communication online
  - Protecting the contents of a disk from outsiders
- There's two parts to this course:
  1. How to transmit data using a shared secret key
  2. How to establish public-key cryptography
- Symmetric encryption:
  - We have a message m, key k and two algorithms E and D (together
    called the cipher). E is used to /encrypt/ the message and D is
    used to /decrypt/ it afterwards. The result of applying E to m is called c for ciphertext.
  - Always use algorithms that are publicly known.
  - Only k is secret. Everything else is information available for the attacker.
  - Use cases:
    - Single use key: a key is used only once for its task, i.e. for
      sending e-mail.
    - Multi use key: the key is used multiple times, for example to
      encrypt many files. This approach needs more machinery than one
      time key.
- Cryptography follows standards. You should not try to invent stuff
  yourself ad-hoc style. Shit's complicated, yo!

  \*\*\* [[https://class.coursera.org/crypto-007/lecture/2][what is cryptography? (15 min)]]

- Cryptography use cases:
  - Secure communication
  - Storing files
  - Digital signatures
  - Anonymous communication (using mix net):
    - Two parties are able to communicate with each other without
      knowing who or where each other are located.
  - Anonymous digital cash (Bitcoin):
    - Cryptography allows us to get around the problem of double
      spending.
  - Voting problem: How to hold a legitimate elections where we can
    authentically count the amount of votes without revealing
    information about who voted for who.
  - Private auctions: how to hold legitimate auctions without making public the
    amount of the bids.
  - More generally these two are examples of problems related to
    Secure Multi-Party Computation:
    - We have a group of individuals with their inputs (votes, bids)
      [x1, x2, x3... xn] and our goal is to compute a function (voting
      -> the majority, Vickrey auctioin -> the second highest number)
      out of those inputs securely.
    - One (bad) solution to this problem is to use a central trusted
      authority to count the inputs and compute the function we are
      interested in.
    - There is a theorem in crypthography stating that: Any
      computation that you can do with a trusted authority, you can
      also do it without such central authority.
    - This is done by establishing a protocol among the individuals,
      that results in the desired computation being performed, withoug
      disclosing private information (voting preferences, bidding
      prices) amongs themselves.
  - Privately outsourced computation: example with Google search.
  - Zero knowledge (proof of knowledge): [[https://news.ycombinator.com/item?id%3D5545377][examples]], an [[http://www.mit.edu/~rothblum/papers/sudoku.pdf][academic paper]]
    demonstrating the technique on a sudoku puzzle (I claim that I can
    solve a puzzle but you don't trust me. The application of
    cryptography allows me to demonstrate this to you without
    revealing what the solution to the puzzle is).
- Cryptography is a rigorous science and follows a three step
  protocol:
  - 1. Preciseley outlining a threat model
  - 2. Proposing a construction to solve the threat
  - 3. Prove that breaking the construction under threat mode will
       solve an underplying hard problem
       \*\*\* [[https://class.coursera.org/crypto-007/lecture/3][history of cryptography (19 min)]]
- A book: [[http://www.amazon.com/The-Codebreakers-Comprehensive-Communication-ebook/dp/B001D201IK/ref%3Dsr_1_1?s%3Ddigital-text&ie%3DUTF8&qid%3D1371460285&sr%3D1-1&keywords%3Ddavid%2Bkahn%2Bthe%2Bcode%2Bbreakers][the codebreakers]]
- Some historic examples of cryptography:
  - Substitution cipher: simple technique where you substitute one
    letter for another based on a rule. - Caesar Cipher (no key): the rule -> shift by three, so: a -> d,
    b -> e, c -> f etc. - How to break: - The /keyspace/ of this cipher is 26! so around 2^88. This in
    itself is actually ok, but.. - We can easily break the code by analyzing letter frequency: - We know that "e" is the most frequent letter in the English
    language at around 12.7%. Therefore the most frequent letter
    in the ciphered text is likely to be "e". - After individual letters we can move to the frequency of
    letter pairs (digrams) - This scheme is very weak because we only need access to the
    ciphertext in order to crack it. - Vigener cipher (16th century): - You choose a key and repeat it over the length of the message.
    Then you add the (+ mod 26) of the two letters together (so
    once you go over Z you start at A again) and thus you get your
    ciphertext. - Rotor Machines (first mechanical form of cryptography) (1870-1943) - The key is a rotor in a machine that rotates, thus creating a
    new key map for each key press. - Early example: the Hebern machine - The most famous example: The Enigma - Also breakable with cipher-only attacks. - Data Encryption Standard (1974): - The government establised a standard for encryption - DES uses 2^56 keys with block size(?) of 64 bits, which while
    suffecient when it was introduced, should not be used in
    todays world because it's past its days. - Today we have AES (2001), Salsa20 (2008) and others
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/67][discrete probability (crash course) (18 min)]]
- Discrete probability is always defined over a finite universe,
  denoted by U.
- Probability distribution P over U is a function that assigns a
  probability to each element in U so that the sum total for all of
  them is 1. Probability distributions can be categorized based on
  their characteristics:
  - 1. Uniform distribution: the probability of each element is equal,
       i.e. 1/|U|
  - 2. Point distributio at x0, where P(x0) = 1, x ∀ x0: P(x) = 0. (∀
       stands for 'for all')
- Events are subsets of U. For example for U = {0,1}^8 (|U| = 256), we
  can define event A such that it's { all x in U such that lsb2(x) (last
  two significant bits) are 11 }. For the uniform distribution on
  {0,1}^8 the probability of A is 1/4. (11 is one out of four [00, 01,
  10, 11])
- The Union Bound: the probability for events A1 and A2 is Pr[ A1 A2
  ] <= Pr[A1] + Pr[A2]
- A Randomized Algorithm is an algorithm which given the same input
  returns a random output. So instead of y <- A(m) we have y <-
  A(m;r), where r <-R- {0,1}^n output is a random variable.
- We can think of Randomized Algorithms as outputting a randomized variable.
- In a cryptographic algorithm where algorithm A takes Message m and
  Key k as its arguments, and outputs encrypted message E(k, m), we
  can think of the algorithm as being a randomized algorithm where y
  <-R- A(m).
  \*\*\* [[https://class.coursera.org/crypto-007/lecture/66][discrete probability (crash course, cont.) (14 min)]]
- Independence: events A and B are independent if the occurence of one
  event tells nothing about the occurence of the other. So in other
  words if Pr[ A and B ] = Pr[A] \* Pr[B]
- Random variables x and y taking values V are independent if a,b V:
  Pr[X=a and Y=b] = Pr[X=a] \* Pr[Y=b]
- XOR has an important property from cryptographys point of view:
  - For a random variable over {0,1}^n and an independent uniform
    variable on {0,1}^n, then for Z := Y XOR X is a uniform variable.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/4][information theoretic security and the one time pad (19 min)]]
- The definition of a working cipher is defined over (/K/, /M/, /C/):
  - Where /K/ stands for the key space, or the set of all possible
    keys
  - /M/ for the message space. or the set of all possible messages
  - /C/ fro the cipher space, or the set of all possible ciphers
- The formal definition of a cipher is thus defined so that for a
  pair of "efficient" algorithms:
  - Encryption algorithm E: /K/ x /M/ -> /C/
  - Decryption algorithm D: /K/ x /C/ -> /M/
  - For all messages m in message space /M/, and all keys k in key
    space /K/, D( k, E( k, m )) = m
- E is often randomized. D is always deterministic.
- The One Time Pad (OTP) (Verman 1917) is our first example of a
  "secure" cipher:
  - C := E(k, m) = k XOR m
    D(k, c) = k XOR c
  - It's very fast encode and decoding, but keys are long (as long as
    the message)
- Information Theoretic Security (Shannon 1949):
  - Basic idea: cipher text (CT) should reveal no "info" about plain
    text (PT)
  - Definition: A cipher (E, D) over (/K/, /M/, /C/) has perfect
    secrecy if for all m0, m1, that are elements of /M/, where
    len(m0) = len(m1) and for all c that are elements of /C/, the Pr[
    E(k, m0) = c] = Pr[ E(k, m1) = c], where k is uniform in /K/ (k
    <-r- /K/)
  - I.e. if all the adversary has is the cipher text, then he should have
    no idea if it originated from which message.
  - There are no CT only attacks! (but there might be other attacks)
  - The bad news: If we have perfect secrecy, then |K| >= |M|
  - Therefore it's not very practical.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/5][stream ciphers and pseudo random generators (20 min)]]
- Idea: replace "random" key by "pseudorandom" key:
  - PRG: is a function G (for generator) that takes a seed {0,1}^s
    (s-bit seed), that maps it into a larger string {0,1}^n that we
    can expand to string where n >> s.
  - Needs to be "effectively" computable by a deterministic alrogithm
  - Stream ciphers can't have prefect secrecy:
    - We therefore need a different definition of security
    - Security is dependent on the strength of the RPG
- The PRG must be unpredictable:
  - What does it mean for PRG to be predictable?
    - There exist some i such that given the first i bits of a
      sequence generated by G(k)|1,...,i, there exists some algorithm A that
      can predict the next i+1,...,n bits of the sequence.
    - Example: in the SMTP protocol (e-mail), every message begins
      with the word "from,". The attacker could XOR the cipher text
      with the pre-fix "from,", and thus he would get a pre-fix for
      the pseudorandom sequence. From the prefix we can predict the
      rest of the message.
    - Even if you can only predict one bit from a prefix, this
      becomes a problem.
  - PRG is predictable if there exists some algorithm A that given
    some a bit i from a position 1 <= i <= n-1, the Pr[
    A(G(k))|1,..,i = G(k)|i+1 ] >= 1/2 + epsilon.
  - Usually an epsilon of >= 0.5^30 would be considered non-negligeable.
- Some examples of weak PRGs (not suitable for crypto):
  - [[https://en.wikipedia.org/wiki/Linear_congruential_generator][linear congruential generators]]
  - [[http://www.mathstat.dal.ca/~selinger/random/][glibc random()]]
- Neglible vs. non-neglibgle:
  In practice:
  - epsilon of >= 0.5^30 will is non-neglible because it is likely to
    take place over 1GB of data
  - epsilon of >= 0.5^80 is neglible because it won't happen over a
    life time of the key
  - These practical definitions of neglible can be problematic
    In theory:
  - We don't talk about epsilon in terms of scalars, but in terms of functions: - These functions map on non negative integers, and they are
    bigger than some 1/polynomial infinitely often. - Neglible means that for degree polynomial d, λ >= λd:
    epsilon(λ) <= 1/λ^d.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/6][attacks on stream ciphers and the one time pad (24 min)]]
- Attack 1: Using a two time pad is insecure:
  - If we have C1 <- m1 XOR PRG(k) and C2 <- m2 XOR PRG(k), then an
    attacker who has access to both C1 and C2 can take the XOR of the
    two, yielding him the XOR of m1 and m2. The English language and
    ASCII encoding has enough redundancy that you can figure out the
    plain text from that.
  - Never use a stream cipher key more than once!
  - Some real world examples:
    - Project Verona (1941-1946): Russians were encoding their
      messages using a key generated by throwing dice, but the people
      generating the keys got lazy and used the same pad for more than
      one message. This allowed the US Intelligence agency to decrypt
      something like 3k messages.
    - MS-PPTP (Point to Point Transfer Protocol) in Windows NT: A
      client is communicating with a service by sending messages i.e.
      m1, m2, m3, and the server responds with r1, r2, r3. The
      messages are treated as a stream, and encrypted using a stream
      cipher. The problem is that the same is also happening on the
      server side, using the same cipher key. The way to do this
      securely would be to have one key for C->S and S->C.
    - 802.11b WEP (WIFI): We have a client and and access point
      (router): When a client sends a message to the server, it gets
      encrypted by PRG( IV || k ) where IV is a 24 bit string that
      starts repeating after 2^24 = ~16M frames. The problem is that
      once the IV cycles we have a two time pad. On some 802.11 cards
      the IV resets to 0 after a reset.
    - Another mistake WEP makes: The changing IV bit is 24 bits and
      the key is 104 bits but never changes. An attacker listening in
      on the stream can perform an attack that takes advantage of the
      similarity of the total seed-keys and the PRG (RC4) used in WEP,
      which allows him to recover the key after only 40k frames.
    - Disk encryption: If we make an edit to a file using the same
      pad, the attacker is able to identify the part of the file where
      the edit occured. In order to prevent this, the change of a
      small part of the file should result in the contents of the
      whole file getting changed.
  - Summary:
    - Never use a stream cipher key more than once
    - For network traffic: negotiate a new key for every session (e.g. TLS)
    - For disk encryption: avoid using a stream cipher.
- Attack 2: no integrity (OTP is malleable)
  - An attacker who has has access to the cipher text and the ability
    to send messages to the receiving party can spoof the message by
    XOR'ing a new pad P the the cipher, which leaves the receiver with
    m XOR p. This is a problem because the impact on the plaintext can
    be predictable.
  - Example: Bob sends an e-mail to Alice using encryption. The
    message gets intercepted, and the attacker, knowing that a message
    from Bob will start with the form: "From: Bob", can use this to
    spoof a fake message, that appears to be "From: Eve" instead. He
    can do so by XOR'ing "Bob" with "Eve", and replacing the part of
    the message with the name of the sender with such a pad. Alice
    will then receive the modified message, displaying as though it
    was from Eve.
  - This is an example of the cipher scheme lacking integrity, or in
    other words of being malleable.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/7][real-world stream ciphers (20 min)]]
- RC4 (1987) (Broken):
  - Takes a 128 bit seed that gets expanded into 2048 bits and then
    executes a loop that produces one byte at a time.
  - Used in HTTPS and WEP
  - Has several weaknesses and is not recommended for use in modern applications:
    - Bias in initial output: Pr[ 2nd byte = 0 ] = 2/256 instead of
      1/256. The same case is true not just for the second byte, for
      for all bytes before 256. You should therefore ignore the first
      256 bytes altogether.
    - Prob. of sequential 0,0 is 1/256^2 + 1/256^3 when it should be
      only 1/256^2. This appears after several gigabytes of data is produced.
    - Related key attacks: Using keys that are similar to one another
      leaves you vulnerable to an attack.
- CSS (Content Scrambling System) (hardware) (Broken):
  - Based on a concept called Linear Feedback Shift Register
  - Seed is the initial state of the LSFR, which is a collection of
    sequential bits. Predetermined bytes get XOR'd together, the
    sequence of bits gets shifted right, and the XOR'd bit becomes
    the first bit of the sequence.
  - CSS is used in DVD encryption (2 LFSR), GSM encryption (3 LSFR)
    and Bluetooth (4 LFSR). They are all badly broken.
  - CSS in DVD's:
    - seed = 5 bytes = 40 bits
    - Two LSFR's: first a 17-bit and the second a 25-bit. The first
      2 bytes of the 17-bit LSFR get concatenated, as is done for
      the last three bytes of the 25-bit key. Then the two LSFR's
      are run for 8 rounds, and the result is added together +
      (mod 256) plus a carry from the previous block. Then one byte
      per round is outputted.
    - Easy to break in time ~= 2^17 time.
    - Movie files start with a predictable plain text, which the
      attacker can XOR with the first x = (length plain-text) bits,
      which gets him the first 20 bits of the LSFR. The attacker can
      then try each 2^17 of the possible values the first LSFR can
      take, and once he lands on the right one, he can retrieve the
      first x bits of the 25-bit LFSR as well. When he has both, he
      can decrypt those first x bits.
    - Many open source systems that can decrypt CSS encrypted data.
  - Modern stream ciphers: eStream (2008) (Not broken!): - In addition to a seed, the algorithm also takes a {0,1}^s x R
    (Nonce) -> {0,1}^n, n>>s. - Nonce: a non-repeating value for a given key. - The encryption scheme then becomes E(k, m: r) = m XOR PRG(k; r),
    where the pair (k, r) is never used more than once. We can thus
    re-use the key, because the nonce makes it "fresh" - eStream: Salsa 20 (Software + Hardware): - {0,1}^128 or 256 bit key x {0,1}^64 nonce -> {0,1}^n (max n is
    2^73 bits) - Salsa20(k, r) := H( k, (r,0)) || H( k, (r,1)) || ... . H takes
    key, a nonce and an incremental counter.
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/8][prg security definitions (25 min)]]
- What does it mean for a PRG to be secure? Our goal is as follows:
  - Define what it means that [ k <-r- /K/ output G(k) ] is
    "indistinguishable" from [ r <-r- {0,1}n, output r ]
  - In other words: The uniform output of G must be indistinguishable
    from the uniform distribution of all possible random bits that
    could be produced, despite the key-bits being a tiny minority of
    the entire set.
- Statistical Tests:
  - A statistical test is an algorithm A that takes an n-bit string,
    and outputs "1" or "0" for random, or not random.
  - Examples:
    - 1. A(x) = 1 iff (if and only if) | x.count(0) - x.count(1) | <=
         10\*sqrt(n)
    - 2. A(x) = 1 iff | x.count("00") - n/4 | <= 10 \* sqrt(n)
    - 3. A(x) = 1 iff x.max-run-of(0) <= 10 \* log2(n). Note that if
         you give an all 11111... string to this test, it will also
         output 1.
  - Statistical tests can't do pretty much whatever they want. In the
    old days, you would take a battery of statistical tests and if G
    passed a required number of them, then you could say that G was
    secure. This is not a good standard by modern standards though.
- Advantage:
  - Defined:
    - Adv(prg)[A, G] := | Pr[ A(G(k)) = 1 ], (where k <-R- /K/) - Pr[
      A(r) = 1 ], (where r <-r- {0,1}^n) |
    - The advantage is therefore always between 0 and 1
    - If Adv. is close to 1 -> the statistical test A behaved
      differently when we gave it pseudo random input, than when we
      gave it truly random input. This means that A is able to
      distinguish the output of G from random, and is thus breaking G.
      If the Adv. is 0 then A can not break G.
  - Example:
    - 1. A(x) = 0 => Adv(PRG)[A,G] = 0
    - 2. Suppose we have G: K -> {0,1}^n satisfies msb(G(k)) = 1 for
         2/3 of keys in K. Define a stat. test A(x) as: if [ msb(x)=1 ]
         output 1, else 0. Then Adv(PRG) = | Pr[ A(G(k))=1] - Pr[ A(r)=1
         ] | = | 2/3 - 1/2 | = 1/6. We can say that A breaks G with an
         advantage of 1/6.
- Secure PRGs: crypto definition
  - Definition: We say that G:K -> {0,1}^n is secure PRG if there
    exists no such statistical test A that can distinguish its output
    from truly random input efficiently.
  - ∀ "eff" A: Adv(prg)[A,G] is "negligible"
  - Are there provably secure PRGs? We actually can't say. Because of
    the P = NP problem.
  - A secure PRG is unpredictable; you can't infer the probability of
    any of the bits from its previous input.
  - Theorem (Yao, -82): An unpredictable PRG is secure. Let G:K ->
    {0,1}^n be PRG. If ∀ i ∈ {0, ..., n-1} PRG G is unpredictable at
    pos. i, then G is secure PRG.
  - If next-bit predictors cannot distinguish G from random, then no
    statistical test can.
  - It is possible to know that a G is unsecure / predictable, without
    knowing in which way it is so.
  - More Generally: - Let P1 and P2 be two distributions over {0,1}^n. We say that P1
    and P2 are computationally indistinguishable (denoted, P ~=p P2) - If ∀ "eff" stat. tests A, the probability that A(x) = 1 for all
    x <- P1 minus the probability that A(x) = 1 for x <- P2 is less
    than negligible. - A PRG is secure if {k <-r- K: G(k)} ~=p uniform({0,1}^n)
    \*\*\* [[https://class.coursera.org/crypto-007/lecture/9][semantic security (16 min)]]
- What is a secure cipher?
  - try #1: attacker cannot recover secret key? NOPE. E(k,m) = m would
    pass the test
  - try #2: attacker cannot recover all of plaintext? NOPE. revealing
    even some of the text is not very cool.
  - Shannon's idea: cipher text should reveal no information about
    plain text
  - Shannon's theorem of perfect secrecy is too strong though. Stream
    ciphers are not secure by that definition. What we need is a
    weaker definition that we can call semantically secure.
  - Compare:
    - Shannon's: (E,D) has perfect secrecy if ∀ m0, m1 ∈ /M/ (m0, m1
      are same length), {E(k, m0)} = {E(k, m1)} where k <- /K/
    - Semantic security: (E,D) has perfect secrecy if ∀ m0, m1 ∈ /M/
      (same length), {E(k,m0} ~=p {E(k,m1)} where k <- /K/
  - Semantic security (for one-time key)
    - For two messages m0 and m1 that get encrypted by E. If an
      adversary is able to distinguish between their encrypted forms,
      then E is not secure.
    - In other words, for all explicit m0, m1 ∈ M: {E(k, m0)} ~=p
      {E(k, m1)}.
  - OTP is semantically secure, because the distribution of XOR'ing
    anything with a key is always uniform (special property of XOR
    mentioned earlier).
