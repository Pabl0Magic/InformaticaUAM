fun main() {
    open class View(
        val id: Int,
        val alignment: String
    )
    class Button(
        var clicked: Boolean,
        var text: String,
        id: Int,
        alignment: String
    ) : View(id, alignment)

    val button: Button = Button(true, "Save", 1, "centered")

    if (button.clicked)
        println("The button with id ${button.id} has been clicked")

    val view = View(2, "left")

    // Error: unresolved reference
    //println(view.text)

}
