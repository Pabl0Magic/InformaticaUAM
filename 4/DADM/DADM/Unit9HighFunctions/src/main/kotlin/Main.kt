/*fun main() {
    println("Alameda".count() { it == 'a' })
    println("Alameda".count() { it == 'e' })
}
*/
/*
fun main() {
    println("Alameda".count() { it == 'a' || it == 'e' })
}
*/
fun main() {

    fun filter(car: Char): Boolean = car =='a' || car == 'e' || car =='i' || car == 'o' || car == 'u'

    println("siesta".count(::filter))
}