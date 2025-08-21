Minishell

42 School müfredatındaki bash-benzeri kabuk uygulaması. Temel hedef: etkileşimli bir kabukta komut yürütme, pipe ve yönlendirmeler, sinyaller ve çevresel değişkenlerle çalışma.

> Durum (21.08.2025): Aktif geliştirme sürüyor. Aşağıdaki bölümlerde neler hazır, neler sırada net olarak işaretlendi.




---

Gereksinimler

C derleyicisi: cc / gcc

GNU Readline başlık ve kütüphanesi: libreadline-dev (Debian/Ubuntu) veya readline (Homebrew)

POSIX uyumlu bir ortam (Linux veya WSL)


Kurulum (Ubuntu/Debian):

sudo apt-get update && sudo apt-get install -y build-essential libreadline-dev

Derleme ve Çalıştırma

git clone https://github.com/Sayicon/minishell.git
cd minishell
make
./minishell

> Makefile tipik hedefler: make, make clean, make fclean, make re.




---

Özellik Durumu

Aşağıdaki liste projedeki işlevlerin güncel durumunu gösterir.

Çekirdek

[x] Prompt (kullanıcı/host/cwd) oluşturma

[x] Sinyaller: SIGINT için prompt davranışı; SIGQUIT maskelenir/ignore

[x] Çevre (env) listesi: envp içeriğinden bağlı liste oluşturma, erişim yardımcıları

[x] Bellek yönetimi: Özel Garbage Collector yardımcıları

[ ] Executor: fork/execve, dup2, pipe zinciri

[ ] Yerleşik komutlar: echo, cd, pwd, export, unset, env, exit


Lexer / Tokenizer

[x] Kelime (WORD), boşluk ayrıştırma

[x] Operatörler: |, <, >, >>, << (tokenize)

[x] Tırnaklar: '...' (literal), "..." (expansion koruması)

[ ] Değişken genişletme: $VAR, $? (lexer+expander)

[ ] Heredoc içerik akışı ve "NOEXP" delimitleyici davranışları

[ ] (Opsiyonel/Bonus) Mantıksal &&, || ve (/) gruplama


Parser / AST

[ ] Komut düğümü (argv, redir listesi)

[ ] Boru hattı ve sıradüzen


Hata Yönetimi & Edge Caseler

[ ] Sentaks hataları ve tutarlı exit status

[ ] Quote/escape köşe durumları



---

Proje Yapısı (Güncel)

minishell/
├── inc/                    # Header dosyaları (genel tipler, API)
├── src/
│   ├── lexer/              # Girdi → Token (kelime/operatör/quote işleme)
│   ├── parser/             # Token → AST (planlanıyor)
│   ├── executor/           # AST → process ve pipe yürütme (planlanıyor)
│   ├── builtins/           # echo, cd, pwd, export, unset, env, exit (planlanıyor)
│   ├── env/                # env listesi, arama/ekleme/güncelleme yardımcıları
│   ├── signals/            # SIGINT/SIGQUIT davranışı, terminal modları
│   └── utils/              # Garbage Collector, string/errno yardımcıları
├── obj/                    # .o çıktıları (derleme sırasında)
├── Makefile
└── README.md

> Not: Klasör isimleri ve kapsamı, commitlerle birlikte evrilebilir; üstteki yapı mevcut düzeni ve hedef mimariyi yansıtır.




---

Kullanım (Hızlı Örnekler)

minishell$ echo "Merhaba Dünya"
Merhaba Dünya

minishell$ export NAME=Kerem
minishell$ echo $NAME
Kerem

minishell$ ls -l | grep minishell
-rwxr-xr-x  1 user  user   12345 Aug 21 12:00 minishell

> Not: Örnekler, hedeflenen davranışı gösterir; tüm akışlar executor/parsing tamamlandıkça birebir hale gelecektir.




---

Geliştirme Notları

Norm/42 Uyumu: Başlık korumaları, fonksiyon uzunluğu ve dosya boyutları 42 Norm kurallarına göre tutulur.

Sinyaller: Prompt açıkken Ctrl-C satırı temizleyip yeni satır verir; Ctrl-\ görmezden gelinir.

Bellek: GC ile ayrılan bloklar kabuk kapanışında toptan serbest bırakılır; ara serbest bırakma yardımcıları mevcuttur.

Taşınabilirlik: Linux/WSL üzerinde geliştirilmiştir; macOS ortamlarda Readline sürüm eşleşmesine dikkat edin.


Test Önerileri

Valgrind: valgrind --leak-check=full --show-leak-kinds=all ./minishell

Quote karması: echo "" '' "a b" 'c d' $USER "$USER" '$USER' | grep "x|y" | cat <<EOF << "NOEXP" >>>out2 || echo end

Redir/pipe sıra denemeleri, boş girdi/EOF, çoklu boşluk/sekme dizileri



---

Yol Haritası

1. Parser/AST iskeletinin tamamlanması


2. Executor ile pipe/redirection akışı


3. Yerleşikler ve $?/env genişletme


4. Heredoc akışı ve NOEXP varyantı


5. Hata/sentaks mesajlarının standardizasyonu




---

Kaynaklar

GNU Bash Reference Manual

POSIX Shell Command Language

42 minishell subject (kamusal paylaşım kısıtlarından ötürü doğrudan eklenmemiştir)


Lisans

Bu proje MIT lisansı ile lisanslıdır. Ayrıntılar için LICENSE dosyasına bakınız.

