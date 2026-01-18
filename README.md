# 🧩 Basic Lighting Shaders with raylib
### Learning-Oriented Shader Project (Türkçe + English)

<img width="797" height="575" alt="image" src="https://github.com/user-attachments/assets/9528b8f1-f73b-4013-b0ca-759de06660e6" />


## 🇹🇷 Türkçe

### 📌 Projenin Amacı
Bu proje, **raylib** kullanarak **temel shader (vertex & fragment)** mantığını öğrenmek amacıyla geliştirilmiştir.  
Projenin ana hedefi:

- Shader’ların raylib içinde nasıl kullanıldığını öğrenmek
- 3D model, kamera ve ışık ilişkisini anlamak
- Gerçek zamanlı ışıklandırmanın shader üzerinden nasıl kontrol edildiğini görmek
- Türkçe kaynak eksikliğini bir nebze olsun azaltmak

Bu proje **ticari değildir**, tamamen **öğrenme ve deneme** amaçlıdır.

---

### 🧠 Shader Nedir?
Shader’lar GPU üzerinde çalışan küçük programlardır.

- **Vertex Shader**: 3D modelin köşe noktalarının (vertex) ekranda nerede olacağını hesaplar
- **Fragment Shader**: Her pikselin rengini ve ışıklandırmasını hesaplar

Bu projede aydınlatma (lighting) hesapları shader içinde yapılmaktadır.

```text
C++ (CPU)
├─ Kamera pozisyonu
├─ Işıkların konumu, rengi, aktifliği
├─ Modelin vertex verileri
↓
Vertex Shader (GPU)
↓
Fragment Shader (GPU)
↓
Ekrandaki nihai piksel rengi 
```

---

## 🎥 Kamera Bilgisi Shader’a Nasıl Gidiyor?

### C++ Tarafı
cpp
shader.locs[SHADER_LOC_VECTOR_VIEW] =
    GetShaderLocation(shader, "viewPos");

float cameraPos[3] = {
    camera.position.x,
    camera.position.y,
    camera.position.z
};

SetShaderValue(shader,
    shader.locs[SHADER_LOC_VECTOR_VIEW],
    cameraPos,
    SHADER_UNIFORM_VEC3);
    
  🔹 Burada yapılan şey:
    -> Kamera pozisyonu her frame GPU’ya gönderilir
    -> Fragment shader bu bilgiyi yansıma hesabında kullanır
    
---
# 💡 Raylib’de Işıklar Shader’a Nasıl Bağlanır?

## 🧠 Genel Mantık (Özet)

-> CPU (C++) → GPU (Shader) → Piksel rengi


## 📦 Kullanılan Yapı: `rlights.h`

Bu projede ışık sistemi Raylib’in resmi örneklerinden biri olan  
`rlights.h` dosyası kullanılarak kurulmuştur.

→ Işık bilgileri hazırlanır  
→ Shader’a uniform olarak gönderilir  
→ GPU (Shader) her piksel için ışık hesaplar  
- Işıklar C++’ta **veridir**
- Gerçek aydınlatma shader’da yapılır
- Shader’a veri gönderilmezse ışık yoktur
- Raylib sadece köprü görevi görür

  İşte öğrenmek için raylib bu nedenle iyi bir kaynak çünkü
  kendisi otomatik olarak OpenGL ile arasında bir köprü kuruyo
  ve buda ekrana bir üçgen, kare ve ışık gibi kompleks yapıları
  kolayca işlemenizi sağlıyor.

---

### 🧱 Kullanılan Teknolojiler
- C++
- raylib
- OpenGL (GLSL 330)
- glTF (.glb) 3D model formatı
- rlights.h (raylib örneklerinden)


---

### 💡 Işıklar
- 4 adet **Point Light** kullanılmıştır
- Her ışık klavye ile açılıp kapatılabilir
- Işık bilgileri shader’a uniform olarak gönderilir

| Tuş | Işık |
|----|-----|
| 1 | Sarı |
| 2 | Kırmızı |
| 3 | Yeşil |
| 4 | Mavi |

### 🚗 Model
- `.glb` formatında 3D model kullanılmıştır
- Model ücretsiz olarak internetten alınmıştır

---

## 📚 Referanslar
Bu proje, aşağıdaki raylib örneğinden referans almıştır:

- raylib official example  
  `shaders_basic_lighting.c`  
  https://github.com/raysan5/raylib

Amaç, shader mantığını **anlayarak öğrenmektir**.

---

## 🇬🇧 English

### 🎯 Project Purpose
This project is a **learning-oriented implementation** of basic lighting shaders using **raylib**.

It demonstrates:
- How shaders are used in raylib
- How lights interact with 3D models
- How camera position affects lighting
- How GLSL shaders work with C++ code

---

### 🧠 What Are Shaders?
Shaders are small programs that run on the **GPU**.

- **Vertex Shader**: Calculates vertex positions
- **Fragment Shader**: Calculates pixel color and lighting

This project focuses on real-time lighting.

---

### 📚 References
Inspired by raylib’s official example:

- `shaders_basic_lighting.c`  
  https://github.com/raysan5/raylib

---

## 📝 Note
This project was created to better understand shaders and to provide
a partially Turkish explanation due to limited Turkish resources in the graphics programming community.

