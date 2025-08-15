# Minishell

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![42](https://img.shields.io/badge/School-42-black)

Minishell, **42 School** müfredatının bir parçası olan, Bash'e benzer bir kabuk (shell) uygulamasıdır.  
Bu proje, temel Unix komutlarını çalıştırabilen, yönlendirmeler ve pipe'lar gibi özellikleri destekleyen, etkileşimli bir kabuk geliştirmeyi amaçlar.

> **Durum:** Bu proje şu anda geliştirme aşamasında ve temel altyapı üzerinde çalışılmaktadır.

---

## 🎯 Amaçlar

- C programlama dilinde **process management** ve **system call** kullanımını öğrenmek.
- **Lexer / Parser / AST** mantığını kavramak.
- `fork()`, `execve()`, `pipe()`, `dup2()` gibi temel Unix fonksiyonlarının çalışma şeklini anlamak.
- Signal ve terminal yönetimi hakkında pratik bilgi edinmek.

---

## 🛠 Planlanan Özellikler

- **Prompt** gösterimi
- **Komut yürütme**
  - Dış komutlar (`/bin/ls`, `/usr/bin/grep` vb.)
  - Built-in komutlar (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- **Yönlendirmeler**
  - `>` `>>` `<` `<<` (heredoc)
- **Pipe** desteği (`|`)
- **Çevresel değişkenlerin yönetimi** (`$HOME`, `$PATH` vb.)
- **Tırnak işaretleri**
  - Tek tırnak `'...'` (literal)
  - Çift tırnak `"..."` (expansion ile)
- **Signal yönetimi**
  - `Ctrl+C`, `Ctrl+D`, `Ctrl+\`

---

## 📂 Proje Yapısı (Planlanan)

```
minishell/
├── inc/              # Header dosyaları
├── src/              # Kaynak kodlar
│   ├── lexer/        # Girdi -> Token
│   ├── parser/       # Token -> AST
│   ├── executor/     # AST -> Çalışan process
│   ├── builtins/     # Dahili komutlar
│   ├── utils/        # Yardımcı fonksiyonlar
│   └── main.c
├── Makefile
└── README.md
```

---

## 🚀 Kurulum

```bash
git clone https://github.com/Sayicon/minishell.git
cd minishell
make
./minishell
```

---

## 📌 Kullanım (Örnekler - Planlanan)

```bash
minishell$ echo "Merhaba Dünya"
Merhaba Dünya

minishell$ ls -l | grep minishell
-rwxr-xr-x  1 user  user   12345 Aug 15 12:00 minishell

minishell$ export NAME=Kerem
minishell$ echo $NAME
Kerem
```

---

## 📖 Kaynaklar

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- 42 School **subject PDF** (ödev dokümanı)

---

## 📜 Lisans

Bu proje [MIT Lisansı](LICENSE) ile lisanslanmıştır.
