write_log(S) :- open('error_logs.txt', append, Out), write(Out, S), write(Out, '\n'), close(Out).

/***************
* AUXILIAR FUNCTION. pow/3
*
*	ENTRADA:
*		B: Number to calculate the power of.
*		E: Power value.
*	SALIDA:
*		R: Result of the power. 
*
****************/
pow(_,0,1).
pow(B,E,R) :- E > 0,!, E1 is E -1, pow(B,E1,R1), R is B * R1.

/***************
* EJERCICIO 1. sum_pot_prod/4
*
*	ENTRADA:
*		X: Vector de entrada de numeros de valor real.
*		Y: Vector de entrada de numeros de valor real.
*		Potencia: Numero de valor entero, potencia.
*	SALIDA:
*		Resultado: Numero de valor real resultado de la operacion sum_pot_prod. 
*
****************/
sum_pot_prod([], [], _, 0) :- !.
sum_pot_prod([_], [], _, _) :- write_log('ERROR 1.2 Longitud'), !, fail.
sum_pot_prod([], [_], _, _) :- write_log('ERROR 1.2 Longitud'), !, fail.
sum_pot_prod([HX|TX], [HY|TY], Potencia, Resultado) :-
    (
        Potencia < 0 -> % if power less than one, fail
        write_log('ERROR 1.1 Potencia'), fail, !
            ; % else continue by returning true
        true
    ), sum_pot_prod(TX, TY, Potencia, Z),
    pow(HX*HY, Potencia, HP),
    Resultado is HP + Z, !.


/***************
* EJERCICIO 2. segundo_penultimo/3
*
*       ENTRADA:
*               L: Lista de entrada de numeros de valor real.
*       SALIDA:
*               X : Numero de valor real. Segundo elemento.
*		Y : Numero de valor real. Penultimo elemento.
*
****************/
segundo_penultimo([], X, Y) :-  % tell the recursive call to pick the First as Y,
    % first check if there's no X, which would mean invalid length
    (
        var(X) -> write_log('ERROR 2.1 Longitud'), !, fail
        ;
        true
    ),
    Y = '_internal_segpen_First'.

segundo_penultimo([_], X, Y) :- % tell the recursive call to pick the Second as Y
    % first check if there's no X, which would mean invalid length
    (
        var(X) -> write_log('ERROR 2.1 Longitud'), !, fail
        ;
        true
    ),
    Y = '_internal_segpen_Second'.

segundo_penultimo([First,Second|Tail], X, Y) :-
    (
        var(X) -> X = Second ; true % skip else statement
    ),
    segundo_penultimo(Tail, X, Y_rec), % check the tail for penultimate
    (
        Y_rec = '_internal_segpen_Second' ->
            Y = Second
        ;
        Y_rec = '_internal_segpen_First' -> 
            Y = First
        ;
        Y = Y_rec % this only happens when Y_rec has been set to anything that's not the things above
    ),
    !.

/***************
* EJERCICIO 3. sublista/5
*
*       ENTRADA:
*		L: Lista de entrada de cadenas de texto.
*		Menor: Numero de valor entero, indice inferior.
*		Mayor: Numero de valor entero, indice superior.
*		E: Elemento, cadena de texto.
*       SALIDA:
*		Sublista: Sublista de salida de cadenas de texto.
*
****************/
sublista_basic([], _, _, Sublista) :- write_log('ERROR 3.2 Indices'), fail, !.
sublista_basic([H|_], 1, 1, Sublista) :-
    % the last one we must pick is this H
    Sublista = [H], !.
sublista_basic([H|T], 1, Mayor, Sublista) :-
    % begin to include these on the list
    M1 is Mayor - 1,
    sublista_basic(T, 1, M1, Sublista_aux),
    (
        var(Sublista_aux) -> fail ;
        append([H], Sublista_aux, Sublista)
    ),
    !.
sublista_basic([H|T], Menor, Mayor, Sublista) :-
    % don't include, just remove until "Menor" is 0
    (
        Menor > Mayor ->
            write_log('ERROR 3.2 Indices'), fail, !
        ; Menor =:= 1 -> % comes from other conditional
            fail, !
        ; Mayor =:= 1 -> % comes from other conditional
            fail, !
        ; Menor < 1 -> % bad argument
            write_log('ERROR 3.2 Indices'), fail, !
        ; Mayor < 1 -> % bad argument
            write_log('ERROR 3.2 Indices'), fail, !
        ;
        M1 is Menor - 1,
        M2 is Mayor - 1,
        sublista_basic(T, M1, M2, Sublista),
        !
    ), !.

sublista(L, Menor, Mayor, E, Sublista) :- % 
    sublista_basic(L, Menor, Mayor, Sublista),
    (
        member(E, Sublista) ->
            true 
        ; write_log('ERROR 3.1 Elemento'), !, fail
    ). 
/***************
* EJERCICIO 4. espacio_lineal/4
*
*       ENTRADA:
*               Menor: Numero de valor entero, valor inferior del intervalo.
*               Mayor: Numero de valor entero, valor superior del intervalo.
*               Numero_elementos: Numero de valor entero, numero de valores de la rejilla.
*       SALIDA:
*               Rejilla: Vector de numeros de valor real resultante con la rejilla.
*
****************/

espacio_lineal(Menor, Mayor, 1, Rejilla) :- % base case
    Rejilla = [Mayor], !.
espacio_lineal(Menor, Mayor, Numero_elementos, Rejilla) :- % recursive caller
    (
        Menor > Mayor -> write_log('ERROR 4.1 Indices'), fail, !
        ; true
    ),
    % Calculate the step and send recursively the next "Menor" pre-calculated
    ST is (Mayor - Menor) / (Numero_elementos - 1),
    M1 is Menor + ST,
    NE is Numero_elementos - 1,
    espacio_lineal(M1, Mayor, NE, Rejilla_aux),
    append([Menor], Rejilla_aux, Rejilla),
    !.

/***************
* EJERCICIO 5. normalizar/2
*
*       ENTRADA:
*		Distribucion_sin_normalizar: Vector de numeros reales de entrada. Distribucion sin normalizar.
*       SALIDA:
*		Distribucion: Vector de numeros reales de salida. Distribucion normalizada.
*
****************/
head([H|_], H). % aux function
removehead([_|T], T). % aux function
normalizar([Accumulator_Or_First, H], Distribucion) :- % only two elements, a.k.a. last head
        Z is Accumulator_Or_First + H,
        LastValInDistribution is H/Z,
        SometimesFirst is Accumulator_Or_First/Z,
        Distribucion = [SometimesFirst, LastValInDistribution], !.
normalizar([Accumulator_Or_First, H|T], Distribucion) :- 
    Accumulator is Accumulator_Or_First + H,
    append([Accumulator], T, List_With_Accumulator),
    (
        Accumulator_Or_First < 0 ->
            write_log('ERROR 5.1. Negativos'),
            !, fail
        ; H < 0 ->
            write_log('ERROR 5.1. Negativos'),
            !, fail
        ;
        true % continue
    ),
    normalizar(List_With_Accumulator, Distribucion_With_Accumulator),
    % remove the accumulator
    removehead(Distribucion_With_Accumulator, Distribucion_aux),
    % compare two heads, ThisHead/DistrHead = z
    head(T, ThisHead),
    head(Distribucion_aux, DistrHead),
    Z is (ThisHead/DistrHead),
    MyValue is H/Z,
    FirstValue is Accumulator_Or_First/Z,
    append([FirstValue, MyValue], Distribucion_aux, Distribucion), !.

/***************
* EJERCICIO 6. divergencia_kl/3
*
*       ENTRADA:
*		D1: Vector de numeros de valor real. Distribucion.
*		D2: Vector de numeros de valor real. Distribucion.
*       SALIDA:
*		KL: Numero de valor real. Divergencia KL.
*
****************/
is_distribution([Accumul], Length) :-
    Length is 1,
    Accumul =< 1.
is_distribution([Accumul_Or_First, Next | T], Length) :-
    Accumulator is Accumul_Or_First + Next,
    Accumulator =< 1,
    append([Accumulator], T, Tail_With_Accumulator),
    is_distribution(Tail_With_Accumulator, Length_aux),
    Length is Length_aux + 1.
divergencia_kl_calculate([], [], KL) :- KL is 0. 
divergencia_kl_calculate([H1], [H2], KL) :- 
    (
        H1 =< 0 ->
            write_log('ERROR 6.1. Divergencia KL no definida'),
            !,fail
        ;
        H2 =< 0 ->
            write_log('ERROR 6.1. Divergencia KL no definida'),
            !,fail
        ;
        true
    ),
    DIV is H1/H2,
    log(DIV, LOG_RESULT),
    KL is H1 * LOG_RESULT,
    !.

divergencia_kl_calculate([H1|T1], [H2|T2], KL) :- 
    (
        H1 =< 0 ->
            write_log('ERROR 6.1. Divergencia KL no definida'),
            !,fail
        ;
        H2 =< 0 ->
            write_log('ERROR 6.1. Divergencia KL no definida'),
            !,fail
        ;
        true
    ),
    divergencia_kl_calculate(T1, T2, KL_aux),
    DIV is H1/H2,
    log(DIV, LOG_RESULT),
    KL is KL_aux + H1 * LOG_RESULT,
    !.
% function that does the distribution checks and write_logs
% the user important info

divergencia_kl(D1, D2, KL) :-
    % first check if they are distributions
    (
        is_distribution(D1, D1L) ->
            true
        ;
            write_log('ERROR 6.2 Divergencia KL definida solo para distribuciones'),
            !, fail
    ),
    (
        is_distribution(D2, D2L) ->
            true
        ;
            write_log('ERROR 6.2 Divergencia KL definida solo para distribuciones'),
            !, fail
    ),
    % then check for different lenghts
    (
        D1L \== D2L ->
            write_log('ERROR 6.3 Longitud'),
            !, fail
        ;
        true
    ),
    % then do the calculations
    divergencia_kl_calculate(D1, D2, KL),
    !.

/***************
* EJERCICIO 7. producto_kronecker/3
*
*       ENTRADA:
*		Matriz_A: Matriz de numeros de valor real.
*		Matriz_B: Matriz de numeros de valor real.
*       SALIDA:
*		Matriz_bloques: Matriz de bloques (matriz de matrices) de numeros reales.
*
****************/
producto_kronecker(Matriz_A, Matriz_B, Matriz_bloques) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8a. distancia_euclidea/3
*
*       ENTRADA:
*               X1: Vector de numeros de valor real. 
*               X2: Vector de numeros de valor real.
*       SALIDA:
*               D: Numero de valor real. Distancia euclidea.
*
****************/
distancia_euclidea(X1, X2, D) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8b. calcular_distancias/3
*
*       ENTRADA:
*               X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*               X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*
****************/
calcular_distancias(X_entrenamiento, X_test, Matriz_resultados) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8c. predecir_etiquetas/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*       SALIDA:
*               Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
predecir_etiquetas(Y_entrenamiento, K, Matriz_resultados, Y_test) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8d. predecir_etiqueta/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
predecir_etiqueta(Y_entrenamiento, K, Vec_distancias, Etiqueta) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8e. calcular_K_etiquetas_mas_relevantes/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*		K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*
****************/
calcular_K_etiquetas_mas_relevantes(Y_entrenamiento, K, Vec_distancias, K_etiquetas) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8f. calcular_etiqueta_mas_relevante/2
*
*       ENTRADA:
*               K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
calcular_etiqueta_mas_relevante(K_etiquetas, Etiqueta) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8g. k_vecinos_proximos/5
*
*       ENTRADA:
*		X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*		Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*		K: Numero de valor entero.
*		X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*		Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
k_vecinos_proximos(X_entrenamiento, Y_entrenamiento, K, X_test, Y_test) :- write_log('Error. Este ejercicio no esta implementado todavia.'), !, fail.