import java.util.Scanner;

class polinomio {

   public static void main(String[] args) {
   
         Scanner xleer = new Scanner(System.in);
         /*int n = 0;
         int m = 0;
         int l = 0;*/
         int MOD;
         int power;
         int module;
         
         System.out.print("Introduce (mod n) = "); MOD = xleer.nextInt(); 
         System.out.print("\n\nIngrese g(x): \n\n");
         ZnPoli I = leerPoli(MOD);
         I.escP();
         System.out.print("\n\n");
         
         ZnPoli p = leerPoli(MOD);
         p.escP();
         System.out.print("\n\n\n residuo(x) := ");

         I.modP(p, MOD).escP();
        System.out.print("\n\n\n");
   }


   public static int potMod(int n, int m, int mod) {////////potencias en Z_n
          int p = 1;
          if (m == 0) return p;
          else{
          for (int i = 0; i < m; i++) p *= n;
          return p%mod;    
          }   
   }

   public static int inversoZp(int a, int MOD) {////////inverso en Z_p
         return potMod(a, MOD - 2, MOD);
   }

   public static int divideZp(int num, int den, int MOD) {////////////////////////////////division en Z_p
         return (num * inversoZp(den, MOD))%MOD;    
   }

   public static ZnPoli leerPoli(int MOD) {
         int n;
         Scanner xleer = new Scanner(System.in);
         System.out.println("\nChoose the degree of the polinomial:");
         System.out.print("deg(p) = "); n = xleer.nextInt();
         int[] c = new int[n+1];
         System.out.print("\nNow type the coeficientes needed:\n");
         for (int i = 0; i < c.length; i++) {
             System.out.format("a[%d] = ", i); c[i] = xleer.nextInt(); 
         }
         
         return new ZnPoli(c, MOD); 
   }

}

class ZnPoli {
  int[] a;

  ZnPoli(int[] c, int mod) {//////////////////////contruir poli
        for (int i = 0; i < c.length; i++) {
            c[i] %= mod;
        }
   
        a = new int[check(c) + 1];
        for (int i = 0; i < check(c) + 1; i++) {
            a[i] = c[i];
         }        
  }

  private static int check(int[] c) {//////////////revisar ceros
         int suma = 0;
         for (int i = 0; i < c.length; i++) {
             suma += c[i];
         }
         if (suma == 0) return 0;
         else {
               int cont = c.length - 1;
               while(c[cont] == 0) {
                    cont -=1;
               }
               return cont;
         }
         
  }

  void escP() {//////////////////////////////////escribir polinomio
      System.out.print("p(x) = ");


      int suma = 0;
      for (int i = 0; i < a.length; i++) {if (a[i] != 0) suma += 1; else{suma += 0;}}
    
      if (suma == 0) {System.out.println(0);}
      else{
         if (a[0] != 0) {System.out.format("%d + ", a[0]);}
         for (int i = 1; i < a.length - 1; i++) {
             if (a[i] != 1) {if (a[i] != 0) System.out.format("%dx^{%d} + ", a[i], i);}
             else {System.out.format("x^{%d} + ", i);}
         }
         if (a[a.length - 1] != 1 && (a.length - 1) != 0){System.out.format("%dx^{%d}", a[a.length - 1], a.length - 1);}
         else {if ((a.length - 1) != 0)System.out.format("x^{%d}", a.length - 1);}
         }
  }

  int evalP(int x, int mod) {////////////////////evaluar polinomio
      int sum = 0;
      for (int i = 0; i < a.length; i++) {
          sum += a[i] * pot(x, i);
      }
      return sum%mod;
  }


  ZnPoli addPQ(ZnPoli p, int mod) {/////////////sumar de dos polinomios
         int[] c = new int[max(a.length, p.a.length)];
         if (a.length == p.a.length) {
            for (int i = 0; i < a.length; i++) {
                c[i] = a[i] + p.a[i];
                c[i] = c[i]%mod;
            }
         }else{
               if (a.length < p.a.length) {
                  for (int i = 0; i < a.length; i++) {
                      c[i] = a[i] + p.a[i];
                      c[i] = c[i]%mod;
                  }
                  
                  for (int i = a.length; i < p.a.length; i++) {
                      c[i] = p.a[i];
                  }
               }
               else{
                  for (int i = 0; i < p.a.length; i++) {
                      c[i] = a[i] + p.a[i];
                      c[i] = c[i]%mod;
                  }
                  
                  for (int i = p.a.length; i < a.length; i++) {
                      c[i] = a[i];
                  }
               }
         }
   return new ZnPoli(c, mod);
  }

 
  ZnPoli subPQ(ZnPoli p, int mod) {/////////////sumar de dos polinomios
         int[] c = new int[max(a.length, p.a.length)];
         if (a.length == p.a.length) {
            for (int i = 0; i < a.length; i++) {
                c[i] = (a[i] - p.a[i])%mod;
                if (c[i] < 0) {c[i] += mod; c[i] %= mod;}
            }
         }else{
               if (a.length < p.a.length) {
                  for (int i = 0; i < a.length; i++) {
                      c[i] = (a[i] - p.a[i])%mod;
                      if (c[i] < 0) {c[i] += mod; c[i] %= mod;}
                  }
                  
                  for (int i = a.length; i < p.a.length; i++) {
                      c[i] = p.a[i];
                  }
               }
               else{
                  for (int i = 0; i < p.a.length; i++) {
                      c[i] = (a[i] - p.a[i])%mod;
                      if (c[i] < 0) {c[i] += mod; c[i] %= mod;}
                  }
                  
                  for (int i = p.a.length; i < a.length; i++) {
                      c[i] = a[i];
                  }
               }
         }
   return new ZnPoli(c, mod);
  }

  ZnPoli multP(ZnPoli p, int mod) {/////////////multiplicar polinomio
        int[] c = new int[a.length + p.a.length];
    
        for (int i = 0; i < a.length; i++)
            for (int j = 0; j < p.a.length; j++) {
                c[i+j] += a[i] * p.a[j];
            }
        ZnPoli r = new ZnPoli(c, mod);
        return r;
  }

  ZnPoli multS(int k, int mod) {/////////////multiplicar polinomio
        int[] c = new int[a.length];
    
        for (int i = 0; i < a.length; i++) {
            c[i] = k * a[i];
        }
        
        return new ZnPoli(c, mod);
  }


  private static int pot(int p, int n) {////////////funcion potencia de enteros
         int po = 1;
         if (n == 0) return 1;
         else {
               for (int i = 0; i < n; i++) {
                  po *= p;
               }
               return po;
         } 
   }

   private static int max(int a, int b) {/////////////maximo de dos enteros
          if(a == b) {return a;}
          else{
              if(a < b) return b;
              else{return a;}
          }
   }

   int irreducible(int mod) {
      int ret = 0;
      int root = 0;
      while (ret != mod){
           int sum = 0;
           for (int i = 0; i < a.length; i++) {
               sum += a[i] * pot(ret, i);
           } 
           ret += 1;
           if (sum%mod == 0) {root += 1; break;}
      }
     return root;
   }

   ZnPoli vector(int degree, int polinomio, int mod) {///////////////find elements of Zn[x]/P
          
          degree %= a.length - 1;
          polinomio %= mod;
          int[] zero = {0};
          if(polinomio == 0) {return new ZnPoli(zero, mod);}

          int[][][] b = new int[a.length][mod][a.length];
          int[] ret = new int[a.length];
          for (int k = 0; k < a.length - 1; k++) {  
              for (int i = 0; i < mod; i++)
                  for (int j = 0; j < a.length; j++) {
                      if (j == k) b[k][i][j] = i;
                      else {b[k][i][j] = 0;}
              }
          }
     
           for (int i = 0; i < a.length; i++)
               ret[i] = b[degree][polinomio][i];

           b = null;
           return new ZnPoli(ret, mod);
   }

   public static int potMod(int n, int m, int mod) {////////potencias en Z_n
          int p = 1;
          if (m == 0) return p;
          else{
          for (int i = 0; i < m; i++) p *= n;
          return p%mod;    
          }   
   }

   public static int inversoZp(int a, int MOD) {////////inverso en Z_p
         return potMod(a, MOD - 2, MOD);
   }

   public static int divideZp(int num, int den, int MOD) {////////////////////////////////residuo de dividir polinomios
         return (num * inversoZp(den, MOD))%MOD;    
   }

   ZnPoli modP(ZnPoli p, int MOD) {
          int[] q = new int[a.length - p.a.length + 1];
          
          ZnPoli r = new ZnPoli(a, MOD);
          ZnPoli aux = new ZnPoli(p.a, MOD);

          for (int i = 0; i < q.length; i++) {
              q[i] = 0;
          }

          System.out.print("\n\nFirst Residuo := "); r.escP();
          
          while (r.zero() == false && r.a.length >= p.a.length) {
                
                int t = divideZp(r.a[r.a.length - 1], p.a[p.a.length - 1], MOD);
                int[] t1 = new int[r.a.length - p.a.length + 1];

                for (int i = 0; i < t1.length - 2; i++) {
                    t1[i] = 0;
                }

                t1[t1.length - 1] = t;

                ZnPoli T = new ZnPoli(t1, MOD);
                r = r.subPQ(T.multP(p, MOD), MOD);
                t1 = null;
          }


          return r;
   }

   boolean zero() {////////////////////////////////////////////revisa si un polinomio es cero
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
          if (a[i] != 0) {sum += 1;}
        }
       if (sum == 0) return true;
       else {return false;}
   }

   ZnPoli multIdeal(ZnPoli p, ZnPoli q, int MOD) {/////////////multiplication over ideals
          if (p.zero() || q.zero()) {
             int[] zero = new int[1];
             zero[0] = 0;
             return new ZnPoli(zero, MOD);
          }

          if (p.a.length == 0 && q.a.length == 0) {
             return p.multP(q, MOD);
          }else{
         
          ZnPoli comb = p.multP(q, MOD);
          ZnPoli f = new ZnPoli(a, MOD);
          return comb.modP(f, MOD);
          }
   }

}


