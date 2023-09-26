fun main() {

    /* Lambda function */
    var functionThatGreets: () -> Unit

    functionThatGreets = {
        println("Hello")
    }

    /* Anonymous function */
    var funcThatGreets = fun(): Unit { //Unit can be omitted
        return println("Hello")
    }

    var FunctionThatGreets: () -> String

    FunctionThatGreets = {
        "Hello"
    }

    println(FunctionThatGreets())
    funcThatGreets()
}

/*
fun main() {

    var functionThatGreets: (String, String) -> Unit

    functionThatGreets = { firstName, lastName ->
        println("Hello, $firstName $lastName")
    }

    functionThatGreets("Elena", "Gonzalez")
}

 */

/*
fun main() {
    Count the length of a string
    var count: (String) -> Int = { string ->
        var number: Int = 0
        for (c in string)
            number++
        number
    }

    println("The length of Burgos is ${count("Burgos")}")
}

 */