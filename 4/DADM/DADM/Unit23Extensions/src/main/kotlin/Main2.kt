open class View2 {
    open fun draw() = println("I'm a view")
}

class Button : View2() {
    override fun draw() = println("I'm a button")
    fun draw(color: Int) = println("I'm a button of color $color")
}

fun main() {
    View2().draw()
    Button().draw(2)
    Button().draw()
}   