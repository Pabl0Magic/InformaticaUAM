val String.last : Char
    get() = get(length - 1)

val String.diff: Int
    get() = get(length - 1) - get(0)

fun main() {
    println("Village".diff)
}
