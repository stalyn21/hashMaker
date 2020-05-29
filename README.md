# Hash-Maker in the Blockchain
## Idea
Finding zeros modifying the nonce.

Our goal is to see which of the 3 algorithms is best for finding hash with zeros at the beginning of it.

### Importance
A nonce is a cryptographic input value which must never repeat within a given context. Nonces are important for the security of many cryptographic building blocks, such as stream ciphers, block cipher modes of operation, and message authentication codes. Nonetheless, the correct generation of nonces is rarely discussed in the cryptographic literature.

## Documentation 
All these codes are a small part of the following algorithms, which you can find in https://github.com/Rytisgit/Hashing (setTransaction), https://github.com/peakstack/Simple-Blockchain (keccak), and a information security practice dictated by Oscar Chang (brute force). Furthermore, these codes were adapted for our purposes.

## Algorithms

### Brute Force
It is a technique that allows you to test all possible combinations until you find the word or readable text that was encrypted. Brute Force Attack: A word length, Encrypted word, Algorithm or encryption function.

The calculation of the nonce is carried out in a forced way, or what is the same: large amounts of computing resources are required and also time, so achieving this value requires the most possible computing resources

### Set Transaction
Based principally on :
To use high precision fractional digits gotten from each symbol by high power root to mutate to whole current hash. The nonce is always the sender's transaction count.

Receiving a transaction doesn't affect the nonce. When a transaction is processed, all pending transactions with a nonce lower than the confirmed transaction are cancelled. For these reason they are intimately relacionated.


### Keccak
It is based on the sponge construction. In Keccak, the underlying function is a permutation chosen in a set of seven Keccak-f  permutations, denoted Keccak-f[b], where  b∈{25,50,100,200,400,800,1600} is the width of the permutation. The width of the permutation is also the width of the state in the sponge construction. All information about this, you can found in https://keccak.team/keccak_specs_summary.html

## General Issues

### Vulnerability of nonce-based systems
The nonce reset problem. While ensuring that nonces never repeat is trivial in theory, practical systems can suffer from accidental or even malicious resets which can wipe out the nonce generators current state.

### To avoid collisions (memory)
The nonce length has to be large, which may be problematic particularly in light-weight cryptographic systems with limited memory or bandwidth.

## An unexpected power-down 
It can mean the loss of all information that was not stored in non-volatile memory (Virtual Memory), storing the nonce to Flash memory or a hard disk is not an option.


## References
All the information collected is here
https://github.com/stalyn21/hashMaker/blob/master/info/links.txt 
