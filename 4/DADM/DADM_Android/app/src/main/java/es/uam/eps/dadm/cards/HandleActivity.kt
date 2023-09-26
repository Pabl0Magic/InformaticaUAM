package es.uam.eps.dadm.cards

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.google.firebase.auth.FirebaseAuth

class HandleActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val currentUser = FirebaseAuth.getInstance().currentUser
        if (currentUser != null) {
            val intent = Intent(this, TitleActivity::class.java)
            startActivity(intent)
            finish()
        } else {
            val intent = Intent(this, EmailPasswordActivity::class.java)
            startActivity(intent)
            finish()
        }
    }
}