bison -d fonctCal.y          # Générer les fichiers fonctCal.tab.c et fonctCal.tab.h
flex -o lex.yy.c fonctCal.l  # Générer le fichier lex.yy.c à partir de votre fichier Flex (.l)

gcc -o output fonctCal.tab.c lex.yy.c -lfl  # Compiler et lier avec Flex (-lfl pour utiliser la bibliothèque Flex)