fun main() {
    val andalucia = mutableListOf("Almería", "Córdoba", "Granada", "Málaga", "Sevilla")
    var extra = mutableListOf("Cádiz", "Jaén", "Huelva", "Madrid")
    extra.remove("Madrid")
    andalucia.addAll(extra)
    andalucia.sort()

    println(andalucia)

    val code = mutableMapOf<Char, Int>(Pair('a', 'a'.toInt()), Pair('b', 'b'.toInt()))
    val one = Pair('c', 'c'.toInt())
    code += one
    val two = Pair('d', 'd'.toInt())
    code += two

    println(code)
    println(code.keys)
    println(code.values)
    println(code.size)
    println(code.entries)


}
