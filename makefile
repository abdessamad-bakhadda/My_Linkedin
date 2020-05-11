.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

build/liste.o: lib/liste.c | build
	clang -Wall -pedantic  -g -c lib/liste.c -I ./lib -o build/liste.o
## 4 groupes
build/groupe_entreprise.o: lib/groupe_entreprise.c | build
	clang -Wall -pedantic  -g -c lib/groupe_entreprise.c -I ./lib -o build/groupe_entreprise.o

build/groupe_poste.o: lib/groupe_poste.c | build
	clang -Wall -pedantic  -g -c lib/groupe_poste.c -I ./lib -o build/groupe_poste.o

build/groupe_employe.o: lib/groupe_employe.c | build
	clang -Wall -pedantic  -g -c lib/groupe_employe.c -I ./lib -o build/groupe_employe.o

build/groupe_chemploi.o: lib/groupe_chemploi.c | build
	clang -Wall -pedantic  -g -c lib/groupe_chemploi.c -I ./lib -o build/groupe_chemploi.o

##

build/libliste.a: build/liste.o  | build
	ar crs build/libliste.a build/liste.o
## 4 groupes
build/libgroupe_entreprise.a: build/groupe_entreprise.o  | build
	ar crs build/libgroupe_entreprise.a build/groupe_entreprise.o

build/libgroupe_poste.a: build/groupe_poste.o  | build
	ar crs build/libgroupe_poste.a build/groupe_poste.o

build/libgroupe_employe.a: build/groupe_employe.o  | build
	ar crs build/libgroupe_employe.a build/groupe_employe.o

build/libgroupe_chemploi.a: build/groupe_chemploi.o  | build
	ar crs build/libgroupe_chemploi.a build/groupe_chemploi.o
##

build/test.o: test/main_entreprise.c | build
	clang -Wall -pedantic  -g -c test/main_entreprise.c -I ./lib -o build/test.o

build/test: build/test.o build/libgroupe_entreprise.a  build/libgroupe_poste.a build/libgroupe_employe.a build/libgroupe_chemploi.a build/libliste.a | build
	clang build/test.o -Lbuild -lgroupe_entreprise -lgroupe_poste -lgroupe_employe -lgroupe_chemploi  -lliste -o build/test



# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: build/test
	
# Lance le programme de test.
check:
	./build/test
