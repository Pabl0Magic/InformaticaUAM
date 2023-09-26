package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import es.uam.eps.dadm.cards.databinding.FragmentAboutBinding

class AboutFragment : Fragment() {

    @SuppressLint("SetTextI18n")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentAboutBinding>(
            inflater,
            R.layout.fragment_about,
            container,
            false
        )

        binding.authorTextAbout.text = "Author: Pablo Almarza Marques"
        binding.versionTextAbout.text = "Version 1.0"
        binding.descriptionTextAbout.text = "Description:\nYou will be able to learn a correlation between two things, including:\n" +
                "Word definition\nWord translation\nDate of historical events\n And more..."


        return binding.root
    }

}