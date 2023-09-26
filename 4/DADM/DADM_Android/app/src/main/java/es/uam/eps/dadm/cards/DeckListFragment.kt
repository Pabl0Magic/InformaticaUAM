package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.databinding.FragmentDeckListBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.util.UUID


class DeckListFragment : Fragment() {
    private lateinit var adapterDeck: DeckAdapter
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    private val viewModel by lazy {
        ViewModelProvider(this)[DeckListViewModel::class.java]
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        val binding = DataBindingUtil.inflate<FragmentDeckListBinding>(
            inflater,
            R.layout.fragment_deck_list,
            container,
            false
        )

        adapterDeck = DeckAdapter()
        adapterDeck.data = emptyList()
        binding.deckListRecyclerView.adapter = adapterDeck

        binding.newAddFab.setOnClickListener {
            val deck = Deck("", deckId = UUID.randomUUID().toString(), userId = userId)

            CoroutineScope(Dispatchers.IO).launch {
                deck.userId = userId
                viewModel.addDeck(deck)
            }

            it.findNavController().navigate(DeckListFragmentDirections.actionDeckListFragmentToDeckEditFragment(deck.deckId))

        }

        viewModel.decks.observe(viewLifecycleOwner) {
            adapterDeck.data = it
            adapterDeck.notifyDataSetChanged()
        }

        return binding.root
    }

}