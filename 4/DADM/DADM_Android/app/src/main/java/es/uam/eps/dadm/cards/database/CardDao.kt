package es.uam.eps.dadm.cards.database

import androidx.lifecycle.LiveData
import androidx.room.*
import es.uam.eps.dadm.cards.Card
import es.uam.eps.dadm.cards.Deck
import es.uam.eps.dadm.cards.DeckWithCards

@Dao
interface CardDao {
    @Query("SELECT * FROM cards_table WHERE userId = :userId")
    fun getCards(userId: String): LiveData<List<Card>>

    @Query("SELECT * FROM cards_table WHERE id = :id")
    fun getCard(id: String): LiveData<Card?>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun addCard(card: Card)

    @Query("DELETE FROM cards_table WHERE id = :id")
    fun deleteCard(id: String)

    @Query("DELETE FROM cards_table WHERE userId = :userId")
    fun deleteAllCards(userId: String)

    @Update
    fun update(card: Card)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun addDeck(deck: Deck)
    @Query("DELETE FROM decks_table WHERE deckId = :id")
    fun deleteDeck(id: String)

    @Query("DELETE FROM decks_table WHERE userId = :userId")
    fun deleteAllDecks(userId: String)

    @Update
    fun updateDeck(deck: Deck)

    @Query("SELECT * FROM decks_table WHERE deckId = :id")
    fun getDeck(id: String): LiveData<Deck?>


    @Query("SELECT * FROM decks_table WHERE userId = :userId")
    fun getDecks(userId: String): LiveData<List<Deck>>

    @Query("SELECT COUNT(*) FROM decks_table WHERE userId = :userId")
    fun getNumDecks(userId: String): LiveData<Int>

    @Query("SELECT * FROM cards_table WHERE deckId = :deckId")
    fun getCardsByDeck(deckId: String): LiveData<List<Card>>

    @Transaction
    @Query("SELECT * FROM decks_table")
    fun getDecksWithCards(): LiveData<List<DeckWithCards>>


    @Transaction
    @Query("SELECT * FROM decks_table WHERE deckId = :deckId")
    fun getDeckWithCards(deckId: Long): LiveData<List<DeckWithCards>>

}