path="./bash.bashrc"

if [[ -f "$path" ]]; then
  line_count=$(grep -c -E '^if.*n$' "$path")
  
  echo "Nombre de lignes qui commencent par 'if' et se terminent par 'n' : $line_count"
else
  echo "Le fichier $path n'existe pas."
fi
