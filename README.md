# Introduction to Cryptography
Lecture Notes and Assignments on Cryptography

Coursera Courses
- https://www.coursera.org/learn/cryptography (Maryland)
- https://www.coursera.org/learn/crypto (Stanford)

---
## Introduction
> Cryptography (or cryptology; from Greek κρυπτός kryptós, "hidden, secret";
> and γράφειν graphein, "writing", or -λογία -logia, "study", respectively) is
> the practice and study of techniques for secure communication in the presence
> of third parties (called adversaries).
-- [Wikipedia page](http://en.wikipedia.org/wiki/Cryptography)

Cryptography is an interdisciplinary topic. It is a crucial part of security but
is not all of it. It is a fun application of mathematics (much of public key
cryptography relies on number theory) and a fun application of theoretical
computer science.

Cryptography has many applications in day-to-day life:
- [Secure Online Communication](http://en.wikipedia.org/wiki/Transport_Layer_Security)
    - HTTPS is simply regular HTTP on top of SSL/TLS.
- Securing the
[credit card transactions](http://en.wikipedia.org/wiki/EMV) you make at
a physical store
- Protecting the contents of a disk or a server
- Digital signatures
- Crypto-currency (Bitcoin):
    - Cryptography allows us to get around the problem of double spending.
- Voting problem: How to hold a legitimate elections where we can authentically count the amount of votes without revealing information about who voted for who.

Cryptography is a rigorous science and follows a three step
  protocol:
1) Precisely outlining a threat model
2) Proposing a construction to solve the threat
3) Prove that breaking the construction under threat mode will
    solve an underlying hard problem

There are two parts of learning this course:
  - 1) How to transmit data using a shared secret key
  - 2) How to establish public-key cryptography

---
## A brief summary of cryptography
* Cryptography follows standards. Never implement your own crypto algorithm.
* Don't use insecure PRNGs like `rand()`, `srand()`, `java.util.Random`. Use
[These](http://en.wikipedia.org/wiki/Cryptographically_secure_pseudorandom_number_generator).
* Don't use
[ECB](http://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_codebook_.28ECB.29)
mode block cipher encryption. Use CBC or GCM instead. However, beware the
[Padding Oracle Attack](http://en.wikipedia.org/wiki/Padding_oracle_attack).
* Always use [initialization Vectors](http://en.wikipedia.org/wiki/Initialization_vector)
in your block ciphers. It's good for you.
* Textbook RSA is insecure. Use RSA with [OAEP padding](http://en.wikipedia.org/wiki/Optimal_asymmetric_encryption_padding).
