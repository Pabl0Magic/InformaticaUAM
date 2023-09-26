package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.*
import androidx.fragment.app.Fragment
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.databinding.FragmentCardListBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.util.UUID

//import java.util.concurrent.Executors

class CardListFragment : Fragment() {
    //private val executor = Executors.newSingleThreadExecutor()
    private lateinit var adapterCard: CardAdapter
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    private val cardListViewModel by lazy {
        ViewModelProvider(this)[CardListViewModel::class.java]
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentCardListBinding>(
            inflater,
            R.layout.fragment_card_list,
            container,
            false
        )

        adapterCard = CardAdapter()
        adapterCard.data = emptyList()
        binding.cardListRecyclerView.adapter = adapterCard


        binding.newAddFab.setOnClickListener {
            val card = Card("", "", userId = userId, deckId = UUID.randomUUID().toString())
            card.delete = false
            card.showDetails = false
            /*val cardDatabase = context?.let { it1 -> CardDatabase.getInstance(it1) }

            executor.execute {
                cardDatabase?.cardDao?.addCard(card)
            }*/

            CoroutineScope(Dispatchers.IO).launch {
                card.userId = userId
                cardListViewModel.addCard(card)
            }

            // Navigate to CardEditFragment
            it.findNavController().navigate(CardListFragmentDirections.actionCardListFragmentToCardEditFragment(card.id))
        }

        cardListViewModel.cards.observe(viewLifecycleOwner) {
            adapterCard.data = it
            adapterCard.notifyDataSetChanged()
        }

        SettingsActivity.setLoggedIn(requireContext(), true)

        /*
        binding.cardListButton.setOnClickListener { view ->
            if (CardsApplication.numberOfDueCards() > 0)
                view.findNavController()
                    .navigate(R.id.action_cardListFragment_to_studyFragment3)
            else
                Toast.makeText(
                    requireActivity(),
                    R.string.no_more_cards_toast_message,
                    Toast.LENGTH_LONG
                ).show()
        }
        */

        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        SettingsActivity.getMaximumNumberOfCards(requireContext())
            ?.let { Snackbar.make(view, it, 3) }
    }
}