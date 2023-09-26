package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase
import es.uam.eps.dadm.cards.databinding.ListItemCardBinding

class CardAdapter(private var isClickable: Boolean = true) : RecyclerView.Adapter<CardAdapter.CardHolder>() {

    var data = listOf<Card>()
    lateinit var binding: ListItemCardBinding
    private lateinit var cardDatabase: CardDatabase
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    inner class CardHolder(view: View) : RecyclerView.ViewHolder(view) {
        private var local = binding

        fun bind(card: Card) {
            local.card = card
            if (isClickable) {
                itemView.setOnClickListener {
                    it.findNavController().navigate(
                        CardListFragmentDirections.actionCardListFragmentToCardEditFragment(card.id)
                    )
                }
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CardHolder {
        val layoutInflater = LayoutInflater.from(parent.context)
        binding = ListItemCardBinding.inflate(layoutInflater, parent, false)

        cardDatabase = CardDatabase.getInstance(parent.context)
        cardDatabase.cardDao.getCards(userId).observeForever{cards ->
            data = cards
            notifyDataSetChanged()
        }

        return CardHolder(binding.root)

    }

    override fun getItemCount() = data.size

    override fun onBindViewHolder(holder: CardHolder, position: Int) {
        holder.bind(data[position])
    }
    @SuppressLint("NotifyDataSetChanged")
    fun setClickable(clickable: Boolean) {
        isClickable = clickable
        notifyDataSetChanged()
    }
}
