class View(
    val id: Int,
    val name: String
)

fun View.show() = println("I am view $id and my name is $name")


fun main() {
    fun String.last(): Char = this.get(this.length - 1)
    println("Village".last())

    fun String.vowels(): Int = uppercase().count {
        it == 'A' || it == 'E' || it == 'I' || it == 'O' || it == 'U'
    }
    println("The number of vowels is ${"Alabama".vowels()}")

    View(1, "Rectangle").show()
}
