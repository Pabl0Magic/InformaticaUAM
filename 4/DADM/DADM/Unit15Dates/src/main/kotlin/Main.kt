import java.time.*
/*
fun main() {
    val localtime = LocalTime.now()

    var newtime = localtime.plusHours(1).plusMinutes(20)

    println(localtime)
    println(newtime)
}*/

fun main() {
    val date = LocalDate.of(2020, 12, 20)

    var newdate = date.plusDays(15)

    println(newdate)
}
