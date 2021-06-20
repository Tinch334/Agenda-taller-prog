static void imprimirContacto(Contacto contacto) {
    printf("\n%-10s \t %-s \t %-7s \t %-25s \t %-15s \t %-10s \t \n","Nombre","Direccion","Telefono","Mail","Telegram","Instagram");    
    printf("%-10s \t %-s \t %-7s \t %-25s \t %-15s \t %-10s \t \n",contacto.nombre,contacto.direccion,contacto.telefono,contacto.mail,contacto.aliasTelegram,contacto.usuarioInstagram);
}