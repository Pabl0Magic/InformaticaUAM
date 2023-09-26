package es.uam.eps.dadm.cards

//import java.time.LocalDateTime
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.*
//import java.io.File

@Entity(tableName = "decks_table")
class Deck (
    @ColumnInfo("deck_name")
    var name: String,
    @PrimaryKey
    var deckId: String = UUID.randomUUID().toString(),
    var userId: String) {
    var delete: Boolean = true

    constructor(): this (
        "Default",
        UUID.randomUUID().toString(),
        ""
            )
    /*fun addCard(card: Card?) {
    }*/

}