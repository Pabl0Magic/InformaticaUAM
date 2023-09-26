package es.uam.eps.dadm.cards

import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Spinner
import android.widget.Toast
import androidx.activity.OnBackPressedCallback
import androidx.databinding.DataBindingUtil
//import androidx.lifecycle.Observer
import androidx.navigation.findNavController
import es.uam.eps.dadm.cards.databinding.FragmentCardEditBinding
import androidx.lifecycle.ViewModelProvider
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
//import java.util.concurrent.Executors


class CardEditFragment : Fragment() {
    //private val executor = Executors.newSingleThreadExecutor()
    lateinit var binding: FragmentCardEditBinding
    lateinit var card: Card
    lateinit var question: String
    lateinit var answer: String
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()
    private lateinit var deckSpinner: Spinner
    private lateinit var deckAdapter: ArrayAdapter<String>
    private lateinit var deckSel: Deck
    private lateinit var deckName: String
    private lateinit var deckList: List<Deck>

    private val viewModel by lazy {
        ViewModelProvider(this)[CardListViewModel::class.java]
    }

    private val deckViewModel by lazy {
        ViewModelProvider(this)[DeckListViewModel::class.java]
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_card_edit,
            container,
            false
        )

        deckSpinner = binding.deckSpinner
        deckAdapter = ArrayAdapter(requireContext(), android.R.layout.simple_spinner_item)
        deckAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        deckSpinner.adapter = deckAdapter

        val args = CardEditFragmentArgs.fromBundle(requireArguments())
        viewModel.getCard(args.cardId).observe(viewLifecycleOwner) { retrievedCard ->
            card = retrievedCard!!
            binding.card = card
            question = card.question
            answer = card.answer
        }

        deckViewModel.getDecks(userId).observe(viewLifecycleOwner) { decks ->
            deckList = decks
            deckAdapter.clear()
            deckAdapter.addAll(decks.map {it.name})
            deckAdapter.notifyDataSetChanged()
        }

        binding.deckSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                deckName = deckAdapter.getItem(position).toString()
                deckSel = deckList.find { it.name == deckName} ?: Deck("", "", "")
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {
                // Handle when nothing is selected
            }
        }

        return binding.root
    }

    override fun onStart() {
        super.onStart()

        val callback = object: OnBackPressedCallback(true) {
            override fun handleOnBackPressed() {
                card.question = question
                card.answer = answer
                if (card.question == "" || card.answer == "") {
                    CoroutineScope(Dispatchers.IO).launch {
                        viewModel.deleteCard(card)
                    }
                }
                view?.findNavController()?.navigate(R.id.action_cardEditFragment_to_cardListFragment)
            }
        }

        requireActivity().onBackPressedDispatcher.addCallback(viewLifecycleOwner, callback)

        val questionTextWatcher = object : TextWatcher {
            override fun afterTextChanged(s: Editable?) {}

            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {}

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                card.question = s.toString()
            }
        }

        val answerTextWatcher = object : TextWatcher {
            override fun afterTextChanged(s: Editable?) {}

            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {}

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                card.answer = s.toString()
            }
        }

        binding.questionEditText.addTextChangedListener(questionTextWatcher)
        binding.answerEditText.addTextChangedListener(answerTextWatcher)

        binding.cancelCardEditButton.setOnClickListener {
            card.question = question
            card.answer = answer

            if (card.answer == "" && card.question == "") {
                CoroutineScope(Dispatchers.IO).launch {
                    viewModel.deleteCard(card)
                }
            }

                it.findNavController().navigate(R.id.action_cardEditFragment_to_cardListFragment)
        }

        binding.acceptCardEditButton.setOnClickListener {
            card.delete = true
            card.showDetails = true
            card.q = card.question
            card.a = card.answer

            if (::deckSel.isInitialized) {
                card.deckId = deckSel.deckId

                val cardDatabase = context?.let { it1 -> CardDatabase.getInstance(it1) }


                if (card == cardDatabase?.cardDao?.getCard(card.id)) {
                    CoroutineScope(Dispatchers.IO).launch {
                        viewModel.updateCard(card)
                        deckViewModel.updateDeck(deckSel)
                    }
                } else {
                    CoroutineScope(Dispatchers.IO).launch {
                        card.userId = userId
                        viewModel.addCard(card)
                        deckViewModel.updateDeck(deckSel)
                    }
                }

                /*if(!first) {
                executor.execute {
                    cardDatabase?.cardDao?.update(card)
                }
            } else {
                executor.execute {
                    cardDatabase?.cardDao?.addCard(card)
                    first = false
                }
            }*/

                it.findNavController().navigate(R.id.action_cardEditFragment_to_cardListFragment)

            } else {
                Toast.makeText(requireContext(), "No decks found. Please create a deck first.", Toast.LENGTH_SHORT).show()
            }

        }


        binding.deleteCardEditButton.setOnClickListener {
            CoroutineScope(Dispatchers.IO).launch {
                viewModel.deleteCard(card)
            }

            it.findNavController().navigate(R.id.action_cardEditFragment_to_cardListFragment)
        }
        /*binding.deleteFirebaseCardEditButton.setOnClickListener {

            it.findNavController().navigate(R.id.action_cardEditFragment_to_cardListFragment)
        }*/

        binding.detailsCardEditButton.setOnClickListener {
            //CardsApplication.showDetails(CardsApplication.getCard(card.id))
            it.findNavController().navigate(CardEditFragmentDirections.actionCardEditFragmentSelf(card.id))
        }

    }
}