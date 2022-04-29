# TP-ahorcado
Este es el primer trabajo practico para Taller de Programacion, en el cual desarrollamos un juego del ahorcado en c, utilizando lo recientemente aprendido sobre la gestión de memoria, el programa cuenta con un menu inicial a traves del cual el usuario puede: 

<ol>
<li><strong>Empezar a jugar</strong>: abriendo un menu donde se le dara a elegir palabras aleatorias del lemario dado y tras una seleccionada se jugara un juego del ahorcado normal, el cual una vez concluido dara la opcion al jugador de volver al menu inicial o terminar el programa.</li>

<li><strong>Revisar historial</strong>: Las palabras, victorias y el porcentaje de victorias de las partidas jugadas (solo en la ejecución del programa en la que el usuario se encuentre) se mostraran en una lista ordenada cronologicamente.</li>

<li><strong>Salir</strong>: Esto terminara la ejecución del programa, cerrandolo y creando un archivo llamado <code>historial.txt</code> el historial de dicha ejecución (sobreescribiendolo en caso de ya existir).</li>

</ol>

## Integrantes del Grupo
---
<ul>
    <li>Tomas Gruning</li>
    <li>Jeronimo Ledesma</li>
    <li>Manuel Noviski</li>
</ul>

## Anotaciones
---
Para este programa decidimos incluir una constante llamada <code>CANT_PALABRA</code> que permite generar mas palabras a elegir para el jugador. Esto cambia un poco la funcion <code>traducir_archivos</code> reduciendo la probabilidad de hacer saltos de linea muy largos.