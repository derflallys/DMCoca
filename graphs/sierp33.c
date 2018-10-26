int orderG(){
return 27;}

int sizeG(){
return 39;
}

int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<orderG() && v<orderG()){
  if((u/3==v/3) && ((u/9==v/9) || (u/9==v%3 && v/9==u%3)))
   return 1; 
  if(u/3==v%3 && u/3==(v/3)%3 && u/3==v%3 && v/3==(u/3)%3)
   return 1;
  }
 return 0;
}

