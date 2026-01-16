#include "app.h"
#include "eadkpp.h"
#include <cstdint>
#include <cstring>

const char eadk_app_name[]
#if PLATFORM_DEVICE
    __attribute__((section(".rodata.eadk_app_name")))
#endif
    = "RSA Crypto";

const uint32_t eadk_api_level
#if PLATFORM_DEVICE
    __attribute__((section(".rodata.eadk_api_level")))
#endif
    = 0;

using namespace RSACrypto;
using namespace EADK;

// === RSA Engine Implementation ===

uint64_t RSAEngine::modPow(uint64_t base, uint64_t exp, uint64_t mod) {
  if (mod == 1) return 0;
  uint64_t result = 1;
  base %= mod;

  while (exp > 0) {
    if (exp & 1) {
      result = ((__uint128_t)result * base) % mod;
    }
    exp >>= 1;
    base = ((__uint128_t)base * base) % mod;
  }
  return result;
}

uint64_t RSAEngine::gcd(uint64_t a, uint64_t b) {
  while (b) {
    uint64_t temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

bool RSAEngine::isPrime(uint64_t n) {
  if (n < 2) return false;
  if (n == 2 || n == 3) return true;
  if (n % 2 == 0) return false;
  
  for (uint64_t i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

RSAEngine::Key RSAEngine::generateKeys(uint64_t p, uint64_t q, uint64_t e) {
  Key key;
  key.n = p * q;
  uint64_t phi = (p - 1) * (q - 1);
  key.e = e;
  
  // Simple modular inverse using extended Euclidean algorithm
  uint64_t m0 = phi, x0 = 0, x1 = 1;
  
  if (phi == 1) {
    key.d = 1;
    return key;
  }
  
  while (e > 1) {
    uint64_t q = e / phi;
    uint64_t t = phi;
    
    phi = e % phi;
    e = t;
    
    t = x0;
    x0 = x1 - q * x0;
    x1 = t;
  }
  
  if (x1 < 0) x1 += m0;
  key.d = x1;
  
  return key;
}

uint64_t RSAEngine::encrypt(uint64_t plaintext, uint64_t n, uint64_t e) {
  return modPow(plaintext, e, n);
}

uint64_t RSAEngine::decrypt(uint64_t ciphertext, uint64_t n, uint64_t d) {
  return modPow(ciphertext, d, n);
}

int main(int argc, char* argv[]) {
  // Initialize display
  Display::pushRectUniform(Screen::Rect, Color(255, 255, 255));
  
  // RSA key generation
  RSAEngine::Key keys = RSAEngine::generateKeys(61, 53, 17);
  
  // Demo encryption/decryption
  uint64_t plaintext = 42;
  uint64_t ciphertext = RSAEngine::encrypt(plaintext, keys.n, keys.e);
  uint64_t decrypted = RSAEngine::decrypt(ciphertext, keys.n, keys.d);
  
  // Display results (simplified)
  const char* text = "RSA Crypto Ready";
  
  // Main loop
  while (1) {
    Keyboard::State state = Keyboard::scan();
    if (state.keyDown(Keyboard::Key::EXE) || state.keyDown(Keyboard::Key::OK)) {
      break;
    }
    Timing::msleep(50);
  }
  
  return 0;
}