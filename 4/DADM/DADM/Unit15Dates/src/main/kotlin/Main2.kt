import java.text.SimpleDateFormat
import java.util.Date

fun main(args: Array<String>) {
    val start = System.currentTimeMillis()

    for (i in 1..1000000);

    val end = System.currentTimeMillis()

    println("Time spent is ${end - start} milliseconds")

    val date = Date()
    for (i in 1..1000000);
    val date2 = Date()
    println(date)
    println(date2)
    println("Comparison = " + date.compareTo(date2))

    val f = SimpleDateFormat("dd-MM-yyyy HH:mm")
    println(f.format(date))
    val dateParse: Date = f.parse("06-02-2023 18:51")

    print(dateParse)

}

/*
fun main() {
    val f = SimpleDateFormat("dd-MM-yyyy HH:mm")
    val calendar = GregorianCalendar()

    calendar.set(Calendar.DAY_OF_MONTH, 12)
    calendar.set(Calendar.MONTH, 0)
    calendar.set(Calendar.YEAR, 2018)

    calendar.add(Calendar.WEEK_OF_YEAR, 1)

    print(f.format(calendar.time))
}

 */