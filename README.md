# 🎹 BabySmasherGame
A game for my son to play. Have fun!

![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B20-orange)
![Engine](https://img.shields.io/badge/engine-SDL2-green)
![Arch](https://img.shields.io/badge/arch-ARM64%20%7C%20x86__64-purple)
![Status](https://img.shields.io/badge/status-Active-success)

**BabySmasherGame**, küçük çocuklar için tasarlanmış, klavyeye basıldıkça renkli şekiller, harfler ve ses efektleri üreten eğlenceli ve öğretici bir masaüstü oyunudur.  
Proje **tamamen C++ + SDL2** ile geliştirilmiştir ve **macOS, Linux ve Windows** üzerinde çalışır.

---

## 🚀 Özellikler

- 🎨 Renkli **daire, kare, üçgen ve yıldız** oluşturma
- 🔤 Şekillerin içinde basılan **harfin gösterimi**
- 🌈 **Gradient + alfa (şeffaflık) destekli render**
- 🔊 **Pop ses efekti** (her tuşta)
- 🗣️ Açılışta **karşılama**, çıkışta **veda sesi**
- 🖼️ Çocuk temalı **Full HD arkaplan**
- ✅ **SDL2_image, SDL2_ttf, SDL2_mixer** entegrasyonu
- ✅ **ARM64 & x86_64** desteği

---

# 🔧 Gereksinimler

- **CMake 3.16+**
- **C++20 uyumlu derleyici**
- **SDL2 bağımlılıkları**
  - SDL2
  - SDL2_image
  - SDL2_ttf
  - SDL2_mixer

---

# 🐧 Linux Derleme

### 1️⃣ SDL2 Kurulumu (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install -y \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-ttf-dev \
  libsdl2-mixer-dev \
  cmake g++
````

### **2️⃣ Derleme**

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### **3️⃣ Çalıştırma**

```
./build/BabySmasherGame
```

---

# **🍎 macOS Derleme (ARM64 & x86_64)**

### **1️⃣ Bağımlılıklar**

```
brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### **2️⃣ Apple Silicon (ARM64)**

```
cmake -S . -B build \
  -G Xcode \
  -DCMAKE_OSX_ARCHITECTURES=arm64

cmake --build build --config Debug
```

### **3️⃣ Intel (x86_64)**

```
cmake -S . -B build_x86 \
  -G Xcode \
  -DCMAKE_OSX_ARCHITECTURES=x86_64

cmake --build build_x86 --config Debug
```

### **4️⃣ Çalıştırma**

```
./build/Debug/BabySmasherGame.app/Contents/MacOS/BabySmasherGame
```

---

# **🪟 Windows Derleme**
## **✅ MinGW**

```
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## **✅ Visual Studio 2022**

```
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

---

# **🔊 Ses Sistemi**

|**Dosya**|**Açıklama**|
|---|---|
|hello.wav|Uygulama açılış sesi|
|goodbye.wav|Uygulama çıkış sesi|
|pop.wav|Tuş sesi|

---

# **🔠 Font Desteği**

Yol:

```
assets/font/OpenSans-Bold.ttf
```

✅ UTF-8 uyumlu

✅ Türkçe karakter destekli

---

# **🧠 Oyun Mantığı**

- Her tuş basımında:
    
    - Rastgele şekil oluşturulur
        
    - Harf yerleştirilir
        
    - Pop sesi çalınır
        
    - Arkaplan otomatik karartılır
        
    
- Şekiller **3 saniye içinde fade-out olur**
    
- Maksimum **29 aktif şekil**

---

# **🧪 Debug Modu**

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

---

# **📜 Lisans**

Bu proje **kişisel ve eğitim amaçlıdır**.

---

# **👨‍💻 Geliştirici**

**Ergün CÜCÜK**

BabySmasherGame – 2025

C++ / SDL2 / Cross-Platform Developer

---
# **✅ Desteklenen Platformlar**

|**Platform**|**Destek**|
|---|---|
|macOS ARM64|✅|
|macOS x86_64|✅|
|Linux ARM64|✅|
|Linux x86_64|✅|
|Windows x86_64|✅|
