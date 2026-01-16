#!/bin/bash
set -e

echo "🔧 Installation des dépendances de compilation ARM..."
apt-get update
apt-get install -y \
  make \
  gcc-arm-none-eabi \
  binutils-arm-none-eabi \
  arm-none-eabi-newlib \
  build-essential

echo "📥 Clonage du SDK Epsilon..."
cd /tmp
git clone --depth 1 https://github.com/numworks/epsilon.git
cd epsilon

echo "🛠️  Copie de l'application RSA..."
mkdir -p external_apps/rsa-crypto/src
cp /workspace/src/*.cpp external_apps/rsa-crypto/src/
cp /workspace/src/*.h external_apps/rsa-crypto/src/
cp /workspace/Makefile external_apps/rsa-crypto/

echo "📦 Compilation du .nwa..."
make -C external_apps/rsa-crypto PLATFORM=device build

echo "✅ Compilation réussie!"
ls -lh external_apps/rsa-crypto/output/device/*.nwa

echo "📤 Copie du .nwa vers /workspace..."
cp external_apps/rsa-crypto/output/device/*.nwa /workspace/

echo "✨ Done! Fichier généré avec succès"
