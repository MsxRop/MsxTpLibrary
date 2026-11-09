

# MsxTPlibrary 1.0_beta
Ci sono progetti che nascono per necessità, altri per curiosità, altri ancora per amore. Questa libreria MSX per Turbo Pascal 3.01 nasce da tutti e tre.
Nasce dalla necessità di avere strumenti moderni per programmare un sistema che moderno non è. Nasce dalla curiosità di vedere fin dove si può spingere un linguaggio come Pascal su una macchina come l’MSX. Nasce dall’amore per una piattaforma che ha segnato un’epoca, e che continua a vivere grazie a chi la studia, la espande, la reinventa.
MsxTPLibrary, è un’idea che prende forma principalmente come esercizio di programmazione e solo successivamente si configura come un tentativo (a lavori ancora in corso) di fornire un’interfaccia completa tra il linguaggio Turbo Pascal e il sistema MSX.
Il sistema operativo MsxDos, disponibile su tutte le macchine da MSX1 fino a MSXTurboR, dotate di Floppy disk drive, è compatibile con il sistema operativo CP/M 80 e dunque il Turbo Pascal 3 di Borland (così come altri software commerciali dell’epoca quali DBII, MsCobol oppure WordStar), gira perfettamente su macchine MSX anche se, naturalmente, non fornisce alcuna istruzione che permette di sfruttare le caratteristiche grafiche delle macchine MSX. Da qui la necessità di una libreria di funzioni e procedure che forniscono un’interfaccia tra il Turbo Pascal e il BIOS Msx. 
Al momento la libreria è ancora in fase beta, ma fornisce già diverse funzioni che permettono di realizzare semplici programmi in Turbo Pascal che, grazie al fatto di essere compilati, garantiscono una maggiore velocità di esecuzione rispetto al Basic MSX che come sappiamo è interpretato. Il compilatore restituisce un file in formato .DSK ovvero un floppy disk da 3.5” contenente MSXDOS.SYS, COMMAND.COM, il file eseguibile “nomefile.com”, eventuali altri file che possiamo anche aggiungere manualmente attraverso software specifici come ad esempio DiskMgr, o attraverso l’ambiente “msx-pascal-project-template” disponibile su GitHub (nei ringraziamenti c’è il link completo) che fornisce un’interfaccia tra il compilatore e l’ambiente Visual Studio Code.

#Perché Turbo Pascal.
Perché scrivere una libreria da utilizzare con Turbo Pascal per programmare macchine Msx? Beh innanzitutto per una questione di riconoscenza. Il Pascal è stato il linguaggio di programmazione che si studiava alle superiori qualche anno fa e quindi fa parte dei miei ricordi di “boomer” informatico, All’epoca in cui frequentavo l’ITIS Feltrinelli di Milano, avevo già una buona dimestichezza col basic MSX, e il Pascal (usavamo il Turbo Pascal 7 all’epoca) rappresentava un linguaggio moderno ed efficace che rispetto al basic apriva nuove prospettive. In quel periodo muoveva i suoi primi passi la programmazione a oggetti (il C++ sarebbe stato standardizzato nel 1998), ma in ogni caso il Pascal rimaneva uno dei linguaggi più utilizzati in ambito scolastico. Un linguaggio rigoroso,  con una efficace gestione dei tipi, con una sintassi ordinata e, nel caso del Turbo Pascal di Borland, una compilazione efficace che restituiva eseguibili veloci ed efficienti. 

Perché una libreria MSX nel 2026
L’MSX è un computer che appartiene a un’altra epoca. Eppure, chi lo conosce sa che non è mai davvero invecchiato. La sua architettura modulare, la sua filosofia aperta, la sua comunità appassionata lo hanno trasformato in un sistema senza tempo. Il Turbo Pascal, nella sua versione 3.0 per CP/M, è uno dei linguaggi più eleganti mai creati. Ha una sintassi chiara, una logica pulita, una struttura che invita alla precisione.
Mettere insieme MSX e Pascal significa unire due mondi: l’hardware essenziale e poetico degli anni ’80 con la disciplina e la chiarezza del Pascal. Questa libreria nasce per far dialogare questi mondi.
Programmare l’MSX in Pascal presenta sfide precise: il BIOS non è pensato per Pascal, il VDP richiede accessi indiretti, la VRAM non è direttamente indirizzabile, gli sprites hanno tabelle complesse, il mouse MSX2 usa pacchetti dedicati e i comandi VDP avanzati sono potenti ma intricati.
Dunque questa libreria nasce come dicevo per essere un esercizio di programmazione, ma è anche un mezzo per  semplificare, astrarre, rendere elegante e leggibile il codice e sfruttare le caratteristiche dell’efficiente compilatore di Borland; Il codice Pascal, associato all’hardware MSX deve  diventare naturale, non una lotta contro l’hardware. 



La libreria è composta dai seguenti moduli:


- Modulo		                     Ruolo		    Target
- Msx.inc			Fondamenta	“Qui nasce tutto”
- VDP.inc			Grafica		“Il mondo visivo dell’MSX”
- VRAM.inc		Memoria video	“Dove vive l’immagine”
- Sprites.inc		Sprite		“Il movimento”
- Games.inc		Input		“Il dialogo con l’utente”
- Generic.inc		Utilità		“Gli strumenti del mestiere”




# Diamo un’occhiata dall’alto:
- Msx.inc — Le fondamenta
Questo modulo contiene: le costanti necessarie al funzionamento delle routines della libreria, le variabili di sistema, i registri Z80 simulati, i registri del VDP, gli entry point del BIOS e alcuni tipi di dato utilizzati da alcune procedure e funzioni. È il modulo che deve essere incluso per primo. Senza di lui, la libreria non esiste.
- VDP.inc — La grafica
Qui vivono i pixel, e con essi le linee e i rettangoli, il testo grafico, i colori e le palette MSX2; è il modulo che trasforma il Pascal in un pennello.
- VRAM.inc — La memoria video
La VRAM è complessa. Questo modulo la rende semplice, al suo interno troviamo le procedure e le funzioni che permettono la lettura/scrittura byte, di copiare dati tra Ram e Vram, l’utilizzo dei comandi VDP ad alta velocità, la gestione indirizzi VRAM.
- Sprites.inc — Il movimento
Gli sprites sono una delle magie dell’MSX. Questo modulo gestisce la definizione dei pattern, il settaggio degli attributi, l’attribuzione dei colori agli sprites di tipo 2 (MSX2), le collisioni software e hardware e la visualizzazione e il movimento degli sprites.
- Games.inc — L’input
Qui vivono le procedure e le funzioni che permettono di utilizzare le periferiche più comuni come mouse,  joystick, cursori e i relativi pulsanti: la barra di spazio e i due tasti associati ai joystick o al mouse. In sostanza è il modulo che permette al programma di “ascoltare” l’utente.
- Generic.inc — Gli strumenti
Contiene alcune procedure e funzioni utili. La unit è destinata a crescere seguendo le esigenze che dovessero presentarsi nell’utilizzo (come dicevo nell’introduzione, al momento la libreria è ancora in fase beta). Al suo interno troviamo la funzione Hex che restituisce la forma esadecimale a 4 cifre di un intero, la procedura beep, che come è ovvio, produce un beep, la procedura Basic che permette di eseguire semplici istruzioni scritte in Basic Msx direttamente dall’ambiente Turbo Pascal e una utile funzione per calcolare XY. Piccoli strumenti, ma fondamentali.


Nota: Le procedure e le funzioni della libreria sono state testate con OpenMSX simulando macchine MSx2. Sebbene funzionino anche su Msx2+ e MsxTurboR non ho implementato codice specifico per queste versioni. Le procedure e le funzioni sono da ritenersi valide per MSX1 e Msx2, anche se, Per evidenti limiti di memoria,  non è possibile utilizzare le librerie su macchine MSX1, ma solo utilizzare i modi MSX1 su macchine MSX2 o superiori. Attualmente sto sperimentando con il PSG, quindi più o meno a breve, sarà disponibilie anche la unit PSG.INC con cui aggiungere musica ai propri programmi. 


# RINGRAZIAMENTI
Questo lavoro è dedicato:
- a chi ama l’MSX
- a chi ama il Pascal
- a chi ama programmare
- a chi crede che la tecnologia sia anche poesia
- 
Grazie in particolare (in ordine sparso) a:

# Associazione MSX Italia
Un bel gruppo di amici attraverso cui ho ritrovato l’MSX e tutto ciò che gira intorno al suo mondo. Non cito nessuno per non dimenticare nessuno, dico solo che sebbene viviamo sparsi un po’ in tutta Italia, è nata una bella e sincera amicizia tra tutti noi.

# Kazuhiko Nishi 
per aver “inventato” MSX e per aver partecipato con entusiasmo al Devcon di Pisa organizzato dalla nostra Associazione.

# Arnaud de Klerk 
per il suo incredibile lavoro di raccolta e conservazione di tutto il materiale MSX disponibile on line e per la sua generoa condivisione con tutta la comunità

# Kari Lammassaari 
dalle cui librerie ho preso ispirazione, spunto (e anche qualche porzione di codice, soprattutto “inline”)

# decocq-stuff/msx-pascal-project-template 
Template build environment for MSX Turbo Pascal with MS Visual Code IDE integration (e chiunque vi abbia lavorato e contribuito) il cui tool, msx-pascal-project-template, mi è stato di grande utilità nella messa a punto della libreria. Indispensabile per programmare in Turbo pascal comodamente attraverso Visual studio Code

# Edison Moraes 
per il suo prezioso libro MSX Top Secret III, davvero una fonte inesauribile di informazioni utili e interessanti

# C.I. Barkinshaw e R.Goodley 
per il loro libro “MSX linguaggio macchina”, uno dei pochi libri in italiano disponibili all’epoca, che svelava qualche retroscena interessante su MSX.

# Ian Sinclair 
per il suo utilissimo libro “MSX linguaggio macchina e assembly”, un valido manuale di programmazione in assembler Z80, pieno di curiosità su come lavora l’interprete BASIC MSX.

# Jacopo Castelfranchi editore 
uno dei pochi editori italiani attento al mondo MSX negli anni d’oro della “nostra” informatica.

# La “Scuola 2F” 
che, più o meno inconsapevolmente, forniva ai suoi studenti quello che, credo, fu l’unico “MSX italiano” il Frael Bruc100.

# Microsoft Copilot 
che qualche volta mi ha tratto d’impaccio con le sue dritte sulle funzioni non documentate del Bios MSX

# Tutte le persone nel mondo che hanno mantenuto viva la scena MSX. 



