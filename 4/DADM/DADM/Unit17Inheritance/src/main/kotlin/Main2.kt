/*fun main(args: Array<String>) {
    open class View {
        init {
            println("View const")
        }
    }

    class Button(var isClickable: Boolean): View() {//Button subclass of View
        init{
            println("Button const")
        }
    }
    class Image: View {
        constructor(): super()
    }
    val inst = Button(true)
    val insta = Image()
    println(View().toString())
    println(inst.equals(insta))
}*/
fun main() {
    open class View(val id: Int, val alignment: String) {
        init {
            println("View const")
        }
    }

    class Button(id: Int, alignment: String) : View(id, alignment) {//Button subclass of View
        init {
            println("Button const")
        }
    }

    val view: Button = Button(2, "centered")
    println("The view with id ${view.id} is ${view.alignment}")
}