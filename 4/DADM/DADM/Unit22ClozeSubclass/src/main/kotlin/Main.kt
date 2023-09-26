fun main() {
    var deck = Deck("English")



    while(true) {
        println("1. Add card")
        println("2. List of cards")
        println("3. Simulation")
        println("4. Exit")
        print("Choose an option: ")
        var option = readln().toInt()
        when (option) {
            1 -> deck.addCard()
            2 -> deck.listCards()
            3 -> deck.simulate(10)
            else -> return
        }
    }

}