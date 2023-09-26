function validarNombre() {
     let x = document.forms["register"]["name"].value;
     let y = /\s/g.test(x);
     let z = /[~`!#$%\^&*+=\-\[\]\\';,/{}|\\":<>\?]/g.test(x);

     if (y == false || z == false) {

        return true;
     }

     alert("El nombre debe tener al menos 5 caracteres y no contener espacios ni caracteres especiales.");
     return false;
}

function validarEmail() {
    let x = document.forms["register"]["email"].value;
    

    if(/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(x)) {
        return true;
    }

    alert("Formato de email no valido.");
    return false;
}

function getPassword() {
    let x = document.forms["register"]["pass"].value;
    
    if(x.length >= 6) {
        return true;
    }

    alert("La contraseña debe tener al menos 6 caracteres");
    return false;
}

function validarPassword() {
    let x = document.forms["register"]["pass"].value;
    let y = document.forms["register"]["checkpass"].value;
    var mes = document.getElementById("error_checkpassword")

    if (x == y) {
        mes.innerHTML = "Las contraseñas coinciden"
        return true;
    }

    mes.innerHTML = "Las contraseñas no coinciden"
    return false;
}

function validarTarjeta() {
    var x = document.forms["register"]["tarjeta"].value;

    if (x.length == 16) {
        return true;
    }

    alert("El numero de tarjeta no es valido");
    return false;
}

function validarDireccion() {
    let x = document.forms["register"]["direccion"].value;

    if (x.length <= 50) {
        return true;
    }

    alert("La direccion no es valida");
    return false;
}

function validarUsuario() {
    let a = validarNombre()
    let b = validarEmail()
    let c = validarPassword()
    let d = validarTarjeta()
    let e = validarDireccion()

    if(a&&b&&c&&d&&e){
        return true;
    }else{
        return false;
    }
}

function removeAll() {
    let x = document.querySelectorAll()
}

