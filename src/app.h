#ifndef RSA_CRYPTO_APP_H
#define RSA_CRYPTO_APP_H

#include <cstdint>

namespace RSACrypto {

class RSAEngine {
public:
  struct Key {
    uint64_t n;  // modulus
    uint64_t e;  // public exponent
    uint64_t d;  // private exponent
  };
  
  // RSA operations
  static uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
  static uint64_t gcd(uint64_t a, uint64_t b);
  static bool isPrime(uint64_t n);
  static Key generateKeys(uint64_t p, uint64_t q, uint64_t e);
  static uint64_t encrypt(uint64_t plaintext, uint64_t n, uint64_t e);
  static uint64_t decrypt(uint64_t ciphertext, uint64_t n, uint64_t d);
};

} // namespace RSACrypto

#endif
