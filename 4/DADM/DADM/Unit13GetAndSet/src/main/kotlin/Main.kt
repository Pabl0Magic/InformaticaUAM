fun main() {
    class AbsoluteValue {
        var value: Double = 0.0
            set(value) {
                if (value < 0.0) {
                    field = value * -1
                } else {
                    field = value
                }

            }
    }

    var x = AbsoluteValue()
    x.value = -32.5

    println(x.value)

}

/*
import kotlin.math.absoluteValue

class AbsoluteValue {
    var value: Double = 0.0
        set(v) {
            field = v.absoluteValue
        }
}

fun main() {
    var x = AbsoluteValue()

    x.value = -32.5

    println("Value is ${x.value}")
}

 */