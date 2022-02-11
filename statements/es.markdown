# Descripción

Después de muchos meses de clases virtuales, ha sido posible organizar una concentración presencial. ¡Todos están muy emocionados por poder reunirse nuevamente en el PES! :)

El COMI se encuentra organizando la logística del evento y como parte del proceso, es necesario seleccionar el hotel en donde se hospedarán los participantes. Esta decisión estará basada en la cantidad de tiempo de transporte durante la concentración. El transporte seleccionado para esta ocasión es el metrobús.

El metrobús de la Ciudad de México está compuesto por $N$ estaciones ($1 \le N \le 50,000$) con la peculiaridad de que para cada par de estaciones existe una única ruta. Además, se conoce el tiempo $T$ ($1 \le T \le 500$) en minutos que es necesario invertir para hacer el viaje entre cada dos estaciones directamente conectadas. Sabemos que hay un hotel cercano a cada estación y que el tiempo de traslado del hotel a la estación es insignificante.

El COMI tiene una lista de $M$ ($0 \le M \le N$) lugares (localizados convenientemente cerca de cada una de las estaciones) que se visitarán durante la concentración y cuántas veces se visitará cada uno ($1 \le F \le 300$). Para simplificar la organización, la ruta seguida siempre será del hotel al lugar de interés de ida y de regreso; es decir, no se irá de un lugar de interés a otro sin antes regresar al hotel.

Dado que el tiempo es oro en la concentración, es necesaria tu ayuda para determinar el mínimo tiempo de traslado posible visitando todos los lugares de interés, así como la ubicación de los hoteles donde se puede lograr este valor óptimo.

# Problema

Ayuda al COMI a encontrar la mínima cantidad de tiempo que se utilizará en traslados en el metrobús y el/los lugares donde se debería elegir el hotel.

# Entrada

La primera línea contiene un entero $N$, la cantidad de estaciones del metrobús. Las siguientes $N - 1$ líneas contienen $3$ enteros representando dos estaciones conectadas y el tiempo de traslado $T$, respectivamente.

La línea $N + 1$ contiene un entero $M$, el número de lugares que están planeados para visitar. Las siguientes $M$ líneas contienen cada una el lugar al que se ha planeado ir y la cantidad de veces que se visitará.

# Salida

En la primera línea, la cantidad mínima de tiempo utilizado en traslados seleccionando la ubicación del hotel óptimamente.
En la segunda línea, $K$ enteros representando los lugares en los que es posible alcanzar el valor óptimo, ordenados ascendentemente.

# Ejemplos

||input
2
1 2 17
2
1 5
2 10

||output
170
2

||description
Existen dos estaciones de metrobús. Si se decide seleccionar el hotel de la estación $1$, el tiempo total de traslado será $5(0) + 10(34) = 340$. Por otro lado, si se selecciona el hotel de la estación $2$, el traslado será $5(34) + 10(0) = 170$. Solo es posible obtener el valor mínimo desde este lugar.

||end

## Subtareas

* ($30$ puntos): $1 \le N \le 1,000$
* ($20$ puntos): Cada estación de metrobús está conectada directamente con a lo más otras dos estaciones.
* ($50$ puntos): Sin restricciones adicionales.