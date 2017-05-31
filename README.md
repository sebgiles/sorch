# Sorch
Progetto finale per il corso di Algoritmi e Strutture di Dati.

# Per eseguire
I file .c si compilano con gcc (su OSX con `gcc -o out in.c`). Gli eseguibili si lanciano con `.\out`.

demo.c dovrebbe essere cross-platform.

interactive.c e benchmark.c richiedono Linux o OSX per usare il cronometro, testato solo su OSX.

I dati per la relazione sono stati generati con benchmark.c e scritti su file tramite pipe da terminale bash.

Il cronometro, cioè le funzioni tic() e toc() sono rudimentali, poichè misurano nanosecondi vanno in overflow molto rapidamente.
Inoltre non sono sicuro se misurino il tempo rispetto al Wall clock o al numero di cicli della CPU, sono comunque utili per 
effettuare dei confronti.
