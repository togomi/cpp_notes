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


Cryptography has many applications in day-to-day life, from keeping your
[Internet communications
secret](http://en.wikipedia.org/wiki/Transport_Layer_Security) to securing the
[credit card transactions](http://en.wikipedia.org/wiki/EMV) you make at
a physical store. It serves as the foundation of many systems that perform
authentication and keep data secure.

Cryptography is an interdisciplinary topic. It is a crucial part of security but
is not all of it. It is a fun application of mathematics (much of public key
cryptography relies on number theory) and a fun application of theoretical
computer science.

This repo is intended to be an extended introduction to applied
cryptography. While a strong background in mathematics, in particular number
theory and probability, will be helpful, it is not required as we will cover
much of the necessary mathematics.

---
## A brief summary of cryptography
* Never implement your own crypto algorithm.
* Don't use insecure PRNGs like `rand()`, `srand()`, `java.util.Random`. Use
[These](http://en.wikipedia.org/wiki/Cryptographically_secure_pseudorandom_number_generator).
* Don't use
[ECB](http://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_codebook_.28ECB.29)
mode block cipher encryption. Use CBC or GCM instead. However, beware the
[Padding Oracle Attack](http://en.wikipedia.org/wiki/Padding_oracle_attack).
* Always use [initialization Vectors](http://en.wikipedia.org/wiki/Initialization_vector)
in your block ciphers. It's good for you.
* Textbook RSA is insecure. Use RSA with [OAEP padding](http://en.wikipedia.org/wiki/Optimal_asymmetric_encryption_padding).
