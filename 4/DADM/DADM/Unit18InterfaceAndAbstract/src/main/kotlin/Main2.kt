/*interface Drawable {
    fun draw()
}

fun main() {
    open class View() : Drawable {
        override fun draw() = println("I'm a view")
    }

    class Button : View() {
        override fun draw() = println("I'm a button")
    }

    var list = mutableListOf<View>()
    list.add(Button())
    list.add(View())
    list.add(Button())

    for (item in list)
        item.draw()
}

 */
