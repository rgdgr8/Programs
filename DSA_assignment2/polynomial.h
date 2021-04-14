#include <stdio.h>
#include <stdlib.h>
#define COMPARE(a,b) a==b ? 0 : (a>b ? 1 : -1)

typedef struct term{
 int exp;
 float coeff;
}term;
term *t;

typedef struct polynomial{
 int start;
 int end;
}polynomial;
polynomial* p;

  int pi = 0;//polynomial array index
  int ti = 0;//term array index
  int max_t = 0;//maximum terms
  int max_p = 0;//maximum polynomials

  void initiate(){//initiate terms array and polynomials array
    if(max_t>0 && max_p>0){
      printf("Already initiated!\n");
      return;
    }
    else{
      printf("Enter maximum number of polynomials required: ");
      scanf("%d",&max_p);
      printf("Enter maximum number of terms required: ");
      scanf("%d",&max_t);
      t = malloc(max_t*sizeof(term));
      p = malloc(max_p*sizeof(polynomial));
    }
  }

  polynomial zero(){//return a polynomial p(x) = 0
    polynomial x = {-1,-1};
    return x;
  }

  void insert(polynomial* a){//insert into terms(t) and polynomials(p) arrays
    if(max_t<=0 || max_p<=0){
      printf("Initiate first by calling initiate()\n");
      return; 
    }

    int terms;
    printf("Enter number of terms for for the %dth polynomial: ",pi);
    scanf("%d",&terms);

    if(terms>(max_t-ti) || pi>=max_p){//if not enough space in terms or polynomials array(p)
      printf("Not enough space\n");
      return;
    }

    a->start = ti;
    a->end = (ti+terms-1);
    p[pi++] = *a;

    printf("Input in strictly desecnding order of exponents\n");
    for(int i=0;i<terms;i++){
       int e;float c;
      do{
       printf("Enter power of variable(less than the previous terms): ");
       scanf("%d",&e);
      
       if(i>0 && e>=t[ti-1].exp)
          printf("Input in strictly desecnding order of exponents!!!\n");
       else
          break;
      }while(1);

       printf("Enter coefficient: ");
       scanf("%f",&c);
       term x = {e,c};
       t[ti++] = x;
    }
  }

  polynomial padd(polynomial a,polynomial b){//add two polynomials
    if(max_t<=0 || max_p<=0){
      printf("Initiate first by calling initiate()\n");
      return zero();
    }
    if(pi>=max_p){//if polynomial array(p) is full
      printf("Not enough space\n");
      return zero();
    }

    int tti = ti;//save the initial index of terms array(t)

    if(a.start==-1){//if a is a zero polynomial

      for(int i=a.start;i<=a.end;i++){//copy data one by one from a into terms array(t)
         t[ti].exp = t[i].exp;
         t[ti++].coeff = t[i].coeff;
      }
      polynomial tp = {tti,(ti-1)};
      p[pi++] =  tp;
      return tp;
    }

    if(b.start==-1){//if b is a zero polynomial

      for(int i=b.start;i<=b.end;i++){//copy data one by one from b into terms array(t)
         t[ti].exp = t[i].exp;
         t[ti++].coeff = t[i].coeff;
      }
      polynomial tp = {tti,(ti-1)};
      p[pi++] =  tp;
      return tp;
    }
 
    int tas = a.start;
    int tbs = b.start;
    
    while(tas<=a.end && tbs<=b.end){//while one of the two polynomials is fully read

       if(ti>=max_t){//if terms array(t) is full
         printf("Not enough space\n");
         ti = tti;
         return zero();
       }

       int res = COMPARE(t[tas].exp,t[tbs].exp);//compare exponents of the current term

       if(res==0){//if the exponents are equal

         term tt = {t[tas].exp,(t[tas].coeff+t[tbs].coeff)};//add the coefficients
         t[ti++] = tt;
         tas++;tbs++;
       }else if(res==-1){//if the exponent of a is lesser than b

         term tt = {t[tbs].exp,(t[tbs].coeff)};//put the coefficient of b
         t[ti++] = tt;
         tbs++;
       }else{//if the exponent of a is greater than b

         term tt = {t[tas].exp,(t[tas].coeff)};//put the coefficient of a
         t[ti++] = tt;
         tas++;
       }
    }

    while(tas<=a.end){//put the rest of unread terms of a(if left) into terms array(t)
       if(ti>=max_t){
         printf("Not enough space\n");
         ti = tti;
         return zero();
       }
         term tt = {t[tas].exp,(t[tas].coeff)};
         t[ti++] = tt;
         tas++;
    }
    while(tbs<=b.end){//put the rest of unread terms of b(if left) into terms array(t)
       if(ti>=max_t){
         printf("Not enough space\n");
         ti = tti;
         return zero();
       }
         term tt = {t[tbs].exp,(t[tbs].coeff)};
         t[ti++] = tt;
         tbs++;
    }
    
    polynomial tp = {tti,(ti-1)};
    p[pi++] =  tp;
    return tp;
  }

  polynomial pmul(polynomial a,polynomial b){//multiply two polynomials
    if(max_t<=0 || max_p<=0){
      printf("Initiate first by calling initiate()\n");
      return zero();
    }
    if(a.start==-1 || b.start==-1)//if a or b is a zero  polynomial
      return zero();
    if(pi>=max_p){//if polynomials array(p) is full
       printf("Not enough space\n");
       return zero();
    }

     int a_length = a.end-a.start+1;//number of terms in a
     int b_length = b.end-b.start+1;//number of terms in b
     term tt[(a_length+b_length)];//temporary terms array
     int tti = 0;//temporary terms array index
     int init_ti = ti;//save the initial terms array index
     int space = max_t-ti;//space left in the original terms array(t)

     for(int i=a.start;i<=a.end;i++){
        for(int j=b.start;j<=b.end;j++){
           term ttt = {(t[i].exp+t[j].exp),(t[i].coeff*t[j].coeff)};//new term by adding exponents and multiplying coeffs
           //printf("ttt= %.3fxE%d\n",ttt.coeff,ttt.exp);
           int flag = 0;
           for(int k=0;k<tti;k++)//loop through temporary terms array(tt)

              if(ttt.exp == tt[k].exp){//if any term in the tt has same exponent as ttt 
                tt[k].coeff += ttt.coeff;//then add the coeffs
                flag = 1;//set flag
                break;
              }

           if(flag==0){//if flag not set
             if(tti>space){//check if original terms array(t) has space for another term
               printf("Not enough space\n");
               ti = init_ti;
               return zero();
             }

             tt[tti++] = ttt;//if has space then add term into temporary array(tt)
           }

           /*for(int k=0;k<tti;k++){
             printf("tt[%d]= %.3fxE%d\n",k,tt[k].coeff,tt[k].exp);
           }*/
        }
     }
    
     int c = 0;
     while(c<tti){//loop through tt

        if(ti>=max_t){//check if t is full
           printf("Not enough space\n");
           ti = init_ti;
           return zero();
        }
        
        int max_i = -1;
        int max = -1;
        for(int i=0;i<tti;i++)
           if(max<tt[i].exp){//find the max exponent term in tt
             max = tt[i].exp;
             max_i = i;
           }
        
        t[ti++] = tt[max_i];//if t not full then copy max exponent term from tt to t
        c++;
        tt[max_i].exp = -1;
     }
      
     polynomial tp = {init_ti,(ti-1)};
     p[pi++] = tp;
     return tp;
  }

  polynomial const_mul(float x,polynomial a){//multiply polynomial with a constant
    if(max_t<=0 || max_p<=0){
      printf("Initiate first by calling initiate()\n");
      return zero();
    }
    if(a.start==-1)//if a is a zero  polynomial
      return zero();

    int length = a.end-a.start+1;//number of terms in a

    if(length>(max_t-ti) || pi>=max_p){//check space in polynomial array(p) and terms array(t)
      printf("Not enough space\n");
      return zero();
    }

    polynomial y = {ti,(ti+length-1)};
    p[pi++] = y;
    
    for(int i=a.start;i<=a.end;i++){
       term tt = {t[i].exp,(x*t[i].coeff)};//multiply each term with the given constant
       t[ti++] = tt;//put into t
    }

    return y;
  }
 
  void print(polynomial a){
    if(a.start==-1){//if a is a zero  polynomial
      printf("0\n");
      return;
    }
    for(int i=a.start;i<=a.end;i++){
       if(i==a.end)
         printf("%.3fxE%d\n",t[i].coeff,t[i].exp);
       else
         printf("%.3fxE%d + ",t[i].coeff,t[i].exp);
    }
  }

