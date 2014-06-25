serveur* factory(struct args* args){
  serveur* this;

  if ((this = malloc(sizeof(serveur))))
    lerror(MEMORY_ERROR(sizeof(serveur)));
  return (this);
}
