# NumWorks RSA Crypto App

Une application de cryptographie RSA pour calculatrice NumWorks.

## Compilation avec Codespaces

1. **Ouvrir Codespaces:**
   - Appuyez sur `<>` Code → Codespaces → Create codespace on main
   - Le build s'exécutera automatiquement

2. **Récupérer le fichier .nwa:**
   - Attendez la fin du build (voir la sortie du terminal)
   - Le fichier `rsa_crypto.nwa` sera généré dans `/workspace/`
   - Téléchargez-le depuis l'explorateur Codespaces

3. **Installer sur NumWorks:**
   - Allez sur https://my.numworks.com/apps
   - Uploadez le fichier `rsa_crypto.nwa`
   - Suivez les instructions

## Fonctionnalités

- Génération de clés RSA
- Encryption/Decryption
- Démo avec clés de test (p=61, q=53, e=17)

## Prérequis pour compilation locale

- GCC ARM (arm-none-eabi-gcc)
- Make
- Epsilon SDK
