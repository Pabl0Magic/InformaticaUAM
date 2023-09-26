package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase
import es.uam.eps.dadm.cards.databinding.ListItemDeckBinding

class DeckAdapter : RecyclerView.Adapter<DeckAdapter.DeckHolder>() {
    var data = listOf<Deck>()
    lateinit var binding: ListItemDeckBinding
    private lateinit var cardDatabase: CardDatabase
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()


    inner class DeckHolder(view: View) : RecyclerView.ViewHolder(view) {
        private var local = binding

        fun bind(deck: Deck) {
            local.deck = deck
            itemView.setOnClickListener {
                it.findNavController().navigate(DeckListFragmentDirections.actionDeckListFragmentToDeckEditFragment(deck.deckId))
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): DeckHolder {
        val layoutInflater = LayoutInflater.from(parent.context)
        binding = ListItemDeckBinding.inflate(layoutInflater, parent, false)

        cardDatabase = CardDatabase.getInstance(parent.context)
        cardDatabase.cardDao.getDecks(userId).observeForever{decks ->
            data = decks
            notifyDataSetChanged()
        }

        return DeckHolder(binding.root)
    }

    override fun onBindViewHolder(holder: DeckHolder, position: Int) {
        holder.bind(data[position])
    }

    override fun getItemCount() = data.size

}