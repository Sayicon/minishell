Minishell

  

Bash'e benzer etkileşimli bir mini shell. 42 School müfredatının bir parçası.

> Durum (2025-08-20): Aktif geliştirme. Lexer/Tokenizer üzerinde çalışmalar sürüyor, çevre değişkenleri ve temel altyapı hazır.




---

🚀 Hedefler

C ile process management ve system call kullanımı

Lexer → Parser → AST → Executor hattını kurmak

fork, execve, pipe, dup2, wait* çağrılarıyla çoklu süreç yürütme

Signal ve terminal yönetimi (prompt, heredoc, ctrl kombinasyonları)



---

📦 Gereksinimler

OS: Linux

Derleyici: cc / gcc (C99 uyumlu)

Kütüphaneler: readline (42'de genellikle izinli), termcap/terminfo (gerekirse)



---

🛠️ Kurulum ve Derleme

git clone https://github.com/Sayicon/minishell.git
cd minishell
make            # veya make re
./minishell

> Makefile ile obj/ klasörüné nesne dosyaları düşer.




---

📁 Proje Yapısı (güncel klasörler)

minishell/
├─ inc/          # Headerlar
├─ src/          # Kaynak kodlar
│  ├─ utils/     # yardımcılar ("garbage collector" dahil)
│  └─ ...        # lexer/parser/executor planlanıyor
├─ obj/          # Derleme çıktıları
├─ Makefile
└─ README.md

> Repo kökünde MIT LICENSE dosyası mevcut.




---

🔧 Uygulama Notları (güncel ilerleme)

Garbage Collector (GC): Projede bellek takibi için basit bir GC katmanı eklendi (başlık ve yardımcı fonksiyonlarla). env_init gibi yerlerde kullanılıyor.

Çevre Değişkenleri: env_init(char **envp, t_shell *shell) ile key=value çiftlerinden bağlı liste kuruluyor.

Prompt: make_prompt() ile kullanıcı/host/cwd birleştirilip prompt oluşturuluyor. setup_signals_prompt() SIGINT yakalıyor, SIGQUIT ignore ediliyor.

Tokenizer/Lexer (WIP): WORD, PIPE, REDIR_IN/OUT/APPEND, HEREDOC, LOGICAL_AND/OR, PAREN_OPEN/CLOSE türleri planlandı. Operatör tanıma ve tırnak/expand kuralları geliştiriliyor.

Makefile: all, clean, fclean, re hedefleri ve obj/ dizini yönetimi aktif.



---

🧩 Token Türleri (planlanan)

Tür	Açıklama	Örnek

WORD	Argüman / kelime	ls, file.txt
PIPE	pipe	`
REDIR_IN	giriş yönlendirme	<
REDIR_OUT	çıkış yönlendirme	>
REDIR_APPEND	ekleme	>>
HEREDOC	here-doc	<<
LOGICAL_AND	&&	&& (bonus)
LOGICAL_OR		
PAREN_OPEN/CLOSE	gruplama	(, ) (bonus)



---

🥺 Test Önerileri

echo hello, pwd, env

ls -l | grep minishell | wc -l

echo hi > out.txt, cat < out.txt, echo a >> out.txt

cat <<EOF + içerik + EOF

echo "a b" 'c d' "$USER" '$USER'

Heredoc/prompt sırasında Ctrl+C ve Ctrl+\ sinyalleri



---

🗺 Yol Haritası

[x] Makefile ve klasör yapısı

[x] Garbage Collector

[x] Env listesi kurulumu

[x] Prompt + sinyaller

[ ] Tokenizer kuralları (tırnak, escape, $expansion, whitespace)

[ ] Parser & AST

[ ] Executor (redir/pipe)

[ ] Builtins (echo, cd, pwd, export, unset, env, exit)

[ ] Heredoc (sinyal kontrolü dahil)

[ ] Hata yönetimi ve çıkış kodları

[ ] Edge-case test koleksiyonu



---

🤖 Kullanım (hedeflenen)

minishell$ echo "Merhaba Dünya"
Merhaba Dünya

minishell$ export NAME=Kerem
minishell$ echo $NAME
Kerem

minishell$ ls -l | grep minishell
-rwxr-xr-x  1 user  user   12345 Aug 20 12:00 minishell


---

📚 Kaynaklar

GNU Bash Reference Manual

POSIX Shell Command Language

42 Subject (paylaşıma uygun çerçevede)



---

🤝 Katkı

PR/Issue açmadan önce lütfen stil ve proje hedefleriyle uyumu kontrol edin. 42 Norm ve proje kurallarına bağlı kalın.


---

📄 Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Detaylar için LICENSE dosyasına bakın.