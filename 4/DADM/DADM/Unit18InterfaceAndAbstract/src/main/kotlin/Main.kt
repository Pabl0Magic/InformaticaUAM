interface Drawable {
    fun draw()
    fun report() {
        println("I am drawable")
    }
}

fun main() {
    open class View(
        val id: Int,
        val alignment: String
    ) {
        open fun draw() = println("View $id is $alignment")
    }

    class Button(
        var isClickable: Boolean,
        var text: String,
        id: Int,
        alignment: String
    ) : View(id, alignment) {
        override fun draw() = when (isClickable) {
            true -> println("Button $id is $alignment and clickable")
            false -> println("Button $id is $alignment and not clickable")
        }
    }

    class Image(id: Int, alignment: String) : View(id, alignment)

    open class View2 : Drawable {
        override fun draw() {
            println("I am a view")
        }
    }

    class Button2 : View2() {
        override fun draw() {
            println("I am a button")
        }
    }

    abstract class AbstractView(var id: Int) {
        abstract fun draw()
        fun report() = println("I extend an abstract view")
    }

    class Button3(id: Int) : AbstractView(id) {
        override fun draw() = println("I am button $id")
    }

    Button(true, "Save", 1, "centered").draw()
    Image(2, "on the left").draw()
    View2().report()
    View2().draw()
    Button2().draw()
    Button2().report()

    val view: AbstractView = Button3(1)
    view.report()
    view.draw()
}