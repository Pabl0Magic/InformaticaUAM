fun main() {
    open class View(
        val id: Int,
        val alignment: String
    )

    class Button : View {
        // Add the code of the first secondary constructor
        constructor(id: Int, al: String) : super(id, al)
        // Add the code of the second secondary constructor
        constructor(id: Int): super(id, "centered")
    }

    val view: Button = Button(1)
    val view2: Button = Button(2, "normal")
    println("The view with id ${view.id} is ${view.alignment}")
    println("The view2 with id ${view2.id} is ${view2.alignment}")

}