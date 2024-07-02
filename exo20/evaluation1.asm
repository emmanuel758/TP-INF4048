extern printf,scanf 
section .data
; Section pour les données (s'il y en a besoin)

section .bss
; Section pour les variables non initialisées (s'il y en a besoin)

section .text
global _start

_start:
    ; Charger la valeur 4 dans le registre eax
    mov eax, 4

    ; Multiplier eax par 5 (eax = 20)
    imul eax, 5

    ; Ajouter 1 à eax (eax = 21)
    add eax, 1

    ; À ce stade, eax contient le résultat de l'expression (21)

    ; Sortie propre du programme
    ; Placer le code de sortie (0) dans eax
    mov eax, 1          ; code de sortie (sys_exit)
    int 0x80            ; appel système pour terminer le programme
