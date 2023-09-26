object Collections {
    val decks = mutableListOf<Deck>()

    fun checkDeck(name: String): Boolean {
        for (i in decks) {
            if (i.name == name) return true
        }

        return false
    }

    fun addDeck(name: String) {
        if (checkDeck(name)) {
            println("Name already in use")
            return
        }
        decks.add(Deck(name))
    }

    fun removeDeck(name: String) {
        val aux = decks.toList()
        for (d in aux) {
            if (d.name == name) {
                decks.remove(d)
            }
        }

        println("No deck named $name")
    }

    fun showDecks() {
        decks.forEach {println(it.name)}
    }
}

fun main() {
    var deck = Deck("English")
    var n = ""
    Collections.decks.add(deck)


    while(true) {
        println("\nYou are in ${deck.name} deck")
        println("1. Add deck")
        println("2. Delete deck")
        println("3. Change deck")
        println("4. Show decks")
        println("5. Add card")
        println("6. Delete card")
        println("7. List of cards")
        println("8. Simulation")
        println("9. Read cards from file")
        println("10. Write cards to file")
        println("11. Exit")
        print("Choose an option: ")
        val option = readln().toInt()

        if (option == 1) {
            print("Write the name of the deck you want to create: ")
            n = readln()
        }

        if (option == 2) {
            print("Write the name of the deck you want to delete: ")
            n = readln()
            if (n == deck.name) {
                println("You can't delete the deck you are using")
                continue
            }
        }

        if (option == 3) {
            print("Write the name of the deck you want to change to: ")
            n = readln()
        }

        if (option == 6) {
            print("Write the question of the card you want to delete: ")
            n = readln()
        }

        if (Collections.decks.isNotEmpty()) {
            when (option) {
                1 -> Collections.addDeck(n)
                2 -> Collections.removeDeck(n)
                3 -> {
                    if (Collections.checkDeck(n)) {
                        for (i in Collections.decks) if (n == i.name) deck = i
                    } else {
                        println("No deck named $n")
                    }
                }
                4 -> Collections.showDecks()
                5 -> deck.addCard()
                6 -> deck.deleteCard(n)
                7 -> deck.listCards()
                8 -> deck.simulate(10)
                9 -> deck.readCards("cards")
                10 -> deck.writeCards("cards")
                else -> return
            }
        } else {
            println("There are no decks")
        }
    }
}