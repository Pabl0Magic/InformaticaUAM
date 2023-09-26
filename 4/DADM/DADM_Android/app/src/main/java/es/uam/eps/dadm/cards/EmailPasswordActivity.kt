package es.uam.eps.dadm.cards

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.auth.FirebaseUser
import com.google.firebase.auth.ktx.auth
import com.google.firebase.ktx.Firebase
//import es.uam.eps.dadm.cards.databinding.ActivityEmailPasswordBinding
import timber.log.Timber


class EmailPasswordActivity : AppCompatActivity() {
    private lateinit var auth: FirebaseAuth
    //lateinit var binding: ActivityEmailPasswordBinding

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        auth = Firebase.auth

        if (auth.currentUser != null) {
            val intent = Intent(this, TitleActivity::class.java)
            startActivity(intent)
            finish()
        } else {
            setContentView(R.layout.activity_email_password)
            val signInButton = findViewById<Button>(R.id.emailSignInButton)
            val createAccountButton = findViewById<Button>(R.id.emailCreateAccountButton)


            signInButton.setOnClickListener {
                val email = findViewById<EditText>(R.id.fieldEmail).text.toString()
                val password = findViewById<EditText>(R.id.fieldPassword).text.toString()
                if (validCredentials(email, password)) {
                    signIn(email, password)
                } else {
                    Timber.tag(TAG).w("Invalid credentials")
                }
            }

            createAccountButton.setOnClickListener {
                val email = findViewById<EditText>(R.id.fieldEmail).text.toString()
                val password = findViewById<EditText>(R.id.fieldPassword).text.toString()
                if (validCredentials(email, password)) {
                    createAccount(email, password)
                } else {
                    Timber.tag(TAG).w("Invalid credentials")
                }
            }
        }
    }

    public override fun onStart() {
        super.onStart()
        // Check if user is signed in (non-null) and update UI accordingly.
        //val currentUser = auth.currentUser
    }

    private fun createAccount(email: String, password: String) {
        auth.createUserWithEmailAndPassword(email, password)
            .addOnCompleteListener(this) { task ->
                if (task.isSuccessful) {
                    // Sign in success, update UI with the signed-in user's information
                    Timber.tag(TAG).d("createUserWithEmail:success")
                    val user = auth.currentUser
                    updateUI(user)
                } else {
                    // If sign in fails, display a message to the user.
                    Timber.tag(TAG).w(task.exception, "createUserWithEmail:failure")
                    Toast.makeText(
                        baseContext, "Authentication failed. Email must be valid and password must be at least 6 characters.",
                        Toast.LENGTH_SHORT
                    ).show()
                    updateUI(null)
                }
            }
    }

    private fun signIn(email: String, password: String) {
        auth.signInWithEmailAndPassword(email, password)
            .addOnCompleteListener(this) { task ->
                if (task.isSuccessful) {
                    // Sign in success, update UI with the signed-in user's information
                    Timber.tag(TAG).d("signInWithEmail:success")
                    val user = auth.currentUser
                    updateUI(user)
                } else {
                    // If sign in fails, display a message to the user.
                    Timber.tag(TAG).w(task.exception, "signInWithEmail:failure")
                    Toast.makeText(
                        baseContext, "Authentication failed.",
                        Toast.LENGTH_SHORT
                    ).show()
                    updateUI(null)
                }
            }
    }


    private fun updateUI(user: FirebaseUser?) {
        if (user != null) {
            val intent = Intent(this, TitleActivity::class.java)
            startActivity(intent)
        }
    }

    /*
    private fun getUser() {
        val user = Firebase.auth.currentUser
        user?.let {
            // Name, email address, and profile photo Url
            val name = it.displayName
            val email = it.email
            val photoUrl = it.photoUrl

            // Check if user's email is verified
            val emailVerified = it.isEmailVerified

            // The user's ID, unique to the Firebase project. Do NOT use this value to
            // authenticate with your backend server, if you have one. Use
            // FirebaseUser.getIdToken() instead.
            val uid = it.uid
        }
    }
     */

    private fun validCredentials(email: String, password: String): Boolean {
        if (email.isEmpty() || password.isEmpty()) {
            return false
        }

        return true
    }

    companion object {
        private const val TAG = "EmailPassword"

        /*fun getUser() {
            val user = Firebase.auth.currentUser
            user?.let {
                // Name, email address, and profile photo Url
                val name = it.displayName
                val email = it.email
                val photoUrl = it.photoUrl

                // Check if user's email is verified
                val emailVerified = it.isEmailVerified

                // The user's ID, unique to the Firebase project. Do NOT use this value to
                // authenticate with your backend server, if you have one. Use
                // FirebaseUser.getIdToken() instead.
                val uid = it.uid
            }
        }*/
    }
}


