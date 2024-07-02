section .data
    result_msg db 'Result: ', 0
    newline db 10, 0

section .bss
    buffer resb 10  ; Tampon pour stocker la chaîne de résultat

section .text
global _start

_start:
    ; Charger la valeur 4 dans le registre eax
    mov eax, 4

    ; Multiplier eax par 5 (eax = 20)
    imul eax, 5

    ; Ajouter 1 à eax (eax = 21)
    add eax, 1

    ; Appel de la fonction pour convertir eax en chaîne
    mov edi, buffer     ; adresse du tampon
    call int_to_ascii

    ; Afficher "Result: "
    mov eax, 4           ; code du système pour sys_write
    mov ebx, 1           ; fichier de sortie (stdout)
    mov ecx, result_msg  ; adresse du message
    mov edx, 8           ; longueur du message
    int 0x80             ; appel système

    ; Afficher le résultat
    mov eax, 4           ; code du système pour sys_write
    mov ebx, 1           ; fichier de sortie (stdout)
    mov ecx, buffer      ; adresse du tampon contenant le résultat
    mov edx, 10          ; longueur du résultat (10 octets réservés pour la sécurité)
    int 0x80             ; appel système

    ; Afficher un saut de ligne
    mov eax, 4           ; code du système pour sys_write
    mov ebx, 1           ; fichier de sortie (stdout)
    mov ecx, newline     ; adresse du saut de ligne
    mov edx, 1           ; longueur du saut de ligne
    int 0x80             ; appel système

    ; Sortie propre du programme
    mov eax, 1           ; code de sortie (sys_exit)
    xor ebx, ebx         ; code de retour 0
    int 0x80             ; appel système pour terminer le programme

; Fonction pour convertir un entier en ASCII (chaîne de caractères)
int_to_ascii:
    ; Convertir l'entier en chaîne de caractères inversée
    ; EAX: nombre, EDI: tampon de sortie
    xor ecx, ecx        ; initialisation du compteur de chiffres
    mov ebx, 10         ; base 10
.convert:
    xor edx, edx        ; remise à zéro du registre edx avant la division
    div ebx             ; EAX / 10, quotient dans EAX, reste dans EDX
    add dl, '0'         ; conversion du chiffre en caractère ASCII
    mov [edi], dl       ; stockage du caractère dans le tampon
    inc edi             ; avancer le pointeur dans le tampon
    inc ecx             ; incrémenter le compteur de chiffres
    test eax, eax       ; vérifier si EAX est non nul
    jnz .convert        ; répéter si EAX n'est pas nul

    ; Inverser la chaîne
    dec edi             ; ajustement pour pointer sur le dernier caractère valide
    mov esi, buffer     ; pointeur de début de tampon
.reverse:
    cmp esi, edi        ; comparer les pointeurs
    jge .done           ; si ESI >= EDI, nous avons inversé toute la chaîne
    mov al, [esi]       ; charger le premier caractère à partir du début
    mov bl, [edi]       ; charger le dernier caractère depuis la fin
    mov [esi], bl       ; échanger les caractères
    mov [edi], al
    inc esi             ; déplacer vers l'avant
    dec edi             ; déplacer vers l'arrière
    jmp .reverse        ; répéter jusqu'à ce que tous les caractères soient échangés
.done:
    ret                  ; retourner à l'appelant
