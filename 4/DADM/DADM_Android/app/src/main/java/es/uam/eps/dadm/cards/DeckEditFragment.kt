package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.activity.OnBackPressedCallback
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase
import es.uam.eps.dadm.cards.databinding.FragmentDeckEditBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class DeckEditFragment : Fragment() {
    lateinit var binding: FragmentDeckEditBinding
    lateinit var deck: Deck
    lateinit var name: String
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()
    private lateinit var cardListAdapter: CardAdapter
    //private val executor = Executors.newSingleThreadExecutor()

    private val viewModel by lazy {
        ViewModelProvider(this)[DeckListViewModel::class.java]
    }


    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_deck_edit,
            container,
            false
        )
        val args = DeckEditFragmentArgs.fromBundle(requireArguments())

        cardListAdapter = CardAdapter()
        cardListAdapter.setClickable(false)
        binding.cardByDeckRecyclerView.apply {
            adapter = cardListAdapter
            layoutManager = LinearLayoutManager(requireContext())
        }

        viewModel.getDeck(args.deckId).observe(viewLifecycleOwner) { retrievedDeck ->
            deck = retrievedDeck!!
            binding.deck = deck
            name = deck.name

            viewModel.getCardsByDeck(deck.deckId).observe(viewLifecycleOwner) { cards ->
                cardListAdapter.data = cards
                cardListAdapter.notifyDataSetChanged()
            }
        }



        return binding.root
    }

    override fun onStart() {
        super.onStart()

        val callback = object: OnBackPressedCallback(true) {
            override fun handleOnBackPressed() {
                deck.name = name
                if (deck.name == "") {
                    CoroutineScope(Dispatchers.IO).launch {
                        viewModel.deleteDeck(deck)
                    }
                }
                view?.findNavController()?.navigate(R.id.action_deckEditFragment_to_deckListFragment)
            }
        }

        requireActivity().onBackPressedDispatcher.addCallback(viewLifecycleOwner, callback)

        val nameTextWatcher = object : TextWatcher {
            override fun afterTextChanged(s: Editable?) {}

            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {}

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                deck.name = s.toString()
            }
        }

        binding.deckNameEditText.addTextChangedListener(nameTextWatcher)

        binding.cancelCardEditButton.setOnClickListener {
            deck.name = name
            if (deck.name == "") {
                CoroutineScope(Dispatchers.IO).launch {
                    viewModel.deleteDeck(deck)
                }
            }

            it.findNavController().navigate(R.id.action_deckEditFragment_to_deckListFragment)
        }

        binding.acceptCardEditButton.setOnClickListener {
            deck.delete = true
            val cardDatabase = context?.let { it1 -> CardDatabase.getInstance(it1) }
            val aux = cardDatabase?.cardDao?.getDeck(deck.deckId)

            if (deck.toString() == aux.toString()) {
                CoroutineScope(Dispatchers.IO).launch {
                    viewModel.updateDeck(deck)
                }
            } else {
                CoroutineScope(Dispatchers.IO).launch {
                    deck.userId = userId
                    viewModel.addDeck(deck)
                }
            }

            it.findNavController().navigate(R.id.action_deckEditFragment_to_deckListFragment)
        }

        binding.deleteCardEditButton.setOnClickListener {
            CoroutineScope(Dispatchers.IO).launch {
                viewModel.deleteDeck(deck)
            }
            it.findNavController().navigate(R.id.action_deckEditFragment_to_deckListFragment)
        }
    }

}